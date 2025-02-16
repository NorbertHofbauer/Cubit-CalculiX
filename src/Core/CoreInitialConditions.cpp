#include "CoreInitialConditions.hpp"
#include "CubitInterface.hpp"
#include "CalculiXCoreInterface.hpp"

CoreInitialConditions::CoreInitialConditions()
{}

CoreInitialConditions::~CoreInitialConditions()
{}

bool CoreInitialConditions::init()
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

bool CoreInitialConditions::update()
{ 
  return true;
}

bool CoreInitialConditions::reset()
{
  initialconditions_data.clear();
  displacement_data.clear();
  temperature_data.clear();
  stress_data.clear();
  stress_element_data.clear();
  stress_block_data.clear();
  
  init();
  return true;
}

bool CoreInitialConditions::check_initialized()
{
  return is_initialized;
}

bool CoreInitialConditions::create_initialcondition(std::vector<std::string> options)
{
  int initialcondition_id;
  int initialcondition_last;
  int sub_id;
  int sub_last;
  int initialcondition_type;
  
  if (initialconditions_data.size()==0)
  {
    initialcondition_id = 1;
  }
  else
  {
    initialcondition_last = int(initialconditions_data.size()) - 1;
    initialcondition_id = initialconditions_data[initialcondition_last][0] + 1;
  }
  
  // initialcondition_type
  initialcondition_type = std::stoi(options[0]);
  
  if (initialcondition_type == 1)
  {  // displacement
    if (displacement_data.size()==0)
    {
      sub_id = 1;
    }
    else
    {
      sub_last = int(displacement_data.size()) - 1;
      sub_id = std::stoi(displacement_data[sub_last][0]) + 1;
    }
    this->add_displacement(std::to_string(sub_id));
  }else if (initialcondition_type == 2)
  { // temperature
    if (temperature_data.size()==0)
    {
      sub_id = 1;
    }
    else
    {
      sub_last = int(temperature_data.size()) - 1;
      sub_id = std::stoi(temperature_data[sub_last][0]) + 1;
    }
    this->add_temperature(std::to_string(sub_id));
  }else if (initialcondition_type == 3)
  { // stress
    if (temperature_data.size()==0)
    {
      sub_id = 1;
    }
    else
    {
      sub_last = int(stress_data.size()) - 1;
      sub_id = stress_data[sub_last] + 1;
    }
    this->add_stress(sub_id);
  }
  
  this->add_initialcondition(initialcondition_id, initialcondition_type, sub_id);
  return true;
}

bool CoreInitialConditions::modify_initialcondition(int initialcondition_id, int modify_type, std::vector<std::string> options, std::vector<int> options_marker)
{
  int sub_data_id;
  int initialconditions_data_id = get_initialconditions_data_id_from_initialcondition_id(initialcondition_id);

  if (initialconditions_data_id == -1)
  {
    return false;
  } else {
    // displacement
    if ((initialconditions_data[initialconditions_data_id][1]==1) && (initialconditions_data[initialconditions_data_id][1]==modify_type))
    {
      sub_data_id = get_displacement_data_id_from_displacement_id(initialconditions_data[initialconditions_data_id][2]);
      for (size_t i = 0; i < options.size(); i++)
      {
        if (options_marker[i]==1)
        {
          displacement_data[sub_data_id][i+1] = options[i];
        }
      }
    } else if ((initialconditions_data[initialconditions_data_id][1]==2) && (initialconditions_data[initialconditions_data_id][1]==modify_type))
    {
      sub_data_id = get_temperature_data_id_from_temperature_id(initialconditions_data[initialconditions_data_id][2]);
      for (size_t i = 0; i < options.size(); i++)
      {
        if (options_marker[i]==1)
        {
          temperature_data[sub_data_id][i+1] = options[i];
        }
      }
    }
    return true;
  }
}

