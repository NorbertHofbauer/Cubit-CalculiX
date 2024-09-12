#include "CoreResultsDat.hpp"
#include "CalculiXCoreInterface.hpp"
#include "CubitInterface.hpp"
#include "CubitMessage.hpp"
#include "StopWatch.hpp"
#include "loadUserOptions.hpp"

#include "ThreadPool.hpp"
#include <functional>

#include <fstream>
#include <iostream>

CoreResultsDat::CoreResultsDat()
{}

CoreResultsDat::~CoreResultsDat()
{}

bool CoreResultsDat::init(int job_id)
{
  if (is_initialized)
  {
    return false; // already initialized
  }else{
    CalculiXCoreInterface *ccx_iface = new CalculiXCoreInterface();
    this->job_id = job_id;
    
    std::vector<std::string> job_data = ccx_iface->get_job_data(job_id);
    this->filepath = job_data[1] + ".dat";

    progressbar = new ProgressTool();

    is_initialized = true;
    return true;
    return true;
  }
}

bool CoreResultsDat::reset()
{
  init(-1);
  return true;
}

bool CoreResultsDat::clear()
{
  result_blocks.clear();
  total_times.clear();
  result_block_components.clear();
  result_block_type.clear();
  result_block_set.clear();
  result_block_data.clear();
  result_block_c1_data.clear();
  buckle_data.clear();
  dat_arrays.clear();

  return true;
}

bool CoreResultsDat::check_initialized()
{
  return is_initialized;
}

bool CoreResultsDat::read()
{
  bool success = false;
  if (ccx_uo.mConverterThreads > 1)
  {
    if (read_parallel())
    {
      success = true;
    }
  }else{
    if (read_single())
    {
      success = true;
    }
  }

  return success;
}

