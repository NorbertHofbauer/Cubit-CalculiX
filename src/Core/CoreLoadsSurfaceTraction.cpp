#include "CoreLoadsSurfaceTraction.hpp"
#include "CubitInterface.hpp"
#include "CalculiXCoreInterface.hpp"

CoreLoadsSurfaceTraction::CoreLoadsSurfaceTraction()
{}

CoreLoadsSurfaceTraction::~CoreLoadsSurfaceTraction()
{}

bool CoreLoadsSurfaceTraction::init()
{
  if (is_initialized)
  {
    return false; // already initialized
  }else{
    CalculiXCoreInterface *ccx_iface = new CalculiXCoreInterface();
    is_initialized = true;  
    return true;
  }
}

bool CoreLoadsSurfaceTraction::update()
{ 
  return true;
}

bool CoreLoadsSurfaceTraction::reset()
{
  loads_data.clear();
  time_delay_data.clear();
  force_data.clear();
  name_data.clear();
  init();
  return true;
}

bool CoreLoadsSurfaceTraction::check_initialized()
{
  return is_initialized;
}

bool CoreLoadsSurfaceTraction::create_load(std::vector<std::string> options, std::vector<double> options2)
{
  int load_id;
  int load_last;
  int sub_id;
  int sub_last;
  int op_mode;
  int amplitude_id;
  int sideset_id;
  int time_delay_id;
  int force_id;
  int name_id;
  
  if (loads_data.size()==0)
  {
    load_id = 1;
  }
  else
  {
    load_last = int(loads_data.size()) - 1;
    load_id = loads_data[load_last][0] + 1;
  }

  // OP MODE
  op_mode = std::stoi(options[0]);
  
  // AMPLITUDE
  amplitude_id = std::stoi(options[1]);

  // time_delay
  if (time_delay_data.size()==0)
  {
    sub_id = 1;
  }
  else
  {
    sub_last = int(time_delay_data.size()) - 1;
    sub_id = std::stoi(time_delay_data[sub_last][0]) + 1;
  }
  time_delay_id = sub_id;
  this->add_time_delay(std::to_string(sub_id), options[2]);

  // SIDESET
  sideset_id = std::stoi(options[3]);
  
  // FORCES
  if (force_data.size()==0)
  {
    sub_id = 1;
  }
  else
  {
    sub_last = int(force_data.size()) - 1;
    sub_id = int(force_data[sub_last][0]) + 1;
  }
  force_id = sub_id;
  this->add_force(double(sub_id), options2[0], options2[1], options2[2]);

  // name
  if (name_data.size()==0)
  {
    sub_id = 1;
  }
  else
  {
    sub_last = int(name_data.size()) - 1;
    sub_id = std::stoi(name_data[sub_last][0]) + 1;
  }
  name_id = sub_id;
  this->add_name(std::to_string(sub_id), options[4]);

  this->add_load(load_id, op_mode, amplitude_id, time_delay_id, sideset_id, force_id, name_id);
  return true;
}

bool CoreLoadsSurfaceTraction::add_load(int load_id, int op_mode, int amplitude_id, int time_delay_id, int sideset_id, int force_id, int name_id)
{
  std::vector<int> v = {load_id, op_mode, amplitude_id, time_delay_id, sideset_id, force_id, name_id};
      
  loads_data.push_back(v);

  return true;
}

bool CoreLoadsSurfaceTraction::modify_load(int load_id, std::vector<std::string> options, std::vector<double> options2, std::vector<int> options_marker)
{
  int sub_data_id;
  std::vector<int> sub_data_ids;
  int loads_data_id = get_loads_data_id_from_load_id(load_id);
  
  if (loads_data_id == -1)
  {
    return false;
  } else {
    // OP MODE
    if (options_marker[0]==1)
    {
      loads_data[loads_data_id][1] = std::stoi(options[0]);
    }
    // AMPLITUDE
    if (options_marker[1]==1)
    {
      loads_data[loads_data_id][2] = std::stoi(options[1]);
    }
    // time delay
    if (options_marker[2]==1)
    {
      sub_data_id = get_time_delay_data_id_from_time_delay_id(loads_data[loads_data_id][3]);
      time_delay_data[sub_data_id][1] = options[2];
    }
    // SIDESET
    if (options_marker[3]==1)
    {
      loads_data[loads_data_id][4] = std::stoi(options[3]);
    }
    // FORCES
    if (options_marker[4]==1)
    {
      sub_data_id = get_force_data_id_from_force_id(loads_data[loads_data_id][5]);
      force_data[sub_data_id][1] = options2[0];
      force_data[sub_data_id][2] = options2[1];
      force_data[sub_data_id][3] = options2[2];
    }
    // name
    if (options_marker[5]==1)
    {
      sub_data_id = get_name_data_id_from_name_id(loads_data[loads_data_id][6]);
      name_data[sub_data_id][1] = options[4];
    }
    return true;
  }
}

bool CoreLoadsSurfaceTraction::delete_load(int load_id)
{
  int sub_data_id;
  int loads_data_id = get_loads_data_id_from_load_id(load_id);
  if (loads_data_id == -1)
  {
    return false;
  } else {
    // time delay
    sub_data_id = get_time_delay_data_id_from_time_delay_id(loads_data[loads_data_id][3]);
    if (sub_data_id != -1){
      time_delay_data.erase(time_delay_data.begin() + sub_data_id);
    }
    // forces
    sub_data_id = get_force_data_id_from_force_id(loads_data[loads_data_id][5]);
    if (sub_data_id != -1){
      force_data.erase(force_data.begin() + sub_data_id);
    }
    // name
    sub_data_id = get_name_data_id_from_name_id(loads_data[loads_data_id][6]);
    if (sub_data_id != -1){
      name_data.erase(name_data.begin() + sub_data_id);
    }

    loads_data.erase(loads_data.begin() + loads_data_id);
    return true;
  }
}

