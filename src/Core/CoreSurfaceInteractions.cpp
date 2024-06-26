#include "CoreSurfaceInteractions.hpp"
#include "CubitInterface.hpp"
#include "CalculiXCoreInterface.hpp"

CoreSurfaceInteractions::CoreSurfaceInteractions()
{}

CoreSurfaceInteractions::~CoreSurfaceInteractions()
{}

bool CoreSurfaceInteractions::init()
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

bool CoreSurfaceInteractions::update()
{ 
  return true;
}

bool CoreSurfaceInteractions::reset()
{
  surfaceinteractions_data.clear();
  surfaceinteraction_name_data.clear();
  exponential_surfacebehavior_data.clear();
  linear_surfacebehavior_data.clear();
  tabular_surfacebehavior_data.clear();
  tied_surfacebehavior_data.clear();
  gap_conductance_data.clear();
  gap_heat_generation_data.clear();
  friction_data.clear();

  init();
  return true;
}

bool CoreSurfaceInteractions::check_initialized()
{
  return is_initialized;
}

bool CoreSurfaceInteractions::create_surfaceinteraction(std::string surfacebehavior_type, std::vector<std::string> options, std::vector<std::vector<std::string>> options2)
{
  int surfaceinteraction_id;
  int surfaceinteraction_last;
  int surfaceinteraction_name_id;
  int surfaceinteraction_name_last;
  int surfacebehavior_type_value;
  int sub_surfacebehavior_id;
  int sub_surfacebehavior_last;

  if (surfacebehavior_type=="EXPONENTIAL")
  {
    if (exponential_surfacebehavior_data.size()==0)
    {
      sub_surfacebehavior_id = 1;
    }
    else
    {
      sub_surfacebehavior_last = int(exponential_surfacebehavior_data.size()) - 1;
      sub_surfacebehavior_id = std::stoi(exponential_surfacebehavior_data[sub_surfacebehavior_last][0]) + 1;
    }
    surfacebehavior_type_value = 1;
    this->add_exponential_surfacebehavior(std::to_string(sub_surfacebehavior_id), options[1], options[2]);
  } else if (surfacebehavior_type=="LINEAR")
  {
    if (linear_surfacebehavior_data.size()==0)
    {
      sub_surfacebehavior_id = 1;
    }
    else
    {
      sub_surfacebehavior_last = int(linear_surfacebehavior_data.size()) - 1;
      sub_surfacebehavior_id = std::stoi(linear_surfacebehavior_data[sub_surfacebehavior_last][0]) + 1;
    }
    surfacebehavior_type_value = 2;
    this->add_linear_surfacebehavior(std::to_string(sub_surfacebehavior_id), options[1], options[2], options[3]);
  } else if (surfacebehavior_type=="TABULAR")
  {
    if (tabular_surfacebehavior_data.size()==0)
    {
      sub_surfacebehavior_id = 1;
    }
    else
    {
      sub_surfacebehavior_id = 1;
      for (size_t i = 0; i < tabular_surfacebehavior_data.size(); i++)
      {
        sub_surfacebehavior_last = std::stoi(tabular_surfacebehavior_data[i][0]);
        if (sub_surfacebehavior_id < sub_surfacebehavior_last)
        {
          sub_surfacebehavior_id = sub_surfacebehavior_last;
        }
      }
      sub_surfacebehavior_id = sub_surfacebehavior_id + 1;
    }
    surfacebehavior_type_value = 3;
    for (size_t i = 0; i < options2.size(); i++)
    {
      this->add_tabular_surfacebehavior(std::to_string(sub_surfacebehavior_id), options2[i][0], options2[i][1]);
    }
  } else if (surfacebehavior_type=="TIED")
  {
    if (tied_surfacebehavior_data.size()==0)
    {
      sub_surfacebehavior_id = 1;
    }
    else
    {
      sub_surfacebehavior_last = int(tied_surfacebehavior_data.size()) - 1;
      sub_surfacebehavior_id = std::stoi(tied_surfacebehavior_data[sub_surfacebehavior_last][0]);
      sub_surfacebehavior_id = sub_surfacebehavior_id + 1;
    }
    surfacebehavior_type_value = 4;
    this->add_tied_surfacebehavior(std::to_string(sub_surfacebehavior_id), options[1]);
  } else if (surfacebehavior_type=="HARD")
  {
    sub_surfacebehavior_id = -1;
    surfacebehavior_type_value = 5;
  }

  if (surfaceinteraction_name_data.size()==0)
  {
    surfaceinteraction_name_id = 1;
  }
  else
  {
    surfaceinteraction_name_last = int(surfaceinteraction_name_data.size()) - 1;
    surfaceinteraction_name_id = std::stoi(surfaceinteraction_name_data[surfaceinteraction_name_last][0]) + 1;
  }
  this->add_name(std::to_string(surfaceinteraction_name_id),options[0]);

  if (surfaceinteractions_data.size()==0)
  {
    surfaceinteraction_id = 1;
  }
  else
  {
    surfaceinteraction_last = int(surfaceinteractions_data.size()) - 1;
    surfaceinteraction_id = surfaceinteractions_data[surfaceinteraction_last][0] + 1;
  }

  //this->add_surfaceinteraction(surfaceinteraction_id,surfaceinteraction_name_id,surfacebehavior_type,surfacebehavior_type_id,gap_conductance_id,gap_heat_generation_id,friction_id);
  
  this->add_surfaceinteraction(surfaceinteraction_id,surfaceinteraction_name_id,surfacebehavior_type_value,sub_surfacebehavior_id,-1,-1,-1);
  
  return true;
}