bool CoreResultsDat::read_single()
{
  StopWatch StopWatch;
  int maxlines = 0;
  int currentline = 0;
  std::string log;
  log = "reading results " + filepath + " for Job ID " + std::to_string(job_id) + " \n";
  PRINT_INFO("%s", log.c_str());

  std::string datline = "";
  std::vector<std::string> dat_array;
  
  std::ifstream dat;
  dat.open(this->filepath);

  // clear all data before reading and reset read mode
  this->clear();
  current_read_mode = 0;

  if (dat.is_open())
  {
    // scan file for number of lines
    progressbar->start(0,100,"Scanning Results dat");
    while (std::getline(dat,datline))
    { 
      ++maxlines;
      if(dat.eof()){
        break;
      }
    }
    progressbar->end();
    dat.close();
    dat.open(this->filepath);

    progressbar->start(0,100,"Reading Results DAT");
    t_start = std::chrono::high_resolution_clock::now();
    
    log = "";
    while (dat)
    {
      if ((!std::getline(dat,datline))||(dat.eof()))
      {
        break;
      }
      ++currentline;
  
      const auto t_end = std::chrono::high_resolution_clock::now();
      int duration = std::chrono::duration<double, std::milli>(t_end - t_start).count();
      if (duration > 500)
      {
        progressbar->percent(double(currentline)/double(maxlines));
        progressbar->check_interrupt();
        t_start = std::chrono::high_resolution_clock::now();
      }
      
      // if whitespace line, get next line until not a whitespace line
      while(this->is_whitespace(datline))
      {
        if ((!std::getline(dat,datline))||(dat.eof()))
        {
          break;
        }
        ++currentline;
      }

      dat_array = this->split_line(datline);
      
      //first lets check if the mode is still valid
      this->check_mode(dat_array);

      if (dat.eof())
      {
        break;
      }else if (current_read_mode == 1)
      {
        this->read_header(dat_array);
      } else if (current_read_mode == 2)
      {
        this->read_line(dat_array);
      } else if (current_read_mode == 10)
      {
        // do nothing here
      } else if (current_read_mode == 11)
      {
        this->header_emas(dat_array);
      } else if (current_read_mode == 102)
      {
        // Buckling, save data extra
        this->read_line_buckle(dat_array);
      }
      
      /*if (!this->is_number(dat_array[0]))
      {
        log="";
        for (size_t i = 0; i < dat_array.size(); i++)
        {
          log.append(std::to_string(current_read_mode) + "#");
          log.append(dat_array[i] + " ");
        }
        log.append("\n");
        PRINT_INFO("%s", log.c_str());
      }*/
      //ccx_iface->log_str(log);
    }
  }
  dat.close();
  progressbar->end();

  // for stress/strain data compute extra components
  progressbar->start(0,100,"Reading Results DAT: pre-defined calculations");
  t_start = std::chrono::high_resolution_clock::now();

  for (size_t i = 0; i < result_blocks.size(); i++)
  {
    //log = "i " + std::to_string(i) + " type '" + result_block_type[result_blocks[i][2]] + "'\n";
    //PRINT_INFO("%s", log.c_str());

    //stresses
    if (this->erase_whitespace(result_block_type[result_blocks[i][2]])=="stresses") 
    {
      // add components
      result_block_components[result_blocks[i][4]].push_back("mises");

      // compute values
      for (size_t ii = 0; ii < result_block_data[result_blocks[i][4]].size(); ii++)
      {
        result_block_data[result_blocks[i][4]][ii].push_back(ccx_iface->compute_von_mises_stress({
        result_block_data[result_blocks[i][4]][ii][2],
        result_block_data[result_blocks[i][4]][ii][3],
        result_block_data[result_blocks[i][4]][ii][4],
        result_block_data[result_blocks[i][4]][ii][5],
        result_block_data[result_blocks[i][4]][ii][6],
        result_block_data[result_blocks[i][4]][ii][7]}));
      }

      // add components
      result_block_components[result_blocks[i][4]].push_back("PS1");
      result_block_components[result_blocks[i][4]].push_back("PS2");
      result_block_components[result_blocks[i][4]].push_back("PS3");
      result_block_components[result_blocks[i][4]].push_back("worstPS");
      result_block_components[result_blocks[i][4]].push_back("maxShear");

      // compute values
      for (size_t ii = 0; ii < result_block_data[result_blocks[i][4]].size(); ii++)
      {
        std::vector<double> ps = ccx_iface->compute_principal_stresses({
        result_block_data[result_blocks[i][4]][ii][2],
        result_block_data[result_blocks[i][4]][ii][3],
        result_block_data[result_blocks[i][4]][ii][4],
        result_block_data[result_blocks[i][4]][ii][5],
        result_block_data[result_blocks[i][4]][ii][6],
        result_block_data[result_blocks[i][4]][ii][7]});

        result_block_data[result_blocks[i][4]][ii].push_back(ps[0]);
        result_block_data[result_blocks[i][4]][ii].push_back(ps[1]);
        result_block_data[result_blocks[i][4]][ii].push_back(ps[2]);
        result_block_data[result_blocks[i][4]][ii].push_back(ps[3]);
        result_block_data[result_blocks[i][4]][ii].push_back(0.5 * std::max({ps[0]-ps[2],ps[0]-ps[1],ps[1]-ps[2]}));
      }
    }

    //strains
    if (this->erase_whitespace(result_block_type[result_blocks[i][2]])=="strains") 
    {
      // add components
      result_block_components[result_blocks[i][4]].push_back("mises");

      // compute values      
      for (size_t ii = 0; ii < result_block_data[result_blocks[i][4]].size(); ii++)
      {
        result_block_data[result_blocks[i][4]][ii].push_back(ccx_iface->compute_von_mises_strain({
        result_block_data[result_blocks[i][4]][ii][2],
        result_block_data[result_blocks[i][4]][ii][3],
        result_block_data[result_blocks[i][4]][ii][4],
        result_block_data[result_blocks[i][4]][ii][5],
        result_block_data[result_blocks[i][4]][ii][6],
        result_block_data[result_blocks[i][4]][ii][7]}));
      }

      // add components
      result_block_components[result_blocks[i][4]].push_back("PE1");
      result_block_components[result_blocks[i][4]].push_back("PE2");
      result_block_components[result_blocks[i][4]].push_back("PE3");
      result_block_components[result_blocks[i][4]].push_back("worstPE");
      result_block_components[result_blocks[i][4]].push_back("maxShear");

      // compute values
      for (size_t ii = 0; ii < result_block_data[result_blocks[i][4]].size(); ii++)
      {
        std::vector<double> pe = ccx_iface->compute_principal_strains({
        result_block_data[result_blocks[i][4]][ii][2],
        result_block_data[result_blocks[i][4]][ii][3],
        result_block_data[result_blocks[i][4]][ii][4],
        result_block_data[result_blocks[i][4]][ii][5],
        result_block_data[result_blocks[i][4]][ii][6],
        result_block_data[result_blocks[i][4]][ii][7]});

        result_block_data[result_blocks[i][4]][ii].push_back(pe[0]);
        result_block_data[result_blocks[i][4]][ii].push_back(pe[1]);
        result_block_data[result_blocks[i][4]][ii].push_back(pe[2]);
        result_block_data[result_blocks[i][4]][ii].push_back(pe[3]);
        result_block_data[result_blocks[i][4]][ii].push_back(0.5 * std::max({pe[0]-pe[2],pe[0]-pe[1],pe[1]-pe[2]}));
      }
    }
     
    const auto t_end = std::chrono::high_resolution_clock::now();
    int duration = std::chrono::duration<double, std::milli>(t_end - t_start).count();
    if (duration > 500)
    {
      progressbar->percent(double(i+1)/double(result_blocks.size()));
      progressbar->check_interrupt();
      t_start = std::chrono::high_resolution_clock::now();
    }
  }

  this->check_element_sets();

  // sorting for faster search
  for (size_t i = 0; i < result_block_c1_data.size(); i++)
  {
    std::vector<int> tmp_c1;
    std::vector<int> tmp_result_block_c1_data_id;
    std::vector<int> tmp_result_block_c1_data_type;

    for (size_t ii = 0; ii < result_block_c1_data[i].size(); ii++)
    {
      tmp_c1.push_back(result_block_c1_data[i][ii][0]);
      tmp_result_block_c1_data_id.push_back(result_block_c1_data[i][ii][1]);
      tmp_result_block_c1_data_type.push_back(result_block_c1_data[i][ii][2]);
    }  
    auto p = sort_permutation(tmp_c1);
    this->apply_permutation(tmp_c1, p);
    this->apply_permutation(tmp_result_block_c1_data_id, p);
    this->apply_permutation(tmp_result_block_c1_data_type, p);
    sorted_c1.push_back(tmp_c1);
    sorted_result_block_c1_data_id.push_back(tmp_result_block_c1_data_id);
    sorted_result_block_c1_data_type.push_back(tmp_result_block_c1_data_type);
  }

  progressbar->end();

  //PRINT_INFO("%s", log.c_str());
  //print_data();

  StopWatch.total("Duration of reading DAT [ms]: ");

  return true;
}

