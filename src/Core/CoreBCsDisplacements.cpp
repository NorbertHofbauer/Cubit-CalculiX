#include "CoreBCsDisplacements.hpp"
#include "CubitInterface.hpp"
#include "CalculiXCoreInterface.hpp"

CoreBCsDisplacements::CoreBCsDisplacements()
{}

CoreBCsDisplacements::~CoreBCsDisplacements()
{}

bool CoreBCsDisplacements::init()
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

bool CoreBCsDisplacements::update()
{ 
  // Get the list of bcs
  std::vector<int> bc_ids;
  int bc_id;
  int sub_id;
  int sub_last;
  int time_delay_id;
  bc_ids = CubitInterface::get_bc_id_list(CI_BCTYPE_DISPLACEMENT);	
  
  int bcs_data_id;
  bool erase_bc;

  // check for new bcs!

  for (size_t i = 0; i < bc_ids.size(); i++)
  {
    bc_id = bc_ids[i];
    bcs_data_id = get_bcs_data_id_from_bc_id(bc_id);
    if (bcs_data_id == -1)
    {
      // time delay
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
      this->add_time_delay(std::to_string(sub_id), "");

      add_bc(bc_id, 0 , -1, time_delay_id,0,0,0,0,0,0);
    }
  }

  // check if a bc changes id or is removed, this means we have erase all bcs in our bcs_data that cannot be connected anymore

  for (size_t i = bcs_data.size(); i > 0; i--)
  {
    erase_bc = true;
    for (size_t ii = 0; ii < bc_ids.size(); ii++)
    {
      bc_id = bc_ids[ii];
      if (bc_id == bcs_data[i-1][0])
      {
        erase_bc = false;
        break;
      }
    }
    if (erase_bc)
    {
      delete_bc(bcs_data[i-1][0]);
    }
  }

  return true;
}

bool CoreBCsDisplacements::reset()
{
  bcs_data.clear();
  time_delay_data.clear();
  init();
  return true;
}

bool CoreBCsDisplacements::check_initialized()
{
  return is_initialized;
}

bool CoreBCsDisplacements::add_bc(int bc_id, int op_mode, int amplitude_id, int time_delay_id, int fixed_dof_1, int fixed_dof_2, int fixed_dof_3, int fixed_dof_4, int fixed_dof_5, int fixed_dof_6)
{
  std::vector<int> v = {bc_id, op_mode, amplitude_id, time_delay_id, fixed_dof_1, fixed_dof_2, fixed_dof_3, fixed_dof_4, fixed_dof_5, fixed_dof_6};
      
  bcs_data.push_back(v);

  return true;
}

bool CoreBCsDisplacements::modify_bc(int bc_id, std::vector<std::string> options, std::vector<int> options_marker)
{
  int sub_data_id;
  std::vector<int> sub_data_ids;
  int bcs_data_id = get_bcs_data_id_from_bc_id(bc_id);
  
  if (bcs_data_id == -1)
  {
    return false;
  } else {
    // OP MODE
    if (options_marker[0]==1)
    {
      bcs_data[bcs_data_id][1] = std::stoi(options[0]);
    }
    // AMPLITUDE
    if (options_marker[1]==1)
    {
      bcs_data[bcs_data_id][2] = std::stoi(options[1]);
    }
    // time delay
    if (options_marker[2]==1)
    {
      sub_data_id = get_time_delay_data_id_from_time_delay_id(bcs_data[bcs_data_id][3]);
      time_delay_data[sub_data_id][1] = options[2];
    }
    // fixed dof 1
    if (options_marker[3]==1)
    {
      bcs_data[bcs_data_id][4] = std::stoi(options[3]);
    }
    // fixed dof 2
    if (options_marker[4]==1)
    {
      bcs_data[bcs_data_id][5] = std::stoi(options[4]);
    }
    // fixed dof 3
    if (options_marker[5]==1)
    {
      bcs_data[bcs_data_id][6] = std::stoi(options[5]);
    }
    // fixed dof 4
    if (options_marker[6]==1)
    {
      bcs_data[bcs_data_id][7] = std::stoi(options[6]);
    }
    // fixed dof 5
    if (options_marker[7]==1)
    {
      bcs_data[bcs_data_id][8] = std::stoi(options[7]);
    }
    // fixed dof 6
    if (options_marker[8]==1)
    {
      bcs_data[bcs_data_id][9] = std::stoi(options[8]);
    }

    return true;
  }
}

bool CoreBCsDisplacements::delete_bc(int bc_id)
{
  int sub_data_id;
  int bcs_data_id = get_bcs_data_id_from_bc_id(bc_id);
  if (bcs_data_id == -1)
  {
    return false;
  } else {
    // time delay
    sub_data_id = get_time_delay_data_id_from_time_delay_id(bcs_data[bcs_data_id][3]);
    if (sub_data_id != -1){
      time_delay_data.erase(time_delay_data.begin() + sub_data_id);
    }
    bcs_data.erase(bcs_data.begin() + bcs_data_id);
    return true;
  }
}