bool CoreSurfaceInteractions::modify_surfaceinteraction(std::string modify_type,int surfaceinteraction_id, std::vector<std::string> options, std::vector<int> options_marker, std::vector<std::vector<std::string>> options2)
{
  int modify_type_value;
  if (modify_type=="NAME")
  {
    modify_type_value = 0;
  }else if (modify_type=="EXPONENTIAL")
  {
    modify_type_value = 1;
  }else if (modify_type=="LINEAR")
  {
    modify_type_value = 2;
  }else if (modify_type=="TABULAR")
  {
    modify_type_value = 3;
  }else if (modify_type=="TIED")
  {
    modify_type_value = 4;
  }else if (modify_type=="HARD")
  {
    modify_type_value = 5;
  }else if (modify_type=="GAPCONDUCTANCE")
  {
    modify_type_value = 6;
  }else if (modify_type=="GAPHEATGENERATION")
  {
    modify_type_value = 7;
  }else if (modify_type=="FRICTION")
  {
    modify_type_value = 8;
  }

  int sub_data_id;
  int sub_data_last;
  std::vector<int> sub_data_ids;
  int surfaceinteractions_data_id = get_surfaceinteractions_data_id_from_surfaceinteraction_id(surfaceinteraction_id);
  
  if (surfaceinteractions_data_id == -1)
  {
    return false;
  } else {
    if (modify_type_value == 0) // modify name
    {
      sub_data_id = get_surfaceinteraction_name_data_id_from_surfaceinteraction_name_id(surfaceinteractions_data[surfaceinteractions_data_id][1]);
      for (size_t i = 0; i < options.size(); i++)
      {
        if (options_marker[i]==1)
        {
          surfaceinteraction_name_data[sub_data_id][1] = options[i];
        }
      }
      return true;
    }else if ((surfaceinteractions_data[surfaceinteractions_data_id][2]==1) && (surfaceinteractions_data[surfaceinteractions_data_id][2]==modify_type_value))
    {
      sub_data_id = get_exponential_surfacebehavior_data_id_from_exponential_surfacebehavior_id(surfaceinteractions_data[surfaceinteractions_data_id][3]);

      for (size_t i = 0; i < options.size(); i++)
      {
        if (options_marker[i]==1)
        {
          exponential_surfacebehavior_data[sub_data_id][i+1] = options[i];
        }
      }
      return true;
    }else if ((surfaceinteractions_data[surfaceinteractions_data_id][2]==2) && (surfaceinteractions_data[surfaceinteractions_data_id][2]==modify_type_value))
    {
      sub_data_id = get_linear_surfacebehavior_data_id_from_linear_surfacebehavior_id(surfaceinteractions_data[surfaceinteractions_data_id][3]);

      for (size_t i = 0; i < options.size(); i++)
      {
        if (options_marker[i]==1)
        {
          linear_surfacebehavior_data[sub_data_id][i+1] = options[i];
        }
      }
      return true;
    }else if ((surfaceinteractions_data[surfaceinteractions_data_id][2]==3) && (surfaceinteractions_data[surfaceinteractions_data_id][2]==modify_type_value))
    {
      sub_data_ids = get_tabular_surfacebehavior_data_ids_from_tabular_surfacebehavior_id(surfaceinteractions_data[surfaceinteractions_data_id][3]);

      if (options2.size()==sub_data_ids.size())
      {
        for (size_t i = 0; i < options2.size(); i++)
        {
          tabular_surfacebehavior_data[sub_data_ids[i]][0] = std::to_string(surfaceinteractions_data[surfaceinteractions_data_id][3]);
          tabular_surfacebehavior_data[sub_data_ids[i]][1] = options2[i][0];
          tabular_surfacebehavior_data[sub_data_ids[i]][2] = options2[i][1];
        }
      }else{
        // first delete and then make a push back
        // delete from back to begin so that we don't have to care about mismatching id's
        for (size_t i = sub_data_ids.size(); i > 0; i--)
        {
          tabular_surfacebehavior_data.erase(tabular_surfacebehavior_data.begin() + sub_data_ids[i-1]);
        }
        
        for (size_t i = 0; i < options2.size(); i++)
        {
          add_tabular_surfacebehavior(std::to_string(surfaceinteractions_data[surfaceinteractions_data_id][3]),options2[i][0],options2[i][1]);
        }
      }
      return true;
    }else if ((surfaceinteractions_data[surfaceinteractions_data_id][2]==4) && (surfaceinteractions_data[surfaceinteractions_data_id][2]==modify_type_value))
    {
      sub_data_id = get_tied_surfacebehavior_data_id_from_tied_surfacebehavior_id(surfaceinteractions_data[surfaceinteractions_data_id][3]);

      for (size_t i = 0; i < options.size(); i++)
      {
        if (options_marker[i]==1)
        {
          tied_surfacebehavior_data[sub_data_id][i+1] = options[i];
        }
      }
      return true;
    } // modify type 5 not needed to implement, right now...
    else if (modify_type_value == 6) // gap conductance
    {
      // check if already set, if not create
      sub_data_ids = get_gap_conductance_data_ids_from_gap_conductance_id(surfaceinteractions_data[surfaceinteractions_data_id][4]);
      if (sub_data_ids.size() == 0)
      { 
        if (gap_conductance_data.size()==0)
        {
          sub_data_id = 1;
        }else{
          sub_data_id = 1;
          for (size_t i = 0; i < gap_conductance_data.size(); i++)
          {
            sub_data_last = std::stoi(gap_conductance_data[i][0]);
            if (sub_data_id < sub_data_last)
            {
              sub_data_id = sub_data_last;
            }
          }
          sub_data_id = sub_data_id + 1;
        }
        surfaceinteractions_data[surfaceinteractions_data_id][4] = sub_data_id;
        for (size_t i = 0; i < options2.size(); i++)
        {
          add_gap_conductance(std::to_string(sub_data_id),options2[i][0],options2[i][1],options2[i][2]);
        }
      }else{
        if (options2.size()==sub_data_ids.size())
        {
          for (size_t i = 0; i < options2.size(); i++)
          {
            gap_conductance_data[sub_data_ids[i]][0] = std::to_string(surfaceinteractions_data[surfaceinteractions_data_id][4]);
            gap_conductance_data[sub_data_ids[i]][1] = options2[i][0];
            gap_conductance_data[sub_data_ids[i]][2] = options2[i][1];
            gap_conductance_data[sub_data_ids[i]][3] = options2[i][2];
          }
        }else{
          // first delete and then make a push back
          // delete from back to begin so that we don't have to care about mismatching id's
          for (size_t i = sub_data_ids.size(); i > 0; i--)
          {
            gap_conductance_data.erase(gap_conductance_data.begin() + sub_data_ids[i-1]);
          }
          for (size_t i = 0; i < options2.size(); i++)
          {
            add_gap_conductance(std::to_string(surfaceinteractions_data[surfaceinteractions_data_id][4]),options2[i][0],options2[i][1],options2[i][2]);
          }
        }
      }
      return true;
    }else if (modify_type_value == 7) // gap_heat_generation
    {
      // check if already set, if not create
      sub_data_id = get_gap_heat_generation_data_id_from_gap_heat_generation_id(surfaceinteractions_data[surfaceinteractions_data_id][5]);
      if (sub_data_id == -1)
      { 
        if (gap_heat_generation_data.size()==0)
        {
          sub_data_id = 1;
        }else{
          sub_data_id = 1;
          for (size_t i = 0; i < gap_heat_generation_data.size(); i++)
          {
            sub_data_last = std::stoi(gap_heat_generation_data[i][0]);
            if (sub_data_id < sub_data_last)
            {
              sub_data_id = sub_data_last;
            }
          }
          sub_data_id = sub_data_id + 1;
        }
        surfaceinteractions_data[surfaceinteractions_data_id][5] = sub_data_id;
        add_gap_heat_generation(std::to_string(sub_data_id), options[0], options[1], options[2]);
      }else{
        for (size_t i = 0; i < options.size(); i++)
        {
          if (options_marker[i]==1)
          {
            gap_heat_generation_data[sub_data_id][i+1] = options[i];
          }
        }
      }
      return true;
    }else if (modify_type_value == 8) // friction
    {
      // check if already set, if not create
      sub_data_id = get_friction_data_id_from_friction_id(surfaceinteractions_data[surfaceinteractions_data_id][6]);
      if (sub_data_id == -1)
      { 
        if (friction_data.size()==0)
        {
          sub_data_id = 1;
        }else{
          sub_data_id = 1;
          for (size_t i = 0; i < friction_data.size(); i++)
          {
            sub_data_last = std::stoi(friction_data[i][0]);
            if (sub_data_id < sub_data_last)
            {
              sub_data_id = sub_data_last;
            }
          }
          sub_data_id = sub_data_id + 1;
        }
        surfaceinteractions_data[surfaceinteractions_data_id][6] = sub_data_id;
        add_friction(std::to_string(sub_data_id), options[0], options[1]);
      }else{
        for (size_t i = 0; i < options.size(); i++)
        {
          if (options_marker[i]==1)
          {
            friction_data[sub_data_id][i+1] = options[i];
          }
        }
      }
      return true;
    }
    return false;
  }
}