bool CoreResultsDat::read_parallel()
{
  StopWatch StopWatch;
  int max_threads = ccx_uo.mConverterThreads;
  std::vector<std::thread> ReadThreads; // vector to contain threads for reading frd
  int maxlines = 0;
  int currentline = 0;
  std::string log;
  log = "reading results " + filepath + " for Job ID " + std::to_string(job_id) + " \n";
  PRINT_INFO("%s", log.c_str());

  std::string datline = "";
  std::vector<std::string> dat_array;
  
  std::ifstream dat;
  dat.open(this->filepath);

  // clear all data before reading and reset read mode
  this->clear();
  current_read_mode = 0;

  if (dat.is_open())
  {
    // scan file for number of lines
    progressbar->start(0,100,"Scanning Results dat");
    while (std::getline(dat,datline))
    { 
      ++maxlines;
      if(dat.eof()){
        break;
      }
    }
    progressbar->end();
    dat.close();
    dat.open(this->filepath);

    progressbar->start(0,100,"Reading Result Headers DAT");
    t_start = std::chrono::high_resolution_clock::now();
    
    log = "";
    while (dat)
    {
      if ((!std::getline(dat,datline))||(dat.eof()))
      {
        break;
      }
      ++currentline;
  
      const auto t_end = std::chrono::high_resolution_clock::now();
      int duration = std::chrono::duration<double, std::milli>(t_end - t_start).count();
      if (duration > 500)
      {
        progressbar->percent(double(currentline)/double(maxlines));
        progressbar->check_interrupt();
        t_start = std::chrono::high_resolution_clock::now();
      }
      
      // if whitespace line, get next line until not a whitespace line
      while(this->is_whitespace(datline))
      {
        if ((!std::getline(dat,datline))||(dat.eof()))
        {
          break;
        }
        ++currentline;
      }

      dat_array = this->split_line(datline);
      int current_block_data_id = result_blocks.size()-1;
      
      //first lets check if the mode is still valid
      this->check_mode(dat_array);

      if (dat.eof())
      {
        break;
      }else if (current_read_mode == 1)
      {
        this->read_header(dat_array);
      } else if (current_read_mode == 2)
      {
        //this->read_line(dat_array);
        this->dat_arrays[current_block_data_id].push_back(dat_array);
      } else if (current_read_mode == 10)
      {
        // do nothing here
      } else if (current_read_mode == 11)
      {
        this->header_emas(dat_array);
      } else if (current_read_mode == 102)
      {
        // Buckling, save data extra
        this->read_line_buckle(dat_array);
      }
    }
  }
  dat.close();
  progressbar->end();

  // processing data lines
  /*
  for (size_t i = 0; i < dat_arrays.size(); i++)
  {
    this->read_lines_thread(i);
  }
  */
  progressbar->start(0,100,"Reading Result Blocks DAT");

  this->progress = std::vector<int>(max_threads + 1, 0);
  progress[max_threads] = get_result_block_lines(dat_arrays);

  int loop_c = 0;
  int number_of_result_blocks = dat_arrays.size();
  /*
  while (number_of_result_blocks > 0)
  {
    if (number_of_result_blocks > max_threads)
    {
      for (size_t i = 0; i < max_threads; i++)
      { 
        ReadThreads.push_back(std::thread(&CoreResultsDat::read_lines_thread, this,loop_c*max_threads+i,i));
      }
    }else{
      for (size_t i = 0; i < number_of_result_blocks; i++)
      { 
        ReadThreads.push_back(std::thread(&CoreResultsDat::read_lines_thread, this,loop_c*max_threads+i,i));
      }
    }
    // wait till all threads are finished
    int it=0;
    while (ReadThreads.size()>0)
    {
      if (ReadThreads[it].joinable())
      {
        ReadThreads[it].join();
        ReadThreads.erase(ReadThreads.begin() + it);
        number_of_result_blocks = number_of_result_blocks - 1;
        it=-1;
      }
      if (it==ReadThreads.size())
      {
        it=-1;
      }
      update_progressbar();
      ++it;
    }
    ++loop_c;
  }
  */

  ThreadPool tp;
  tp.start(max_threads);
  for (size_t i = 0; i < number_of_result_blocks; i++)
  {
      std::function<void()> f = std::bind(&CoreResultsDat::read_lines_thread, this,i,0);
      tp.queueJob(f);
  }
  while(tp.busy())
  {
    update_progressbar();
  }
  tp.stop();

  /*
  log = "result_blocks.size() " + std::to_string(result_blocks.size()) + "\n";
  PRINT_INFO("%s", log.c_str());
  log = "result_block_data.size() " + std::to_string(result_block_data.size()) + "\n";
  PRINT_INFO("%s", log.c_str());

  log = "number of blocks " + std::to_string(dat_arrays.size()) + "\n";
  PRINT_INFO("%s", log.c_str());

  */

  /*
  for (size_t i = 0; i < result_blocks.size(); i++)
  {    
    log = "block id " + std::to_string(i) + " data id " + std::to_string(result_blocks[i][4]) + "\n";
    PRINT_INFO("%s", log.c_str());
  }
  
  for (size_t i = 0; i < result_block_c1_data.size(); i++)
  {    
    //log = "block id " + std::to_string(i) + " type " + std::to_string(result_block_c1_data[i][0][2]) + "\n";
    log = "block id " + std::to_string(i) + " size " + std::to_string(result_block_c1_data[i].size()) + "\n";
    PRINT_INFO("%s", log.c_str());
  }
  */

  // for stress/strain data compute extra components
  
  progressbar->start(0,100,"Computing pre-defined calculations for Results DAT");
  
  this->progress = std::vector<int>(max_threads + 1, 0);
  progress[max_threads] = get_result_blocks_predefined();

  loop_c = 0;
  number_of_result_blocks = result_blocks.size();
  /*
  while (number_of_result_blocks > 0)
  {
    if (number_of_result_blocks > max_threads)
    {
      for (size_t i = 0; i < max_threads; i++)
      { 
        ReadThreads.push_back(std::thread(&CoreResultsDat::compute_predefined, this,loop_c*max_threads+i,i));
      }
    }else{
      for (size_t i = 0; i < number_of_result_blocks; i++)
      { 
        ReadThreads.push_back(std::thread(&CoreResultsDat::compute_predefined, this,loop_c*max_threads+i,i));
      }
    }
    // wait till all threads are finished
    int it=0;
    while (ReadThreads.size()>0)
    {
      if (ReadThreads[it].joinable())
      {
        ReadThreads[it].join();
        ReadThreads.erase(ReadThreads.begin() + it);
        number_of_result_blocks = number_of_result_blocks - 1;
        it=-1;
      }
      if (it==ReadThreads.size())
      {
        it=-1;
      }
      update_progressbar();
      ++it;
    }
    ++loop_c;
  }
  */

  ThreadPool tp2;
  tp2.start(max_threads);
  for (size_t i = 0; i < number_of_result_blocks; i++)
  {
      std::function<void()> f = std::bind(&CoreResultsDat::compute_predefined, this,i,0);
      tp2.queueJob(f);
  }
  while(tp2.busy())
  {
    update_progressbar();
  }
  tp2.stop();
  
  this->check_element_sets();

  // sorting for faster search
  loop_c = 0;
  number_of_result_blocks = result_block_c1_data.size();
  for (size_t i = 0; i < result_block_c1_data.size(); i++)
  {
    std::vector<int> tmp_c1;
    std::vector<int> tmp_result_block_c1_data_id;
    std::vector<int> tmp_result_block_c1_data_type;
    sorted_c1.push_back(tmp_c1);
    sorted_result_block_c1_data_id.push_back(tmp_result_block_c1_data_id);
    sorted_result_block_c1_data_type.push_back(tmp_result_block_c1_data_type);
  }

  while (number_of_result_blocks > 0)
  {
    if (number_of_result_blocks > max_threads)
    {
      for (size_t i = 0; i < max_threads; i++)
      { 
        ReadThreads.push_back(std::thread(&CoreResultsDat::sort_data, this,loop_c*max_threads+i));
      }
    }else{
      for (size_t i = 0; i < number_of_result_blocks; i++)
      { 
        ReadThreads.push_back(std::thread(&CoreResultsDat::sort_data, this,loop_c*max_threads+i));
      }
    }
    // wait till all threads are finished
    for (size_t i = 0; i < ReadThreads.size(); i++)
    { 
      ReadThreads[i].join();
    }
    number_of_result_blocks = number_of_result_blocks - ReadThreads.size();
    ++loop_c;
    ReadThreads.clear();
  }

  progressbar->end();
  
  //PRINT_INFO("%s", log.c_str());
  //print_data();

  StopWatch.total("Duration of reading DAT [ms]: ");

  return true;
}

