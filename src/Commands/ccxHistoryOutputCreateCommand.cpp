#include "ccxHistoryOutputCreateCommand.hpp"
#include "CubitInterface.hpp"
#include "CubitMessage.hpp"
#include "CalculiXCoreInterface.hpp"

ccxHistoryOutputCreateCommand::ccxHistoryOutputCreateCommand()
{}

ccxHistoryOutputCreateCommand::~ccxHistoryOutputCreateCommand()
{}

std::vector<std::string> ccxHistoryOutputCreateCommand::get_syntax()
{
  std::vector<std::string> syntax_list;

  std::string syntax = "ccx ";
  syntax.append("create historyoutput ");
  syntax.append("name <string:type='unquoted', number='1', label='name', help='<name>'> " );
  syntax.append("{node|element|contact|section}" );
  syntax_list.push_back(syntax);
  
  return syntax_list;
}

std::vector<std::string> ccxHistoryOutputCreateCommand::get_syntax_help()
{
  std::vector<std::string> help(1);
  help[0] = "ccx create historyoutput name <name> {node|element|contact|section}"; 

  return help;
}

std::vector<std::string> ccxHistoryOutputCreateCommand::get_help()
{
  std::vector<std::string> help;
  return help;
}

bool ccxHistoryOutputCreateCommand::execute(CubitCommandData &data)
{
  CalculiXCoreInterface ccx_iface;

  std::string output;
  std::vector<std::string> options;  
  std::string name;

  data.get_string("name", name);
  options.push_back(name);

  if (data.find_keyword("NODE"))
  {
    options.push_back("1");
  } else if (data.find_keyword("ELEMENT"))
  {
    options.push_back("2");
  } else if (data.find_keyword("CONTACT"))
  {
    options.push_back("3");
  } else if (data.find_keyword("SECTION"))
  {
    options.push_back("4");
  }
  
  if (!ccx_iface.create_historyoutput(options))
  {
    output = "Failed!\n";
    PRINT_ERROR(output.c_str());
  }
  options.clear();
    
  return true;
}