bool CoreSurfaceInteractions::delete_surfaceinteraction(int surfaceinteraction_id)
{
  int sub_data_id;
  std::vector<int> sub_data_ids;
  int surfaceinteractions_data_id = get_surfaceinteractions_data_id_from_surfaceinteraction_id(surfaceinteraction_id);
  if (surfaceinteractions_data_id == -1)
  {
    return false;
  } else {
    // surface name
    sub_data_id = get_surfaceinteraction_name_data_id_from_surfaceinteraction_name_id(surfaceinteractions_data[surfaceinteractions_data_id][1]);
    surfaceinteraction_name_data.erase(surfaceinteraction_name_data.begin() + sub_data_id);
    // surface behavior
    if (surfaceinteractions_data[surfaceinteractions_data_id][2]==1)
    {
      sub_data_id = get_exponential_surfacebehavior_data_id_from_exponential_surfacebehavior_id(surfaceinteractions_data[surfaceinteractions_data_id][3]);
      exponential_surfacebehavior_data.erase(exponential_surfacebehavior_data.begin() + sub_data_id);  
    }else if (surfaceinteractions_data[surfaceinteractions_data_id][2]==2)
    {
      sub_data_id = get_linear_surfacebehavior_data_id_from_linear_surfacebehavior_id(surfaceinteractions_data[surfaceinteractions_data_id][3]);
      linear_surfacebehavior_data.erase(linear_surfacebehavior_data.begin() + sub_data_id);  
    }else if (surfaceinteractions_data[surfaceinteractions_data_id][2]==3)
    {
      sub_data_ids = get_tabular_surfacebehavior_data_ids_from_tabular_surfacebehavior_id(surfaceinteractions_data[surfaceinteractions_data_id][3]);
      for (size_t i = sub_data_ids.size(); i > 0; i--)
      {
        tabular_surfacebehavior_data.erase(tabular_surfacebehavior_data.begin() + sub_data_ids[i-1]);
      } 
    }else if (surfaceinteractions_data[surfaceinteractions_data_id][2]==4)
    {
      sub_data_id = get_tied_surfacebehavior_data_id_from_tied_surfacebehavior_id(surfaceinteractions_data[surfaceinteractions_data_id][3]);
      tied_surfacebehavior_data.erase(tied_surfacebehavior_data.begin() + sub_data_id);  
    } 
    // skip HARD
    // gap conductance
    if (surfaceinteractions_data[surfaceinteractions_data_id][4]!=-1)
    {
      sub_data_ids = get_gap_conductance_data_ids_from_gap_conductance_id(surfaceinteractions_data[surfaceinteractions_data_id][4]);
      for (size_t i = sub_data_ids.size(); i > 0; i--)
      {
        gap_conductance_data.erase(gap_conductance_data.begin() + sub_data_ids[i-1]);
      } 
    }
    // gap heat generation
    if (surfaceinteractions_data[surfaceinteractions_data_id][5]!=-1)
    {
      sub_data_id = get_gap_heat_generation_data_id_from_gap_heat_generation_id(surfaceinteractions_data[surfaceinteractions_data_id][5]);
      gap_heat_generation_data.erase(gap_heat_generation_data.begin() + sub_data_id);  
    }
    // friction
    if (surfaceinteractions_data[surfaceinteractions_data_id][6]!=-1)
    {
      sub_data_id = get_friction_data_id_from_friction_id(surfaceinteractions_data[surfaceinteractions_data_id][6]);
      friction_data.erase(friction_data.begin() + sub_data_id);  
    }

    surfaceinteractions_data.erase(surfaceinteractions_data.begin() + surfaceinteractions_data_id);
    return true;
  }
}