std::vector<std::string> CoreResultsDat::split_line(std::string line)
{
  std::vector<std::string> str_array;
  std::string str_temp;

  // trim whitespaces
  size_t strBegin = line.find_first_not_of(" \t\r\f\v\n");
  if (strBegin != std::string::npos)
  {
    size_t strEnd = line.find_last_not_of(" \t\r\f\v\n");
    size_t strRange = strEnd - strBegin + 1;
    line = line.substr(strBegin, strRange);
  }
  // reduce whitespaces
  size_t beginSpace = line.find_first_of(" \t\r\f\v\n");
  while (beginSpace != std::string::npos)
  {
    size_t endSpace = line.find_first_not_of(" \t\r\f\v\n", beginSpace);
    size_t range = endSpace - beginSpace;

    line.replace(beginSpace,range, " ");
    size_t newStart = beginSpace + 1;
    beginSpace = line.find_first_of(" \t\r\f\v\n",newStart);
  }
  // insert whitespaces before "-" whitespaces but not "E-"
  beginSpace = line.find_first_of("-");
  while (beginSpace != std::string::npos)
  {
    size_t range = 1;
    if ((line[beginSpace-1] != 'E') && (line[beginSpace-1] != ' ') && (beginSpace !=0))
    {
      line.replace(beginSpace,range, " -");
    }
    size_t newStart = beginSpace + 2;
    beginSpace = line.find_first_of("-",newStart);
  }
  // insert whitespaces after "set" if there is none
  beginSpace = line.find("set");
  if (beginSpace != std::string::npos)
  {
    size_t range = 3;
    if (line[beginSpace+3] != ' ')
    {
      line.replace(beginSpace,range, "set ");
    }
  }
  // insert whitespaces before "for" if there is none
  beginSpace = line.find("for");
  if ((beginSpace != std::string::npos) && (beginSpace != 0))
  {
    size_t range = 3;
    if (line[beginSpace-1] != ' ')
    {
      line.replace(beginSpace,range, " for");
    }
  }

  std::stringstream ss(line);

  // split line with delimiter " "
  while (getline(ss,str_temp,' '))
  {
    str_array.push_back(str_temp);
  }
  
  return str_array;
}

bool CoreResultsDat::is_number(std::string number)
{
  for (size_t i = 0; i < number.length(); i++)
  {
    if (!std::isdigit(number[i]))
    {
      return false;
    }
  }
  return true;
}

bool CoreResultsDat::is_whitespace(std::string line)
{
  size_t strBegin = line.find_first_not_of(" \t\r\f\v\n");
  if (strBegin == std::string::npos)
  {
    return true;
  }
  return false;
}

std::string CoreResultsDat::erase_whitespace(std::string line)
{
  // reduce whitespaces
  size_t beginSpace = line.find_first_of(" \t\r\f\v\n");
  while (beginSpace != std::string::npos)
  {
    size_t endSpace = line.find_first_not_of(" \t\r\f\v\n", beginSpace);
    size_t range = endSpace - beginSpace;

    line.replace(beginSpace,range, "");
    size_t newStart = beginSpace + 1;
    beginSpace = line.find_first_of(" \t\r\f\v\n",newStart);
  }
  return line;
}

