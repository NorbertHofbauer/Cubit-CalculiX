#include "ccxLoadsRadiationModifyCommand.hpp"
#include "CubitInterface.hpp"
#include "CubitMessage.hpp"
#include "CalculiXCoreInterface.hpp"

ccxLoadsRadiationModifyCommand::ccxLoadsRadiationModifyCommand()
{}

ccxLoadsRadiationModifyCommand::~ccxLoadsRadiationModifyCommand()
{}

std::vector<std::string> ccxLoadsRadiationModifyCommand::get_syntax()
{
  std::vector<std::string> syntax_list;

  std::string syntax = "ccx ";
  syntax.append("modify gravity <value:label='gravity id',help='<gravity id>'>");
  syntax.append("[magnitude <value:label='magnitude_value',help='<magnitude_value>'>] ");
  syntax.append("[block <value:label='block id',help='<block id>'>] ");
  syntax.append("[direction <value:label='x_value',help='<x_value>'> ");
  syntax.append("<value:label='y_value',help='<y_value>'> ");
  syntax.append("<value:label='z_value',help='<z_value>'>] ");
  syntax.append("[op {mod | new}] " );
  syntax.append("[amplitude <value:label='amplitude id',help='<amplitude id>'>] ");
  syntax.append("[timedelay <value:label='timedelay',help='<timedelay>'>] ");
  
  syntax_list.push_back(syntax);
  
  return syntax_list;
}

std::vector<std::string> ccxLoadsRadiationModifyCommand::get_syntax_help()
{
  std::vector<std::string> help(1);
  help[0] = "ccx "; 
  help[0].append("modify gravity <gravity_id> [magnitude <magnitude_value>] ");
  help[0].append("[block <block id>] ");
  help[0].append("[direction <x> <y> <z>] ");
  help[0].append("[op {mod | new}] " );
  help[0].append("[amplitude <amplitude id>] ");
  help[0].append("[timedelay <timedelay>] ");

  return help;
}

std::vector<std::string> ccxLoadsRadiationModifyCommand::get_help()
{
  std::vector<std::string> help;
  return help;
}

bool ccxLoadsRadiationModifyCommand::execute(CubitCommandData &data)
{
  CalculiXCoreInterface ccx_iface;

  std::string output;
  std::vector<int> options_marker;
  std::vector<std::string> options;
  int gravity_id;
  std::string block_id;
  int block_id_value;
  int op_mode = 0;
  std::string amplitude_id;
  int amplitude_value;
  std::string timedelay;
  double timedelay_value;
  double x_value;
  double y_value;
  double z_value;
  std::string x;
  std::string y;
  std::string z;
  double magnitude_value;
  std::string magnitude;
  
  data.get_value("gravity id", gravity_id);
  
  if (data.find_keyword("OP")){
    if (data.find_keyword("MOD")){
      options_marker.push_back(1);
      options.push_back("0");
    }else if (data.find_keyword("NEW"))
    {
      options_marker.push_back(1);
      options.push_back("1");
    }
  }else{
      options_marker.push_back(0);
      options.push_back("0");
  }

  if (!data.get_value("amplitude id", amplitude_value))
  {
    amplitude_id = "-1";
    options_marker.push_back(0);
  }
  else
  {
    amplitude_id = std::to_string(amplitude_value);
    options_marker.push_back(1);
  }
  options.push_back(amplitude_id);

  if (!data.get_value("timedelay", timedelay_value))
  {
    timedelay = "";
    options_marker.push_back(0);
  }
  else
  {
    timedelay = std::to_string(timedelay_value);
    options_marker.push_back(1);
  }
  options.push_back(timedelay);
  
  if (!data.get_value("block id", block_id_value))
  {
    amplitude_id = "-1";
    options_marker.push_back(0);
  }
  else
  {
    block_id = std::to_string(block_id_value);
    options_marker.push_back(1);
  }
  options.push_back(block_id);

  if (!data.get_value("x_value", x_value))
  {
    x = "-1";
    options_marker.push_back(0);
  }
  else
  {
    x = ccx_iface.to_string_scientific(x_value);
    options_marker.push_back(1);
  }
  options.push_back(x);

  if (!data.get_value("y_value", y_value))
  {
    y = "-1";
    options_marker.push_back(0);
  }
  else
  {
    y = ccx_iface.to_string_scientific(y_value);
    options_marker.push_back(1);
  }
  options.push_back(y);

  if (!data.get_value("z_value", z_value))
  {
    z = "-1";
    options_marker.push_back(0);
  }
  else
  {
    z = ccx_iface.to_string_scientific(z_value);
    options_marker.push_back(1);
  }
  options.push_back(z);

  if (!data.get_value("magnitude_value", magnitude_value))
  {
    magnitude = "-1";
    options_marker.push_back(0);
  }
  else
  {
    magnitude = ccx_iface.to_string_scientific(magnitude_value);
    options_marker.push_back(1);
  }
  options.push_back(magnitude);
  
  if (!ccx_iface.modify_loadsgravity(gravity_id ,options , options_marker))
  {
    output = "Failed!\n";
    PRINT_ERROR(output.c_str());
  }
  options.clear();
    
  return true;
}