bool CoreSurfaceInteractions::add_surfaceinteraction(int surfaceinteraction_id, int surfaceinteraction_name_id, int surfacebehavior_type, int surfacebehavior_type_id, int gap_conductance_id, int gap_heat_generation_id, int friction_id)
{
  std::vector<int> v = {surfaceinteraction_id,surfaceinteraction_name_id,surfacebehavior_type,surfacebehavior_type_id,gap_conductance_id,gap_heat_generation_id,friction_id};
      
  surfaceinteractions_data.push_back(v);

  return true;
}

bool CoreSurfaceInteractions::add_name(std::string name_id, std::string name)
{
  std::vector<std::string> v = {name_id, name};
      
  surfaceinteraction_name_data.push_back(v);
  
  return true;
}

bool CoreSurfaceInteractions::add_exponential_surfacebehavior(std::string exponential_surfacebehavior_id, std::string constant_1, std::string constant_2)
{
  std::vector<std::string> v = {exponential_surfacebehavior_id, constant_1, constant_2};
      
  exponential_surfacebehavior_data.push_back(v);
  
  return true;
}

bool CoreSurfaceInteractions::add_linear_surfacebehavior(std::string linear_surfacebehavior_id, std::string constant_1, std::string constant_2, std::string constant_3)
{
  std::vector<std::string> v = {linear_surfacebehavior_id, constant_1, constant_2, constant_3};
      
  linear_surfacebehavior_data.push_back(v);
  
  return true;
}