bool CoreLoadsSurfaceTraction::add_time_delay(std::string time_delay_id, std::string time_delay_value)
{
  std::vector<std::string> v = {time_delay_id, time_delay_value};
      
  time_delay_data.push_back(v);

  return true;
}

bool CoreLoadsSurfaceTraction::add_force(double force_id, double dof_1_value, double dof_2_value, double dof_3_value)
{
  std::vector<double> v = {force_id, dof_1_value, dof_2_value, dof_3_value};
      
  force_data.push_back(v);

  return true;
}

bool CoreLoadsSurfaceTraction::add_name(std::string name_id, std::string name)
{
  std::vector<std::string> v = {name_id, name};
  
  name_data.push_back(v);
  
  return true;
}

int CoreLoadsSurfaceTraction::get_loads_data_id_from_load_id(int load_id)
{ 
  int return_int = -1;
  for (size_t i = 0; i < loads_data.size(); i++)
  {
    if (loads_data[i][0]==load_id)
    {
        return_int = int(i);
    }  
  }
  return return_int;
}

int CoreLoadsSurfaceTraction::get_time_delay_data_id_from_time_delay_id(int time_delay_id)
{ 
  int return_int = -1;
  for (size_t i = 0; i < time_delay_data.size(); i++)
  {
    if (time_delay_data[i][0]==std::to_string(time_delay_id))
    {
        return_int = int(i);
    }  
  }
  return return_int;
}

int CoreLoadsSurfaceTraction::get_force_data_id_from_force_id(int temperature_id)
{ 
  int return_int = -1;
  for (size_t i = 0; i < force_data.size(); i++)
  {
    if (force_data[i][0]==double(temperature_id))
    {
        return_int = int(i);
    }  
  }
  return return_int;
}

int CoreLoadsSurfaceTraction::get_name_data_id_from_name_id(int name_id)
{ 
  int return_int = -1;
  for (size_t i = 0; i < name_data.size(); i++)
  {
    if (name_data[i][0]==std::to_string(name_id))
    {
        return_int = int(i);
    }  
  }
  return return_int;
}

std::string CoreLoadsSurfaceTraction::get_load_export(int load_id)
{
  int load_data_id;
  int sub_data_id;
  std::string str_temp = "*CLOAD";
  /*
  load_data_id = get_loads_data_id_from_load_id(load_id);
  if (loads_data[load_data_id][1]==0)
  {
    //str_temp.append(",OP=MOD");
  }else if (loads_data[load_data_id][1]==1)
  {
    str_temp.append(",OP=NEW");
  }
  if (loads_data[load_data_id][2]!=-1)
  {
    str_temp.append(",AMPLITUDE=" + ccx_iface->get_amplitude_name(loads_data[load_data_id][2]));
  }
  sub_data_id = get_time_delay_data_id_from_time_delay_id(loads_data[load_data_id][3]);
  if (time_delay_data[sub_data_id][1]!="")
  {
    str_temp.append(",TIME DELAY=" + time_delay_data[sub_data_id][1]);
  }
  if (loads_data[load_data_id][7]!=-1)
  {
    str_temp.append(",FILM AMPLITUDE=" + ccx_iface->get_amplitude_name(loads_data[load_data_id][7]));
  }
  sub_data_id = get_film_time_delay_data_id_from_film_time_delay_id(loads_data[load_data_id][8]);
  if (film_time_delay_data[sub_data_id][1]!="")
  {
    str_temp.append(",FILM TIME DELAY=" + film_time_delay_data[sub_data_id][1]);
  }
  //str_temp.append("\n");
  */

  return str_temp;
}

std::string CoreLoadsSurfaceTraction::print_data()
{
  std::string str_return;
  str_return = "\n CoreLoadsSurfaceTraction loads_data: \n";
  str_return.append("load_id, OP MODE, amplitude_id, time_delay_id, sideset_id, direction_id, magnitude_id,film_amplitude_id, film_time_delay_id,name \n");

  for (size_t i = 0; i < loads_data.size(); i++)
  {
    str_return.append(std::to_string(loads_data[i][0]) + " " + std::to_string(loads_data[i][1]) + " " + std::to_string(loads_data[i][2]) + " " + std::to_string(loads_data[i][3]) + " " + std::to_string(loads_data[i][4]) + " " + std::to_string(loads_data[i][5]) + " " + std::to_string(loads_data[i][6])  + " " + std::to_string(loads_data[i][7])  + " " + std::to_string(loads_data[i][8])  + " " + std::to_string(loads_data[i][9]) + " \n");
  }

  str_return.append("\n CoreLoadsSurfaceTraction time_delay_data: \n");
  str_return.append("time_delay_id, time_delay_value \n");

  for (size_t i = 0; i < time_delay_data.size(); i++)
  {
    str_return.append(time_delay_data[i][0] + " " + time_delay_data[i][1] + " \n");
  }

  str_return.append("\n CoreLoadsSurfaceTraction force_data: \n");
  str_return.append("force_id,dof_1_value,dof_2_value,dof_3_value  \n");

  for (size_t i = 0; i < force_data.size(); i++)
  {
    str_return.append(std::to_string(force_data[i][0]) + " " + std::to_string(force_data[i][1]) + " " + std::to_string(force_data[i][2]) + " " + std::to_string(force_data[i][3]) + " \n");
  }
  
  str_return.append("\n CoreLoadsSurfaceTraction name_data: \n");
  str_return.append("name_id, name \n");

  for (size_t i = 0; i < name_data.size(); i++)
  {
    str_return.append(name_data[i][0] + " " + name_data[i][1] + " \n");
  }

  return str_return;
}