bool CoreBCsDisplacements::add_time_delay(std::string time_delay_id, std::string time_delay_value)
{
  std::vector<std::string> v = {time_delay_id, time_delay_value};
      
  time_delay_data.push_back(v);

  return true;
}

int CoreBCsDisplacements::get_bcs_data_id_from_bc_id(int bc_id)
{ 
  int return_int = -1;
  for (size_t i = 0; i < bcs_data.size(); i++)
  {
    if (bcs_data[i][0]==bc_id)
    {
        return_int = int(i);
    }  
  }
  return return_int;
}

int CoreBCsDisplacements::get_time_delay_data_id_from_time_delay_id(int time_delay_id)
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

std::string CoreBCsDisplacements::get_bc_parameter_export(int bc_id)
{
  int bc_data_id;
  int sub_data_id;
  std::string str_temp = "";
  bc_data_id = get_bcs_data_id_from_bc_id(bc_id);
  if (bcs_data[bc_data_id][1]==0)
  {
    //str_temp.append(",OP=MOD");
  }else if (bcs_data[bc_data_id][1]==1)
  {
    str_temp.append(",OP=NEW");
  }
  if (bcs_data[bc_data_id][2]!=-1)
  {
    str_temp.append(",AMPLITUDE=" + ccx_iface->get_amplitude_name(bcs_data[bc_data_id][2]));
  }
  sub_data_id = get_time_delay_data_id_from_time_delay_id(bcs_data[bc_data_id][3]);
  if (time_delay_data[sub_data_id][1]!="")
  {
    str_temp.append(",TIME DELAY=" + time_delay_data[sub_data_id][1]);
  }
  return str_temp;
}

std::string CoreBCsDisplacements::get_bc_parameter_fixed_export(int bc_id)
{
  int bc_data_id;
  int sub_data_id;
  std::string str_temp = "";
  bc_data_id = get_bcs_data_id_from_bc_id(bc_id);
  if (bcs_data[bc_data_id][1]==0)
  {
    //str_temp.append(",OP=MOD");
  }else if (bcs_data[bc_data_id][1]==1)
  {
    str_temp.append(",OP=NEW");
  }
  if (bcs_data[bc_data_id][2]!=-1)
  {
    str_temp.append(",AMPLITUDE=" + ccx_iface->get_amplitude_name(bcs_data[bc_data_id][2]));
  }
  sub_data_id = get_time_delay_data_id_from_time_delay_id(bcs_data[bc_data_id][3]);
  if (time_delay_data[sub_data_id][1]!="")
  {
    str_temp.append(",TIME DELAY=" + time_delay_data[sub_data_id][1]);
  }
  str_temp.append(",FIXED");
  return str_temp;
}

bool CoreBCsDisplacements::check_fixed(int bc_id)
{
  int bc_data_id;
  bc_data_id = get_bcs_data_id_from_bc_id(bc_id);
  if (bcs_data[bc_data_id][4]==1)
  { 
    return true;
  }else if (bcs_data[bc_data_id][5]==1)
  { 
    return true;
  }else if (bcs_data[bc_data_id][6]==1)
  { 
    return true;
  }else if (bcs_data[bc_data_id][7]==1)
  { 
    return true;
  }else if (bcs_data[bc_data_id][8]==1)
  { 
    return true;
  }else if (bcs_data[bc_data_id][9]==1)
  { 
    return true;
  }else{
    return false;
  }
}

bool CoreBCsDisplacements::check_dof_fixed(int bc_id, int dof)
{
  int bc_data_id;
  bc_data_id = get_bcs_data_id_from_bc_id(bc_id);
  if (bcs_data[bc_data_id][dof + 3]==1)
  { 
    return true;
  }else{
    return false;
  }
}

std::string CoreBCsDisplacements::print_data()
{
  std::string str_return;
  str_return = "\n CoreBCsDisplacements bcs_data: \n";
  str_return.append("bc_id, OP MODE, amplitude_id, time_delay_id, fixed dof 1, fixed dof 2, fixed dof 3, fixed dof 4, fixed dof 5, fixed dof 6 \n");

  for (size_t i = 0; i < bcs_data.size(); i++)
  {
    str_return.append(std::to_string(bcs_data[i][0]) + " " + std::to_string(bcs_data[i][1]) + " " + std::to_string(bcs_data[i][2]) + " " + std::to_string(bcs_data[i][3]) + " " + std::to_string(bcs_data[i][4]) + " " + std::to_string(bcs_data[i][5]) + " " + std::to_string(bcs_data[i][6]) + " " + std::to_string(bcs_data[i][7]) + " " + std::to_string(bcs_data[i][8]) + " " + std::to_string(bcs_data[i][9]) + " \n");
  }

  str_return.append("\n CoreBCsDisplacements time_delay_data: \n");
  str_return.append("time_delay_id, time_delay_value \n");

  for (size_t i = 0; i < time_delay_data.size(); i++)
  {
    str_return.append(time_delay_data[i][0] + " " + time_delay_data[i][1] + " \n");
  }
  
  return str_return;
}