bool CoreSurfaceInteractions::add_tabular_surfacebehavior(std::string tabular_surfacebehavior_id, std::string constant_1, std::string constant_2)
{
  std::vector<std::string> v = {tabular_surfacebehavior_id, constant_1, constant_2};
      
  tabular_surfacebehavior_data.push_back(v);
  
  return true;
}

bool CoreSurfaceInteractions::add_tied_surfacebehavior(std::string tied_surfacebehavior_id, std::string constant_1)
{
  std::vector<std::string> v = {tied_surfacebehavior_id, constant_1};
      
  tied_surfacebehavior_data.push_back(v);
  
  return true;
}

bool CoreSurfaceInteractions::add_gap_conductance(std::string gap_conductance_id, std::string constant_1, std::string constant_2, std::string constant_3)
{
  std::vector<std::string> v = {gap_conductance_id, constant_1, constant_2, constant_3};
      
  gap_conductance_data.push_back(v);
  
  return true;
}

bool CoreSurfaceInteractions::add_gap_heat_generation(std::string gap_heat_generation_id, std::string constant_1, std::string constant_2, std::string constant_3)
{
  std::vector<std::string> v = {gap_heat_generation_id, constant_1, constant_2, constant_3};
      
  gap_heat_generation_data.push_back(v);
  
  return true;
}

bool CoreSurfaceInteractions::add_friction(std::string friction_id, std::string constant_1, std::string constant_2)
{
  std::vector<std::string> v = {friction_id, constant_1, constant_2};
      
  friction_data.push_back(v);
  
  return true;
}


int CoreSurfaceInteractions::get_surfaceinteractions_data_id_from_surfaceinteraction_id(int surfaceinteraction_id)
{ 
  int return_int = -1;
  for (size_t i = 0; i < surfaceinteractions_data.size(); i++)
  {
    if (surfaceinteractions_data[i][0]==surfaceinteraction_id)
    {
        return_int = int(i);
    }  
  }
  return return_int;
}

int CoreSurfaceInteractions::get_surfaceinteraction_name_data_id_from_surfaceinteraction_name_id(int surfaceinteraction_name_id)
{ 
  int return_int = -1;
  for (size_t i = 0; i < surfaceinteraction_name_data.size(); i++)
  {
    if (surfaceinteraction_name_data[i][0]==std::to_string(surfaceinteraction_name_id))
    {
        return_int = int(i);
    }  
  }
  return return_int;
}

int CoreSurfaceInteractions::get_exponential_surfacebehavior_data_id_from_exponential_surfacebehavior_id(int exponential_surfacebehavior_id)
{ 
  int return_int = -1;
  for (size_t i = 0; i < exponential_surfacebehavior_data.size(); i++)
  {
    if (exponential_surfacebehavior_data[i][0]==std::to_string(exponential_surfacebehavior_id))
    {
        return_int = int(i);
    }  
  }
  return return_int;
}

int CoreSurfaceInteractions::get_linear_surfacebehavior_data_id_from_linear_surfacebehavior_id(int linear_surfacebehavior_id)
{ 
  int return_int = -1;
  for (size_t i = 0; i < linear_surfacebehavior_data.size(); i++)
  {
    if (linear_surfacebehavior_data[i][0]==std::to_string(linear_surfacebehavior_id))
    {
        return_int = int(i);
    }  
  }
  return return_int;
}

