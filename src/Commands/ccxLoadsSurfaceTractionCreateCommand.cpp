#include "ccxLoadsSurfaceTractionCreateCommand.hpp"
#include "CubitInterface.hpp"
#include "CubitMessage.hpp"
#include "CalculiXCoreInterface.hpp"

ccxLoadsSurfaceTractionCreateCommand::ccxLoadsSurfaceTractionCreateCommand()
{}

ccxLoadsSurfaceTractionCreateCommand::~ccxLoadsSurfaceTractionCreateCommand()
{}

std::vector<std::string> ccxLoadsSurfaceTractionCreateCommand::get_syntax()
{
  std::vector<std::string> syntax_list;

  std::string syntax = "ccx ";
  syntax.append("create surfacetraction ");
  syntax.append("sideset <value:label='sideset id',help='<sideset id>'> ");
  syntax.append("force_dof_1 <value:label='force_dof_1_value',help='<force_dof_1_value>'> ");
  syntax.append("force_dof_2 <value:label='force_dof_2_value',help='<force_dof_2_value>'> ");
  syntax.append("force_dof_3 <value:label='force_dof_3_value',help='<force_dof_3_value>'> ");
  syntax.append("[op {mod | new}] " );
  syntax.append("[amplitude <value:label='amplitude id',help='<amplitude id>'>] ");
  syntax.append("[timedelay <value:label='timedelay',help='<timedelay>'>] ");
  syntax.append("[name <string:type='unquoted', number='1', label='name', help='<name>'>] " );
  
  syntax_list.push_back(syntax);
  
  return syntax_list;
}

std::vector<std::string> ccxLoadsSurfaceTractionCreateCommand::get_syntax_help()
{
  std::vector<std::string> help(1);
  help[0] = "ccx "; 
  help[0].append("create surfacetraction ");
  help[0].append("sideset <sideset id> ");
  help[0].append("force_dof_1 <force_dof_1_value> ");
  help[0].append("force_dof_2 <force_dof_2_value> ");
  help[0].append("force_dof_3 <force_dof_3_value> ");
  help[0].append("[op {mod | new}] " );
  help[0].append("[amplitude <amplitude id>] ");
  help[0].append("[timedelay <timedelay>] ");
  help[0].append("[name <name>] " );
  
  return help;
}

std::vector<std::string> ccxLoadsSurfaceTractionCreateCommand::get_help()
{
  std::vector<std::string> help;
  return help;
}

bool ccxLoadsSurfaceTractionCreateCommand::execute(CubitCommandData &data)
{
  CalculiXCoreInterface ccx_iface;

  std::string output;
  std::vector<std::string> options;
  std::vector<double> options2;
  std::string sideset_id;
  int sideset_id_value;
  int op_mode = 0;
  double force_dof_1_value;
  double force_dof_2_value;
  double force_dof_3_value;
  std::string amplitude_id;
  int amplitude_value;
  std::string timedelay;
  double timedelay_value;
  std::string name = ""; 
  
  data.get_value("sideset id", sideset_id_value);
  sideset_id = std::to_string(sideset_id_value);
  data.get_value("force_dof_1_value", force_dof_1_value);
  data.get_value("force_dof_2_value", force_dof_2_value);
  data.get_value("force_dof_3_value", force_dof_3_value);
  options2.push_back(force_dof_1_value);
  options2.push_back(force_dof_2_value);
  options2.push_back(force_dof_3_value);

  if (data.find_keyword("OP")){
    if (data.find_keyword("MOD")){
      op_mode = 0;
    }else if (data.find_keyword("NEW"))
    {
      op_mode = 1;
    }
  }

  if (!data.get_value("amplitude id", amplitude_value))
  {
    amplitude_id = "-1";
  }
  else
  {
    amplitude_id = std::to_string(amplitude_value);
  }
  
  if (!data.get_value("timedelay", timedelay_value))
  {
    timedelay = "";
  }
  else
  {
    timedelay = ccx_iface.to_string_scientific(timedelay_value);
  }
  
  data.get_string("name", name);
  
  options.push_back(std::to_string(op_mode));
  options.push_back(amplitude_id);
  options.push_back(timedelay);
  options.push_back(sideset_id);
  options.push_back(name);
  
  if (!ccx_iface.create_loadssurfacetraction(options,options2))
  {
    output = "Failed!\n";
    PRINT_ERROR(output.c_str());
  }
  options.clear();
  options2.clear();
    
  return true;
}