bool CoreResultsDat::check_mode(std::vector<std::string> line)
{
  if ((line[0] == "B")&&(line[1] == "U")) // Buckling!
  {
    current_read_mode = 10;
  } else if (line[0]=="MODE") // still buckling
  {
    current_read_mode = 10; 
  } else if (line[0]=="FACTOR") // still buckling
  {
    current_read_mode = 101;
  } else if (this->is_number(line[0]))
  {
    if (current_read_mode == 101) // read buckling data
    {
      current_read_mode = 102; // read buckling data lines
      // so we need to add a new data set that can be filled
      std::vector<std::vector<double>> buckle_data_tmp;
      this->buckle_data.push_back(buckle_data_tmp);
    }
    if ((current_read_mode != 10)&&(current_read_mode != 102)) // skip if should be skipped
    {
      current_read_mode = 2; // read data lines
    } 
  } else if (!this->is_number(line[0]))
  {
    if (line[0]=="mass")
    {
      current_read_mode = 11; // read header line for EMAS
      return  true;
    }
    for (size_t i = 0; i < line.size(); i++)
    {
      if (
        (line[i]=="contact")
      ||(line[i]=="statistics")
      ||(line[i]=="surface")
      ||(line[i]=="center")
      ||(line[i]=="shear")
      ||(line[i]=="total")
      //||(line[i]=="mass")
      ||(line[i]=="variables")
      )
      {
        current_read_mode = 10; // skip
        return  true;
      }
      if (line[i]=="set")
      {
        current_read_mode = 1; // read header line
        return  true;
      }
    } 
    current_read_mode = 10; // read header line
  }

  return true;
}

bool CoreResultsDat::read_header(std::vector<std::string> line)
{

  double total_time;
  std::string block_set;
  std::string block_type;
  int result_block_data_id;
  int result_block_type_data_id;
  int result_block_set_data_id;

  int search = -1;
  for (size_t i = 0; i < line.size(); i++)
  {
    if (line[i]=="set")
    {
      search = int(i);
    }
  } 
  block_set = line[search + 1];
  total_time = ccx_iface->string_scientific_to_double(line[line.size()-1]);
  total_times.push_back(total_time);
  current_total_time_id = int(total_times.size())-1;

  block_type = "";
  for (size_t i = 0; i < search-1; i++)
  {
    block_type.append(line[i]);
    if (i!=search-2)
    {
      block_type.append(" ");
    }
  }

  std::vector<std::string> tmp_result_block_components;
  // extract components if possible
  size_t beginSpace = block_type.find_first_of("(");
  if (beginSpace != std::string::npos)
  {  
    std::string str_comp = "";
    size_t endSpace = block_type.find_first_of(")", beginSpace);
    size_t range = endSpace - beginSpace + 1;
    str_comp = block_type.substr(beginSpace + 1,range-2);
    block_type.replace(beginSpace,range, "");

    str_comp = this->erase_whitespace(str_comp);

    std::stringstream ss(str_comp);
    std::string str_temp;
    // split line with delimiter ","
    while (getline(ss,str_temp,','))
    {
      tmp_result_block_components.push_back(str_temp);
    }
  }else{
    tmp_result_block_components.push_back(block_type);
  }
  // write new set of component names
  result_block_components.push_back(tmp_result_block_components);


  std::vector<std::vector<double>> tmp_result_block_data;
  std::vector<std::vector<int>> tmp_result_block_c1_data;
  result_block_data.push_back(tmp_result_block_data);
  result_block_c1_data.push_back(tmp_result_block_c1_data);
    
  current_result_block = int(result_blocks.size())-1;
  result_block_data_id = int(result_block_data.size())-1;
  result_block_type_data_id = this->get_current_result_block_type(block_type);
  result_block_set_data_id = this->get_current_result_block_set(block_set);
  
  result_blocks.push_back({current_result_block,current_total_time_id,result_block_type_data_id,result_block_set_data_id,result_block_data_id});
  dat_arrays.push_back({});
 
  return true;
}


bool CoreResultsDat::header_emas(std::vector<std::string> line)
{
  double total_time;
  std::string block_set;
  std::string block_type;
  int result_block_data_id;
  int result_block_type_data_id;
  int result_block_set_data_id;

  int search = -1;
  for (size_t i = 0; i < line.size(); i++)
  {
    if (line[i]=="set")
    {
      search = int(i);
    }
  } 
  block_set = line[search + 1];
  total_time = ccx_iface->string_scientific_to_double(line[line.size()-1],5);
  total_times.push_back(total_time);
  current_total_time_id = int(total_times.size())-1;

  block_type = "emas";
  std::vector<std::string> tmp_result_block_components;

  tmp_result_block_components.push_back("element");
  tmp_result_block_components.push_back("mass");
  tmp_result_block_components.push_back("xx");
  tmp_result_block_components.push_back("yy");
  tmp_result_block_components.push_back("zz");
  tmp_result_block_components.push_back("xy");
  tmp_result_block_components.push_back("xz");
  tmp_result_block_components.push_back("yz");

  // write new set of component names
  result_block_components.push_back(tmp_result_block_components);

  std::vector<std::vector<double>> tmp_result_block_data;
  std::vector<std::vector<int>> tmp_result_block_c1_data;
  result_block_data.push_back(tmp_result_block_data);
  result_block_c1_data.push_back(tmp_result_block_c1_data);
    
  current_result_block = int(result_blocks.size())-1;
  result_block_data_id = int(result_block_data.size())-1;
  result_block_type_data_id = this->get_current_result_block_type(block_type);
  result_block_set_data_id = this->get_current_result_block_set(block_set);
  
  result_blocks.push_back({current_result_block,current_total_time_id,result_block_type_data_id,result_block_set_data_id,result_block_data_id});
  dat_arrays.push_back({});

  return true;
}