std::vector<int> CoreSurfaceInteractions::get_tabular_surfacebehavior_data_ids_from_tabular_surfacebehavior_id(int tabular_surfacebehavior_id)
{ 
  std::vector<int> return_int;
  for (size_t i = 0; i < tabular_surfacebehavior_data.size(); i++)
  {
    if (tabular_surfacebehavior_data[i][0]==std::to_string(tabular_surfacebehavior_id))
    {
        return_int.push_back(int(i));
    }  
  }
  return return_int;
}

int CoreSurfaceInteractions::get_tied_surfacebehavior_data_id_from_tied_surfacebehavior_id(int tied_surfacebehavior_id)
{ 
  int return_int = -1;
  for (size_t i = 0; i < tied_surfacebehavior_data.size(); i++)
  {
    if (tied_surfacebehavior_data[i][0]==std::to_string(tied_surfacebehavior_id))
    {
      return_int = int(i);
    }  
  }
  return return_int;
}

std::vector<int> CoreSurfaceInteractions::get_gap_conductance_data_ids_from_gap_conductance_id(int gap_conductance_id)
{ 
  std::vector<int> return_int;
  for (size_t i = 0; i < gap_conductance_data.size(); i++)
  {
    if (gap_conductance_data[i][0]==std::to_string(gap_conductance_id))
    {
      return_int.push_back(int(i));
    }  
  }
  return return_int;
}

int CoreSurfaceInteractions::get_gap_heat_generation_data_id_from_gap_heat_generation_id(int gap_heat_generation_id)
{ 
  int return_int = -1;
  for (size_t i = 0; i < gap_heat_generation_data.size(); i++)
  {
    if (gap_heat_generation_data[i][0]==std::to_string(gap_heat_generation_id))
    {
        return_int = int(i);
    }  
  }
  return return_int;
}

int CoreSurfaceInteractions::get_friction_data_id_from_friction_id(int friction_id)
{ 
  int return_int = -1;
  for (size_t i = 0; i < friction_data.size(); i++)
  {
    if (friction_data[i][0]==std::to_string(friction_id))
    {
        return_int = int(i);
    }  
  }
  return return_int;
}

