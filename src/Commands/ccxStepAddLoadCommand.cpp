#include "ccxStepAddLoadCommand.hpp"
#include "CubitInterface.hpp"
#include "CubitMessage.hpp"
#include "CalculiXCoreInterface.hpp"

ccxStepAddLoadCommand::ccxStepAddLoadCommand()
{}

ccxStepAddLoadCommand::~ccxStepAddLoadCommand()
{}

std::vector<std::string> ccxStepAddLoadCommand::get_syntax()
{
  std::vector<std::string> syntax_list;

  std::string syntax = "ccx ";
  syntax.append("step <value:label='step id',help='<step id>'> ");
  syntax.append("add load ");
  syntax.append("[force <value:label='force id',help='<force id>'>...] " );
  syntax.append("[pressure <value:label='pressure id',help='<pressure id>'>...] " );
  syntax.append("[heatflux <value:label='heatflux id',help='<heatflux id>'>...] " );
  syntax.append("[gravity <value:label='gravity id',help='<gravity id>'>...] " );
  syntax.append("[centrifugal <value:label='centrifugal id',help='<centrifugal id>'>...] " );
  syntax.append("[trajectory <value:label='trajectory id',help='<trajectory id>'>...] " );
  syntax.append("[film <value:label='film id',help='<film id>'>...] " );
  syntax.append("[radiation <value:label='radiation id',help='<radiation id>'>...] " );
  syntax.append("[surfacetraction <value:label='surfacetraction id',help='<surfacetraction id>'>...] " );
  syntax_list.push_back(syntax);
  
  return syntax_list;
}

std::vector<std::string> ccxStepAddLoadCommand::get_syntax_help()
{
  std::vector<std::string> help(1);
  help[0] = "ccx step <step id> add load [force <force id>...] [pressure <pressure id>...] [heatflux <heatflux id>...] ";
  help[0].append("[gravity <gravity id>...] ");
  help[0].append("[centrifugal <centrifugal id>...] ");
  help[0].append("[trajectory <trajectory id>...] ");
  help[0].append("[film <film id>...] ");
  help[0].append("[radiation <radiation id>...] ");
  help[0].append("[surfacetraction <surfacetraction id>...] ");

  return help;
}

std::vector<std::string> ccxStepAddLoadCommand::get_help()
{
  std::vector<std::string> help;
  return help;
}

bool ccxStepAddLoadCommand::execute(CubitCommandData &data)
{
  CalculiXCoreInterface ccx_iface;

  std::string output;
  
  int step_id;
  std::vector<int> force_ids;
  std::vector<int> pressure_ids;
  std::vector<int> heatflux_ids;
  std::vector<int> gravity_ids;
  std::vector<int> centrifugal_ids;
  std::vector<int> trajectory_ids;
  std::vector<int> film_ids;
  std::vector<int> radiation_ids;
  std::vector<int> surfacetraction_ids;

  data.get_value("step id", step_id);

  data.get_values("force id", force_ids);
  data.get_values("pressure id", pressure_ids);
  data.get_values("heatflux id", heatflux_ids);
  data.get_values("gravity id", gravity_ids);
  data.get_values("centrifugal id", centrifugal_ids);
  data.get_values("trajectory id", trajectory_ids);
  data.get_values("film id", film_ids);
  data.get_values("radiation id", radiation_ids);
  data.get_values("surfacetraction id", surfacetraction_ids);
   
  if (!ccx_iface.step_add_loads(step_id, 1, force_ids))
  {
    output = "Failed adding Force!\n";
    PRINT_ERROR(output.c_str());
  }
  if (!ccx_iface.step_add_loads(step_id, 2, pressure_ids))
  {
    output = "Failed adding Pressure!\n";
    PRINT_ERROR(output.c_str());
  }
  if (!ccx_iface.step_add_loads(step_id, 3, heatflux_ids))
  {
    output = "Failed adding Heatflux!\n";
    PRINT_ERROR(output.c_str());
  }
  if (!ccx_iface.step_add_loads(step_id, 4, gravity_ids))
  {
    output = "Failed adding Gravity!\n";
    PRINT_ERROR(output.c_str());
  }
  if (!ccx_iface.step_add_loads(step_id, 5, centrifugal_ids))
  {
    output = "Failed adding Centrifugal!\n";
    PRINT_ERROR(output.c_str());
  }
  if (!ccx_iface.step_add_loads(step_id, 6, trajectory_ids))
  {
    output = "Failed adding Trajectory!\n";
    PRINT_ERROR(output.c_str());
  }
  if (!ccx_iface.step_add_loads(step_id, 7, film_ids))
  {
    output = "Failed adding Film!\n";
    PRINT_ERROR(output.c_str());
  }
  if (!ccx_iface.step_add_loads(step_id, 8, radiation_ids))
  {
    output = "Failed adding Radiation!\n";
    PRINT_ERROR(output.c_str());
  }
  if (!ccx_iface.step_add_loads(step_id, 9, surfacetraction_ids))
  {
    output = "Failed adding Surface Traction!\n";
    PRINT_ERROR(output.c_str());
  }

  return true;
}