bool CoreResultsDat::read_line(std::vector<std::string> line)
{
  bool bool_node;
  int c1_id;
  int c1_type;
  int n_comp = int(result_block_components[result_block_components.size()-1].size());
  
  if (n_comp == line.size()) // elemental results
  {
    bool_node = false;
    if (n_comp == 2)
    {
      c1_type = 3; // element data with no integration points
    }else if (result_block_type[result_blocks[result_blocks.size()-1][2]]=="emas")
    {
      c1_type = 3; // element data with no integration points
    }else{
      c1_type = 2;
    }
  } else {                   // nodal results
    bool_node = true;
    c1_type = 1;
    
    //check if last component really is a number, shells ... so random
    if (line[line.size()-1][0]=='_')
    {
      bool_node = false;
      c1_type = 2;
    }
  }
  
  std::vector<double> result_comp(n_comp);
  int result_block_c1_data_id = -1;

  c1_id = std::stoi(line[0]);

  for (size_t i = 0; i < n_comp; i++)
  {
    if (bool_node)
    {
      result_comp[i] = ccx_iface->string_scientific_to_double(line[i+1]);
    }else{
      result_comp[i] = ccx_iface->string_scientific_to_double(line[i]);
    }
  }
      
  result_block_data[result_block_data.size()-1].push_back(result_comp);
  result_block_c1_data_id = int(result_block_data[result_block_data.size()-1].size()-1);
  result_block_c1_data[result_block_c1_data.size()-1].push_back({c1_id,result_block_c1_data_id,c1_type});

  return true;
}

bool CoreResultsDat::read_line_buckle(std::vector<std::string> line)
{ 
  std::vector<double> result_comp(2);
  result_comp[0] = ccx_iface->string_scientific_to_double(line[0]); // mode no
  result_comp[1] = ccx_iface->string_scientific_to_double(line[1]); // buckling factor
  
  this->buckle_data[buckle_data.size()-1].push_back(result_comp);

  return true;
}

bool CoreResultsDat::read_lines_thread(int result_block_data_id, int thread_id)
{
  for (size_t ib = 0; ib < this->dat_arrays[result_block_data_id].size(); ib++)
  {
    std::vector<std::string> line = dat_arrays[result_block_data_id][ib];

    bool bool_node;
    int c1_id;
    int c1_type;
    int n_comp = int(result_block_components[result_block_data_id].size());
    
    if (n_comp == line.size()) // elemental results
    {
      bool_node = false;
      if (n_comp == 2)
      {
        c1_type = 3; // element data with no integration points
      }else if (result_block_type[result_blocks[result_block_data_id][2]]=="emas")
      {
        c1_type = 3; // element data with no integration points
      }else{
        c1_type = 2;
      }
    } else {                   // nodal results
      bool_node = true;
      c1_type = 1;
      
      //check if last component really is a number, shells ... so random
      if (line[line.size()-1][0]=='_')
      {
        bool_node = false;
        c1_type = 2;
      }
    }
    
    std::vector<double> result_comp(n_comp);
    int result_block_c1_data_id = -1;

    c1_id = std::stoi(line[0]);

    for (size_t i = 0; i < n_comp; i++)
    {
      if (bool_node)
      {
        result_comp[i] = ccx_iface->string_scientific_to_double(line[i+1]);
      }else{
        result_comp[i] = ccx_iface->string_scientific_to_double(line[i]);
      }
    }
        
    result_block_data[result_block_data_id].push_back(result_comp);
    result_block_c1_data_id = int(result_block_data[result_block_data_id].size()-1);
    result_block_c1_data[result_block_data_id].push_back({c1_id,result_block_c1_data_id,c1_type});
    
    this->progress[thread_id] = this->progress[thread_id] + 1;
  }
  
  
  return true;
}