std::string CoreSurfaceInteractions::get_surfaceinteraction_export() // get a list of the CalculiX surfaceinteractions exports
{
  std::vector<std::string> surfaceinteractions_export_list;
  surfaceinteractions_export_list.push_back("********************************** S U R F A C E I N T E R A C T I O N S ****************************");
  std::string str_temp;
  int sub_data_id;
  std::vector<int> sub_data_ids;
   
  //loop over all surface interactions
  for (size_t i = 0; i < surfaceinteractions_data.size(); i++)
  { 
    // CUSTOMLINE START
    std::vector<std::string> customline = ccx_iface->get_customline_data("BEFORE","SURFACEINTERACTION",surfaceinteractions_data[i][0]);
    for (size_t icl = 0; icl < customline.size(); icl++)
    {
      surfaceinteractions_export_list.push_back(customline[icl]);
    }
    // CUSTOMLINE END

    // NAME
    str_temp = "*SURFACE INTERACTION,NAME=";
    sub_data_id = get_surfaceinteraction_name_data_id_from_surfaceinteraction_name_id(surfaceinteractions_data[i][1]);
    str_temp.append(surfaceinteraction_name_data[sub_data_id][1]);
    surfaceinteractions_export_list.push_back(str_temp);
      
    // EXPONENTIAL
    if (surfaceinteractions_data[i][2] == 1) 
    {
      sub_data_id = get_exponential_surfacebehavior_data_id_from_exponential_surfacebehavior_id(surfaceinteractions_data[i][3]);
      str_temp = "*SURFACE BEHAVIOR,PRESSURE-OVERCLOSURE=EXPONENTIAL";
      surfaceinteractions_export_list.push_back(str_temp);
      // second line
      str_temp = "";
      str_temp.append(exponential_surfacebehavior_data[sub_data_id][1]);
      str_temp.append(",");
      str_temp.append(exponential_surfacebehavior_data[sub_data_id][2]);
      surfaceinteractions_export_list.push_back(str_temp);
    }
    // LINEAR
    if (surfaceinteractions_data[i][2] == 2) 
    {
      sub_data_id = get_linear_surfacebehavior_data_id_from_linear_surfacebehavior_id(surfaceinteractions_data[i][3]);
      str_temp = "*SURFACE BEHAVIOR,PRESSURE-OVERCLOSURE=LINEAR";
      surfaceinteractions_export_list.push_back(str_temp);
      // second line
      str_temp = "";
      str_temp.append(linear_surfacebehavior_data[sub_data_id][1]);
      str_temp.append(",");
      str_temp.append(linear_surfacebehavior_data[sub_data_id][2]);
      str_temp.append(",");
      str_temp.append(linear_surfacebehavior_data[sub_data_id][3]);
      surfaceinteractions_export_list.push_back(str_temp);
    }
    // TABULAR
    if (surfaceinteractions_data[i][2] == 3) 
    {
      sub_data_ids = get_tabular_surfacebehavior_data_ids_from_tabular_surfacebehavior_id(surfaceinteractions_data[i][3]);
      str_temp = "*SURFACE BEHAVIOR,PRESSURE-OVERCLOSURE=TABULAR";
      surfaceinteractions_export_list.push_back(str_temp);
      // second lines
      for (size_t i = 0; i < sub_data_ids.size(); i++)
      {
        str_temp = "";
        str_temp.append(tabular_surfacebehavior_data[sub_data_ids[i]][1]);
        str_temp.append(",");
        str_temp.append(tabular_surfacebehavior_data[sub_data_ids[i]][2]);
        surfaceinteractions_export_list.push_back(str_temp);
      }
    }
    // TIED
    if (surfaceinteractions_data[i][2] == 4) 
    {
      sub_data_id = get_tied_surfacebehavior_data_id_from_tied_surfacebehavior_id(surfaceinteractions_data[i][3]);
      str_temp = "*SURFACE BEHAVIOR,PRESSURE-OVERCLOSURE=TIED";
      surfaceinteractions_export_list.push_back(str_temp);
      // second line
      str_temp = "";
      str_temp.append(tied_surfacebehavior_data[sub_data_id][1]);
      surfaceinteractions_export_list.push_back(str_temp);
    }
    // HARD
    if (surfaceinteractions_data[i][2] == 5) 
    {
      str_temp = "*SURFACE BEHAVIOR,PRESSURE-OVERCLOSURE=HARD";
      surfaceinteractions_export_list.push_back(str_temp);
    }
    // GAP CONDUCTANCE
    if (surfaceinteractions_data[i][4] != -1) 
    {
      sub_data_ids = get_gap_conductance_data_ids_from_gap_conductance_id(surfaceinteractions_data[i][4]);
      str_temp = "*GAP CONDUCTANCE";
      surfaceinteractions_export_list.push_back(str_temp);
      // second lines
      for (size_t i = 0; i < sub_data_ids.size(); i++)
      {
        str_temp = "";
        str_temp.append(gap_conductance_data[sub_data_ids[i]][1]);
        str_temp.append(",");
        str_temp.append(gap_conductance_data[sub_data_ids[i]][2]);
        str_temp.append(",");
        str_temp.append(gap_conductance_data[sub_data_ids[i]][3]);
        surfaceinteractions_export_list.push_back(str_temp);
      }
    }
    // GAP HEAT GENERATION
    if (surfaceinteractions_data[i][5] != -1) 
    {
      sub_data_id = get_gap_heat_generation_data_id_from_gap_heat_generation_id(surfaceinteractions_data[i][5]);
      str_temp = "*GAP HEAT GENERATION";
      surfaceinteractions_export_list.push_back(str_temp);
      // second line
      str_temp = "";
      str_temp.append(gap_heat_generation_data[sub_data_id][1]);
      str_temp.append(",");
      str_temp.append(gap_heat_generation_data[sub_data_id][2]);
      str_temp.append(",");
      str_temp.append(gap_heat_generation_data[sub_data_id][3]);
      surfaceinteractions_export_list.push_back(str_temp);
    }
    // FRICTION
    if (surfaceinteractions_data[i][6] != -1) 
    {
      sub_data_id = get_friction_data_id_from_friction_id(surfaceinteractions_data[i][6]);
      str_temp = "*FRICTION";
      surfaceinteractions_export_list.push_back(str_temp);
      // second line
      str_temp = "";
      str_temp.append(friction_data[sub_data_id][1]);
      str_temp.append(",");
      str_temp.append(friction_data[sub_data_id][2]);
      surfaceinteractions_export_list.push_back(str_temp);
    }
    // CUSTOMLINE START
    customline = ccx_iface->get_customline_data("AFTER","SURFACEINTERACTION",surfaceinteractions_data[i][0]);
    for (size_t icl = 0; icl < customline.size(); icl++)
    {
      surfaceinteractions_export_list.push_back(customline[icl]);
    }
    // CUSTOMLINE END
  }
  
  std::string surfaceinteractions_export;

  for (size_t i = 0; i < surfaceinteractions_export_list.size(); i++)
  {
    surfaceinteractions_export.append(surfaceinteractions_export_list[i] + "\n");
  }
  
  return surfaceinteractions_export;
}