bool CoreInitialConditions::add_initialcondition_stress(int initialcondition_id, int modify_type, std::vector<double> options)
{
  int sub_data_id;
  int initialconditions_data_id = get_initialconditions_data_id_from_initialcondition_id(initialcondition_id);

  if (initialconditions_data_id == -1)
  {
    return false;
  } else {
    // element
    if ((initialconditions_data[initialconditions_data_id][1]==3) && (modify_type==1))
    {
      this->add_stress_element(double(initialconditions_data[initialconditions_data_id][2]), options[0], options[1], options[2], options[3], options[4], options[5], options[6], options[7]);
    } else if ((initialconditions_data[initialconditions_data_id][1]==3) && (modify_type==2))
    {
      this->add_stress_block(double(initialconditions_data[initialconditions_data_id][2]), options[0], options[1], options[2], options[3], options[4], options[5], options[6]);
    }
    return true;
  }
}  

bool CoreInitialConditions::add_initialcondition(int initialcondition_id, int initialcondition_type, int initialcondition_type_id)
{
  std::vector<int> v = {initialcondition_id, initialcondition_type, initialcondition_type_id};
      
  initialconditions_data.push_back(v);

  return true;
}

bool CoreInitialConditions::add_displacement(std::string displacement_id)
{
  std::vector<std::string> v = {displacement_id,""};
  
  displacement_data.push_back(v);
  
  return true;
}

bool CoreInitialConditions::add_temperature(std::string temperature_id)
{
  std::vector<std::string> v = {temperature_id,""};
  
  temperature_data.push_back(v);
  
  return true;
}

bool CoreInitialConditions::add_stress(int stress_id)
{
  stress_data.push_back(stress_id);
  
  return true;
}

bool CoreInitialConditions::add_stress_element(double stress_id, double element_id, double ip, double sxx, double syy, double szz, double sxy, double sxz, double syz)
{
  std::vector<double> v = {stress_id, element_id, ip, sxx, syy, szz, sxy, sxz, syz};
  
  stress_element_data.push_back(v);
  
  return true;  
}

bool CoreInitialConditions::add_stress_block(double stress_id, double block_id, double sxx, double syy, double szz, double sxy, double sxz, double syz)
{
  std::vector<double> v = {stress_id, block_id, sxx, syy, szz, sxy, sxz, syz};
  
  stress_block_data.push_back(v);
  
  return true;  
}

bool CoreInitialConditions::delete_initialcondition(int initialcondition_id)
{
  int sub_data_id;
  std::vector<int> sub_data_ids;
  int initialconditions_data_id = get_initialconditions_data_id_from_initialcondition_id(initialcondition_id);
  if (initialconditions_data_id == -1)
  {
    return false;
  } else {
    if (initialconditions_data[initialconditions_data_id][1]==1)
    {
      sub_data_id = get_displacement_data_id_from_displacement_id(initialconditions_data[initialconditions_data_id][2]);
      if (sub_data_id != -1){
        displacement_data.erase(displacement_data.begin() + sub_data_id);  
      }
    }else if (initialconditions_data[initialconditions_data_id][1]==2)
    {
      sub_data_id = get_temperature_data_id_from_temperature_id(initialconditions_data[initialconditions_data_id][2]);
      if (sub_data_id != -1){
        temperature_data.erase(temperature_data.begin() + sub_data_id);  
      }
    }else if (initialconditions_data[initialconditions_data_id][1]==3)
    {
      sub_data_ids = get_stress_element_data_ids_from_stress_id(initialconditions_data[initialconditions_data_id][2]);
      for (size_t i = sub_data_ids.size(); i > 0; i--)
      {
        stress_element_data.erase(stress_element_data.begin() + sub_data_ids[i-1]);
      }
      sub_data_ids = get_stress_block_data_ids_from_stress_id(initialconditions_data[initialconditions_data_id][2]);
      for (size_t i = sub_data_ids.size(); i > 0; i--)
      {
        stress_block_data.erase(stress_block_data.begin() + sub_data_ids[i-1]);
      }
      sub_data_id = get_stress_data_id_from_stress_id(initialconditions_data[initialconditions_data_id][2]);
      if (sub_data_id != -1){
        stress_data.erase(stress_data.begin() + sub_data_id);  
      }
    }
    initialconditions_data.erase(initialconditions_data.begin() + initialconditions_data_id);
    return true;
  }
}

int CoreInitialConditions::get_initialconditions_data_id_from_initialcondition_id(int initialcondition_id)
{ 
  int return_int = -1;
  for (size_t i = 0; i < initialconditions_data.size(); i++)
  {
    if (initialconditions_data[i][0]==initialcondition_id)
    {
        return_int = int(i);
    }  
  }
  return return_int;
}