bool CoreResultsDat::compute_predefined(int result_block_data_id, int thread_id)
{
  int i = result_block_data_id;

  //stresses
  if (this->erase_whitespace(result_block_type[result_blocks[i][2]])=="stresses") 
  {
    // add components
    result_block_components[result_blocks[i][4]].push_back("mises");

    // compute values
    for (size_t ii = 0; ii < result_block_data[result_blocks[i][4]].size(); ii++)
    {
      result_block_data[result_blocks[i][4]][ii].push_back(ccx_iface->compute_von_mises_stress({
      result_block_data[result_blocks[i][4]][ii][2],
      result_block_data[result_blocks[i][4]][ii][3],
      result_block_data[result_blocks[i][4]][ii][4],
      result_block_data[result_blocks[i][4]][ii][5],
      result_block_data[result_blocks[i][4]][ii][6],
      result_block_data[result_blocks[i][4]][ii][7]}));
    }

    // add components
    result_block_components[result_blocks[i][4]].push_back("PS1");
    result_block_components[result_blocks[i][4]].push_back("PS2");
    result_block_components[result_blocks[i][4]].push_back("PS3");
    result_block_components[result_blocks[i][4]].push_back("worstPS");
    result_block_components[result_blocks[i][4]].push_back("maxShear");

    // compute values
    for (size_t ii = 0; ii < result_block_data[result_blocks[i][4]].size(); ii++)
    {
      std::vector<double> ps = ccx_iface->compute_principal_stresses({
      result_block_data[result_blocks[i][4]][ii][2],
      result_block_data[result_blocks[i][4]][ii][3],
      result_block_data[result_blocks[i][4]][ii][4],
      result_block_data[result_blocks[i][4]][ii][5],
      result_block_data[result_blocks[i][4]][ii][6],
      result_block_data[result_blocks[i][4]][ii][7]});

      result_block_data[result_blocks[i][4]][ii].push_back(ps[0]);
      result_block_data[result_blocks[i][4]][ii].push_back(ps[1]);
      result_block_data[result_blocks[i][4]][ii].push_back(ps[2]);
      result_block_data[result_blocks[i][4]][ii].push_back(ps[3]);
      result_block_data[result_blocks[i][4]][ii].push_back(0.5 * std::max({ps[0]-ps[2],ps[0]-ps[1],ps[1]-ps[2]}));
    }
    this->progress[thread_id] = this->progress[thread_id] + 1;
  }

  //strains
  if (this->erase_whitespace(result_block_type[result_blocks[i][2]])=="strains") 
  {
    // add components
    result_block_components[result_blocks[i][4]].push_back("mises");

    // compute values      
    for (size_t ii = 0; ii < result_block_data[result_blocks[i][4]].size(); ii++)
    {
      result_block_data[result_blocks[i][4]][ii].push_back(ccx_iface->compute_von_mises_strain({
      result_block_data[result_blocks[i][4]][ii][2],
      result_block_data[result_blocks[i][4]][ii][3],
      result_block_data[result_blocks[i][4]][ii][4],
      result_block_data[result_blocks[i][4]][ii][5],
      result_block_data[result_blocks[i][4]][ii][6],
      result_block_data[result_blocks[i][4]][ii][7]}));
    }

    // add components
    result_block_components[result_blocks[i][4]].push_back("PE1");
    result_block_components[result_blocks[i][4]].push_back("PE2");
    result_block_components[result_blocks[i][4]].push_back("PE3");
    result_block_components[result_blocks[i][4]].push_back("worstPE");
    result_block_components[result_blocks[i][4]].push_back("maxShear");

    // compute values
    for (size_t ii = 0; ii < result_block_data[result_blocks[i][4]].size(); ii++)
    {
      std::vector<double> pe = ccx_iface->compute_principal_strains({
      result_block_data[result_blocks[i][4]][ii][2],
      result_block_data[result_blocks[i][4]][ii][3],
      result_block_data[result_blocks[i][4]][ii][4],
      result_block_data[result_blocks[i][4]][ii][5],
      result_block_data[result_blocks[i][4]][ii][6],
      result_block_data[result_blocks[i][4]][ii][7]});

      result_block_data[result_blocks[i][4]][ii].push_back(pe[0]);
      result_block_data[result_blocks[i][4]][ii].push_back(pe[1]);
      result_block_data[result_blocks[i][4]][ii].push_back(pe[2]);
      result_block_data[result_blocks[i][4]][ii].push_back(pe[3]);
      result_block_data[result_blocks[i][4]][ii].push_back(0.5 * std::max({pe[0]-pe[2],pe[0]-pe[1],pe[1]-pe[2]}));
    }
    this->progress[thread_id] = this->progress[thread_id] + 1;
  }

  return true;
}

int CoreResultsDat::get_current_result_block_type(std::string result_type)
{

  for (size_t i = 0; i < result_block_type.size(); i++)
  {
    if (result_block_type[i]==result_type)
    {
      return int(i);
    }
  }
  result_block_type.push_back(result_type);
  int data_id = int(result_block_type.size())-1;
  
  return data_id;
}

int CoreResultsDat::get_current_result_block_set(std::string result_set)
{
  int data_id = -1;
  for (size_t i = 0; i < result_block_set.size(); i++)
  {
    if (result_block_set[i]==result_set)
    {
      return int(i);
    }
  }
  result_block_set.push_back(result_set);
  data_id = int(result_block_set.size())-1;
  
  return data_id;
}

bool CoreResultsDat::check_element_sets()
{
  //change set name when there is integration point data
  
  for (size_t i = 0; i < result_blocks.size(); i++)
  {
    if (this->result_block_c1_data[result_blocks[i][4]][0][2] == 2)
    {
      result_blocks[i][3] = this->get_current_result_block_set("ip_" + result_block_set[result_blocks[i][3]]);
    }
  }
  
  //delete set name, if they are not used anymore
  bool unused;
  for (size_t i = 0; i < result_block_set.size(); i++)
  {
    unused = true;
    for (size_t ii = 0; ii < result_blocks.size(); ii++)
    {
      if (result_blocks[ii][3] == i)
      {
        unused = false;
      }
    }
    if (unused)
    {
      std::vector<std::string> set = result_block_set;

      result_block_set.erase(result_block_set.begin() + i);
      --i;

      //rewrite the set id in the blocks!!!
      for (size_t ii = 0; ii < result_blocks.size(); ii++)
      {
        result_blocks[ii][3] = this->get_current_result_block_set(set[result_blocks[ii][3]]);
      }
    }
  }
  return true;
}

std::vector<std::string> CoreResultsDat::get_result_block_components_from_result_block_type(std::string result_block_type)
{
  // on first match write out the components for the first matching result block
  std::vector<std::string> components;
  for (size_t i = 0; i < this->result_block_type.size(); i++)
  {
    if (this->result_block_type[i]==result_block_type)
    {
      components = this->result_block_components[i];
      return components;
    }
  }
  
  return components;
}

int CoreResultsDat::get_result_block_component_id(int result_block_type_id,std::string result_block_component)
{
  int component_id = -1;
  std::vector<std::string> components;
  components = get_result_block_components_from_result_block_type(this->result_block_type[result_block_type_id]);

  for (size_t i = 0; i < components.size(); i++)
  {
    if (components[i]==result_block_component)
    {
      component_id = int(i);
    }
  }
    
  return component_id;
}

int CoreResultsDat::get_result_block_type_data_id(std::string result_block_type)
{
  int result_block_type_data_id = -1;

  for (size_t i = 0; i < result_block_type.size(); i++)
  {
    if (this->result_block_type[i]==result_block_type)
    {
      result_block_type_data_id = int(i);
      return result_block_type_data_id;
    }
  }

  return result_block_type_data_id;
}

int CoreResultsDat::get_result_block_set_data_id(std::string result_block_set)
{
  int result_block_set_data_id = -1;

  for (size_t i = 0; i < result_block_set.size(); i++)
  {
    if (this->result_block_set[i]==result_block_set)
    {
      result_block_set_data_id = int(i);
      return result_block_set_data_id;
    }
  }

  return result_block_set_data_id;
}