std::string CoreSurfaceInteractions::print_data()
{
  std::string str_return;
  str_return = "\n CoreSurfaceInteractions surfaceinteractions_data: \n";
  str_return.append("surfaceinteraction_id, surfaceinteraction_name_id, surfacebehavior_type, surfacebehavior_type_id, gap_conductance_id, gap_heat_generation_id, friction_id \n");

  for (size_t i = 0; i < surfaceinteractions_data.size(); i++)
  {
    str_return.append(std::to_string(surfaceinteractions_data[i][0]) + " " + std::to_string(surfaceinteractions_data[i][1]) + " " + std::to_string(surfaceinteractions_data[i][2])  + " " + std::to_string(surfaceinteractions_data[i][3])  + " " + std::to_string(surfaceinteractions_data[i][4])  + " " + std::to_string(surfaceinteractions_data[i][5])  + " " + std::to_string(surfaceinteractions_data[i][6]) + " \n");
  }

  str_return.append("\n CoreSurfaceInteractions surfaceinteraction_name_data: \n");
  str_return.append("name_id, name \n");

  for (size_t i = 0; i < surfaceinteraction_name_data.size(); i++)
  {
    str_return.append(surfaceinteraction_name_data[i][0] + " " + surfaceinteraction_name_data[i][1] + " \n");
  }

  str_return.append("\n CoreSurfaceInteractions exponential_surfacebehavior_data: \n");
  str_return.append("exponential_surfacebehavior_id, c0, p0 \n");
  
  for (size_t i = 0; i < exponential_surfacebehavior_data.size(); i++)
  {
    str_return.append(exponential_surfacebehavior_data[i][0] + " " + exponential_surfacebehavior_data[i][1] + " " + exponential_surfacebehavior_data[i][2] + " \n");
  }
  
  str_return.append("\n CoreSurfaceInteractions linear_surfacebehavior_data: \n");
  str_return.append("linear_surfacebehavior_id, slope K, sigma_inf, c0 \n");

  for (size_t i = 0; i < linear_surfacebehavior_data.size(); i++)
  {
    str_return.append(linear_surfacebehavior_data[i][0] + " " + linear_surfacebehavior_data[i][1] + " " + linear_surfacebehavior_data[i][2] + " " + linear_surfacebehavior_data[i][3] + " \n");
  }

  str_return.append("\n CoreSurfaceInteractions tabular_surfacebehavior_data: \n");
  str_return.append("tabular_surfacebehavior_id, pressure, overclosure \n");

  for (size_t i = 0; i < tabular_surfacebehavior_data.size(); i++)
  {
    str_return.append(tabular_surfacebehavior_data[i][0] + " " + tabular_surfacebehavior_data[i][1] + " " + tabular_surfacebehavior_data[i][2] + " \n");
  }

  str_return.append("\n CoreSurfaceInteractions tied_surfacebehavior_data: \n");
  str_return.append("tied_surfacebehavior_id, slope K \n");

  for (size_t i = 0; i < tied_surfacebehavior_data.size(); i++)
  {
    str_return.append(tied_surfacebehavior_data[i][0] + " " + tied_surfacebehavior_data[i][1] + " \n");
  }

  str_return.append("\n CoreSurfaceInteractions gap_conductance_data: \n");
  str_return.append("gap_conductance_id, Conductance, Contact Pressure, Temperature \n");

  for (size_t i = 0; i < gap_conductance_data.size(); i++)
  {
    str_return.append(gap_conductance_data[i][0] + " " + gap_conductance_data[i][1] + " " + gap_conductance_data[i][2] + " " + gap_conductance_data[i][3] + " \n");
  }

  str_return.append("\n CoreSurfaceInteractions gap_heat_generation_data: \n");
  str_return.append("gap_heat_generation_id, heat conversion factor, surface weighing factor, differential tangential velocity \n");

  for (size_t i = 0; i < gap_heat_generation_data.size(); i++)
  {
    str_return.append(gap_heat_generation_data[i][0] + " " + gap_heat_generation_data[i][1] + " " + gap_heat_generation_data[i][2] + " " + gap_heat_generation_data[i][3] + " \n");
  }

  str_return.append("\n CoreSurfaceInteractions friction_data: \n");
  str_return.append("friction_id, mu, lambda \n");

  for (size_t i = 0; i < friction_data.size(); i++)
  {
    str_return.append(friction_data[i][0] + " " + friction_data[i][1] + " " + friction_data[i][2] + " \n");
  }

  return str_return;
}