int CoreInitialConditions::get_displacement_data_id_from_displacement_id(int displacement_id)
{ 
  int return_int = -1;
  for (size_t i = 0; i < displacement_data.size(); i++)
  {
    if (displacement_data[i][0]==std::to_string(displacement_id))
    {
        return_int = int(i);
    }  
  }
  return return_int;
}

int CoreInitialConditions::get_temperature_data_id_from_temperature_id(int temperature_id)
{ 
  int return_int = -1;
  for (size_t i = 0; i < temperature_data.size(); i++)
  {
    if (temperature_data[i][0]==std::to_string(temperature_id))
    {
        return_int = int(i);
    }  
  }
  return return_int;
}

int CoreInitialConditions::get_stress_data_id_from_stress_id(int stress_id)
{ 
  int return_int = -1;
  for (size_t i = 0; i < stress_data.size(); i++)
  {
    if (stress_data[i]==stress_id)
    {
        return_int = int(i);
    }  
  }
  return return_int;
}

std::vector<int> CoreInitialConditions::get_stress_element_data_ids_from_stress_id(int stress_id)
{ 
  std::vector<int> return_int;

  for (size_t i = 0; i < stress_element_data.size(); i++)
  {
    if (stress_element_data[i][0]==double(stress_id))
    {
        return_int.push_back(int(i));
    }  
  }
  
  return return_int;
}

std::vector<int> CoreInitialConditions::get_stress_block_data_ids_from_stress_id(int stress_id)
{ 
  std::vector<int> return_int;

  for (size_t i = 0; i < stress_block_data.size(); i++)
  {
    if (stress_block_data[i][0]==double(stress_id))
    {
        return_int.push_back(int(i));
    }  
  }
  
  return return_int;
}

std::string CoreInitialConditions::print_data()
{
  std::string str_return;
  str_return = "\n CoreInitialConditions initialconditions_data: \n";
  str_return.append("initialcondition_id, initialcondition_type, initialcondition_type_id \n");

  for (size_t i = 0; i < initialconditions_data.size(); i++)
  {
    str_return.append(std::to_string(initialconditions_data[i][0]) + " " + std::to_string(initialconditions_data[i][1]) + " " + std::to_string(initialconditions_data[i][2]) + " \n");
  }

  str_return.append("\n CoreInitialConditions displacement_data: \n");
  str_return.append("displacement_id, bc_displacement_id \n");

  for (size_t i = 0; i < displacement_data.size(); i++)
  {
    str_return.append(displacement_data[i][0] + " " + displacement_data[i][1] + " \n");
  }
  
  str_return.append("\n CoreInitialConditions temperature_data: \n");
  str_return.append("temperature_id, bc_temperature_id \n");

  for (size_t i = 0; i < temperature_data.size(); i++)
  {
    str_return.append(temperature_data[i][0] + " " + temperature_data[i][1] + " \n");
  }

  str_return.append("\n CoreInitialConditions stress_data: \n");
  str_return.append("stress_id \n");

  for (size_t i = 0; i < stress_data.size(); i++)
  {
    str_return.append(std::to_string(stress_data[i]) + " \n");
  }

  str_return.append("\n CoreInitialConditions stress_element_data: \n");
  str_return.append("stress_id, element_id, ip, sxx, syy, szz, sxy, sxz, syz \n");

  for (size_t i = 0; i < stress_element_data.size(); i++)
  {
    for (size_t ii = 0; ii < stress_element_data[i].size(); ii++)
    {
      str_return.append(std::to_string(stress_element_data[i][ii]) + ",");
    }
    str_return.append(" \n");
  }

  str_return.append("\n CoreInitialConditions stress_block_data: \n");
  str_return.append("stress_id, block_id, sxx, syy, szz, sxy, sxz, syz \n");

  for (size_t i = 0; i < stress_block_data.size(); i++)
  {
    for (size_t ii = 0; ii < stress_block_data[i].size(); ii++)
    {
      str_return.append(std::to_string(stress_block_data[i][ii]) + ",");
    }
    str_return.append(" \n");
  }

  return str_return;
}