bool CoreResultsDat::sort_data(int data_id)
{
  std::vector<int> tmp_c1;
  std::vector<int> tmp_result_block_c1_data_id;
  std::vector<int> tmp_result_block_c1_data_type;

  for (size_t i = 0; i < result_block_c1_data[data_id].size(); i++)
  {
    tmp_c1.push_back(result_block_c1_data[data_id][i][0]);
    tmp_result_block_c1_data_id.push_back(result_block_c1_data[data_id][i][1]);
    tmp_result_block_c1_data_type.push_back(result_block_c1_data[data_id][i][2]);
  }  
  auto p = sort_permutation(tmp_c1);
  this->apply_permutation(tmp_c1, p);
  this->apply_permutation(tmp_result_block_c1_data_id, p);
  this->apply_permutation(tmp_result_block_c1_data_type, p);
  sorted_c1[data_id] = tmp_c1;
  sorted_result_block_c1_data_id[data_id] = tmp_result_block_c1_data_id;
  sorted_result_block_c1_data_type[data_id] = tmp_result_block_c1_data_type;

  return true;
}

int CoreResultsDat::get_result_block_lines(std::vector<std::vector<std::vector<std::string>>> result_block_lines)
{
  int lines = 0;
  for (size_t i = 0; i < result_block_lines.size(); i++)
  {
    lines = lines + result_block_lines[i].size();
  }
  return lines;
}
int CoreResultsDat::get_result_blocks_predefined()
{
  int blocks = 0;
  for (size_t i = 0; i < result_blocks.size(); i++)
  {
    //stresses
    if ((this->erase_whitespace(result_block_type[result_blocks[i][2]])=="stresses")||(this->erase_whitespace(result_block_type[result_blocks[i][2]])=="strains")) 
    {
      ++blocks;
    }
  }
  return blocks;
}

void CoreResultsDat::update_progressbar()
{
  //std::string log;
  const auto t_end = std::chrono::high_resolution_clock::now();
  int duration = std::chrono::duration<double, std::milli>(t_end - t_start).count();
  if (duration > 500)
  {
    int part = 0;
    for (size_t i = 0; i < progress.size()-1; i++)
    {
      part += progress[i];
      
      //log = "thread " + std::to_string(i) + " lines " + std::to_string(progress[i]) + " \n";
      //PRINT_INFO("%s", log.c_str());
    }

    //log = "max lines " + std::to_string(progress[progress.size()-1]) + " \n";
    //PRINT_INFO("%s", log.c_str());

    progressbar->percent(double(part)/double(progress[progress.size()-1]));
    progressbar->check_interrupt();
    t_start = std::chrono::high_resolution_clock::now();
  }
}

bool CoreResultsDat::print_data()
{
  std::string log;
  log = "DAT DATA for Job ID " + std::to_string(job_id) + " \n";

  if (result_blocks.size()>0)
  {
    for (size_t i = 0; i < result_blocks.size(); i++)
    {
      log.append("result block " + std::to_string(result_blocks[i][0]) + " ## ");
      log.append("total time data id " + std::to_string(result_blocks[i][1]) + " ## ");
      log.append("result block type " + std::to_string(result_blocks[i][2]) + " ## ");
      log.append("result set type " + std::to_string(result_blocks[i][3]) + " ## ");
      log.append("result block data id " + std::to_string(result_blocks[i][4]) + " \n");
      
      log.append("total time " + std::to_string(total_times[result_blocks[i][1]]) + " \n");
      log.append("result block type " + result_block_type[result_blocks[i][2]] + " \n");
      log.append("result block set " + result_block_set[result_blocks[i][3]] + " \n");
      log.append("component names ");
      for (size_t ii = 0; ii < result_block_components[i].size(); ii++)
      {
        log.append(result_block_components[i][ii] + " ");
      }
      log.append("\n");

      for (size_t ii = result_block_c1_data[result_blocks[i][4]].size()-1; ii < result_block_c1_data[result_blocks[i][4]].size(); ii++)
      {
        log.append(std::to_string(result_block_c1_data[result_blocks[i][4]][ii][0]) + " ");
        log.append(std::to_string(result_block_c1_data[result_blocks[i][4]][ii][1]) + " ");
        log.append(std::to_string(result_block_c1_data[result_blocks[i][4]][ii][2]) + " ## ");
        for (size_t iii = 0; iii < result_block_components[i].size(); iii++)
        {
          log.append(ccx_iface->to_string_scientific(result_block_data[result_blocks[i][4]][ii][iii]) + " ");
        }
        log.append("\n");
      }
      
      log.append("\n");
    }
  }

  PRINT_INFO("%s", log.c_str());
  return true;
}


//sorting of vectors
template <typename T> 
std::vector<std::size_t> CoreResultsDat::sort_permutation(
    const std::vector<T>& vec)
{
    std::vector<std::size_t> p(vec.size());
    std::iota(p.begin(), p.end(), 0);
    std::sort(p.begin(), p.end(),
        [&](std::size_t i, std::size_t j){ return vec[i] < vec[j]; });

    return p;
}

template <typename T> 
void CoreResultsDat::apply_permutation(
    std::vector<T>& vec,
    const std::vector<std::size_t>& p)
{
    std::vector<bool> done(vec.size());
    for (std::size_t i = 0; i < vec.size(); ++i)
    {
        if (done[i])
        {
            continue;
        }
        done[i] = true;
        std::size_t prev_j = i;
        std::size_t j = p[i];
        while (i != j)
        {
            std::swap(vec[prev_j], vec[j]);
            done[j] = true;
            prev_j = j;
            j = p[j];
        }
    }
}