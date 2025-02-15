#include "CalculiXCoreInterface.hpp"
#include "loadCalculiXCore.hpp"

CalculiXCoreInterface::CalculiXCoreInterface()
{}

CalculiXCoreInterface::~CalculiXCoreInterface()
{}

bool CalculiXCoreInterface::cmd(std::string cmd)
{
  return ccx_core.cmd(cmd);
}

bool CalculiXCoreInterface::silent_cmd(std::string cmd)
{
  return ccx_core.silent_cmd(cmd);
}

std::string CalculiXCoreInterface::get_version()
{
  return ccx_core.get_version();
}

bool CalculiXCoreInterface::set_use_ccx_autocleanup(bool bool_use)
{
  ccx_core.use_ccx_autocleanup = bool_use;
  return true;
}

bool CalculiXCoreInterface::set_use_ccx_logfile(bool bool_use)
{
  ccx_core.use_ccx_logfile = bool_use;
  return true;
}

bool CalculiXCoreInterface::init_pythoninterface()
{
  return ccx_core.init_pythoninterface();
}

bool CalculiXCoreInterface::init_materiallibrary()
{
  return ccx_core.init_materiallibrary();
}

bool CalculiXCoreInterface::init_completed()
{
  return ccx_core.init_completed();
}

bool CalculiXCoreInterface::gui_updated()
{
  return ccx_core.gui_updated();
}

bool CalculiXCoreInterface::set_gui_updated(bool status)
{
  return ccx_core.set_gui_updated(status);
}

bool CalculiXCoreInterface::block_core_update()
{
  return ccx_core.block_core_update();
}

bool CalculiXCoreInterface::set_block_core_update(bool status)
{
  return ccx_core.set_block_core_update(status);
}

bool CalculiXCoreInterface::block_gui_update()
{
  return ccx_core.block_gui_update();
}

bool CalculiXCoreInterface::set_block_gui_update(bool status)
{
  return ccx_core.set_block_gui_update(status);
}

std::string CalculiXCoreInterface::print_data()
{
  return ccx_core.print_data();
}

bool CalculiXCoreInterface::log_str(std::string str_log)
{
  ccx_core.print_to_log(str_log);
  return true;
}

bool CalculiXCoreInterface::export_to_csv(std::string path, std::vector<std::string> header, std::vector<std::vector<double>> data,bool overwrite)
{
  return ccx_core.export_to_csv(path, header, data,overwrite);
}

std::vector<int> CalculiXCoreInterface::parser(std::string parse_type, std::string parse_string)
{
  return ccx_core.parser(parse_type, parse_string);
}

std::string  CalculiXCoreInterface::to_string_scientific(double value, int precision)
{
  return ccx_core.to_string_scientific(value, precision);
}

double CalculiXCoreInterface::string_scientific_to_double(std::string value, int precision)
{
  return ccx_core.string_scientific_to_double(value, precision);
}

std::vector<std::string> CalculiXCoreInterface::get_ccx_element_types()
{ 
  return ccx_core.get_ccx_element_types();
}

bool CalculiXCoreInterface::set_ccx_element_type(int block_id, std::string ccx_element_type)
{
  if (ccx_core.set_ccx_element_type(block_id, ccx_element_type))
  {
    return true;
  }else{
    return false;
  }
}

std::string CalculiXCoreInterface::get_ccx_element_type(int block_id)
{
  return ccx_core.get_ccx_element_type(block_id);
}

std::string CalculiXCoreInterface::get_cubit_element_type_entity(std::string cubit_element_type)
{
  return ccx_core.get_cubit_element_type_entity(cubit_element_type);
}

std::vector<std::vector<int>> CalculiXCoreInterface::get_element_id_type_connectivity()
{
  return ccx_core.get_element_id_type_connectivity();
}

std::string CalculiXCoreInterface::get_block_name(int block_id)
{
  return ccx_core.get_block_name(block_id);
}

std::vector<int> CalculiXCoreInterface::get_block_node_ids(int block_id)
{
  return ccx_core.get_block_node_ids(block_id);
}

std::vector<int> CalculiXCoreInterface::get_block_element_ids(int block_id)
{
  return ccx_core.get_block_element_ids(block_id);
}

std::string CalculiXCoreInterface::get_material_name(int material_id)
{
  return ccx_core.get_material_name(material_id);
}

std::string CalculiXCoreInterface::get_material_prefix(std::string material_name)
{
  return ccx_core.get_material_prefix(material_name);
}

int CalculiXCoreInterface::get_group_property_size(std::string group_property)
{
  return ccx_core.get_group_property_size(group_property);
}

std::string CalculiXCoreInterface::get_nodeset_name(int nodeset_id)
{
  return ccx_core.get_nodeset_name(nodeset_id);
}

std::string CalculiXCoreInterface::get_sideset_name(int sideset_id)
{
  return ccx_core.get_sideset_name(sideset_id);
}

std::string CalculiXCoreInterface::get_surfaceinteraction_name(int surfaceinteraction_id)
{
  return ccx_core.get_surfaceinteraction_name(surfaceinteraction_id);
}

std::vector<std::string> CalculiXCoreInterface::get_contactpair_master_slave(int contactpair_id)
{
  return ccx_core.get_contactpair_master_slave(contactpair_id);
}

std::string CalculiXCoreInterface::get_amplitude_name(int amplitude_id)
{
  return ccx_core.get_amplitude_name(amplitude_id);
}

std::string CalculiXCoreInterface::get_orientation_name(int orientation_id)
{
  return ccx_core.get_orientation_name(orientation_id);
}

std::vector<int> CalculiXCoreInterface::get_loadsforces_ids()
{
  return ccx_core.get_loadsforces_ids();
}

std::vector<int> CalculiXCoreInterface::get_loadspressures_ids()
{
  return ccx_core.get_loadspressures_ids();
}

std::vector<int> CalculiXCoreInterface::get_loadsheatfluxes_ids()
{
  return ccx_core.get_loadsheatfluxes_ids();
}

std::vector<int> CalculiXCoreInterface::get_loadsgravity_ids()
{
  return ccx_core.get_loadsgravity_ids();
}

std::vector<int> CalculiXCoreInterface::get_loadscentrifugal_ids()
{
  return ccx_core.get_loadscentrifugal_ids();
}

std::vector<int> CalculiXCoreInterface::get_loadstrajectory_ids()
{
  return ccx_core.get_loadstrajectory_ids();
}

std::vector<int> CalculiXCoreInterface::get_loadsfilm_ids()
{
  return ccx_core.get_loadsfilm_ids();
}

std::vector<int> CalculiXCoreInterface::get_loadsradiation_ids()
{
  return ccx_core.get_loadsradiation_ids();
}

std::vector<int> CalculiXCoreInterface::get_loadssurfacetraction_ids()
{
  return ccx_core.get_loadssurfacetraction_ids();
}

std::vector<int> CalculiXCoreInterface::get_bcsdisplacements_ids()
{
  return ccx_core.get_bcsdisplacements_ids();
}

std::vector<int> CalculiXCoreInterface::get_bcstemperatures_ids()
{
  return ccx_core.get_bcstemperatures_ids();
}

std::vector<int> CalculiXCoreInterface::get_orientations_ids()
{
  return ccx_core.get_orientations_ids();
}

std::vector<int> CalculiXCoreInterface::get_equation_ids()
{
  return ccx_core.get_equation_ids();
}

bool CalculiXCoreInterface::check_block_exists(int block_id)
{
  return ccx_core.check_block_exists(block_id);
}

bool CalculiXCoreInterface::check_nodeset_exists(int nodeset_id)
{
  return ccx_core.check_nodeset_exists(nodeset_id);
}

bool CalculiXCoreInterface::check_sideset_exists(int sideset_id)
{
  return ccx_core.check_sideset_exists(sideset_id);
}

bool CalculiXCoreInterface::check_vertex_exists(int vertex_id)
{
  return ccx_core.check_vertex_exists(vertex_id);
}

bool CalculiXCoreInterface::check_curve_exists(int curve_id)
{
  return ccx_core.check_curve_exists(curve_id);
}

bool CalculiXCoreInterface::check_surface_exists(int surface_id)
{
  return ccx_core.check_surface_exists(surface_id);
}

bool CalculiXCoreInterface::check_vertex_in_nodeset_exists(int vertex_id,int nodeset_id)
{
  return ccx_core.check_vertex_in_nodeset_exists(vertex_id,nodeset_id);
}

bool CalculiXCoreInterface::check_orientation_exists(int orientation_id)
{
  return ccx_core.check_orientation_exists(orientation_id);
}

bool CalculiXCoreInterface::check_step_exists(int step_id)
{
  return ccx_core.check_step_exists(step_id);
}

bool CalculiXCoreInterface::core_update()
{
  if (ccx_core.update())
  {
    return true;
  }else{
    return false;
  }
}

bool CalculiXCoreInterface::core_reset()
{
  if (ccx_core.reset())
  {
    return true;
  }else{
    return false;
  }
}

bool CalculiXCoreInterface::core_read_cub(std::string filename)
{
  if (ccx_core.read_cub(filename))
  {
    return true;
  }else{
    return false;
  }
}

bool CalculiXCoreInterface::core_save_cub(std::string filename)
{
  if (ccx_core.save_cub(filename))
  {
    return true;
  }else{
    return false;
  }
}

std::vector<int> CalculiXCoreInterface::get_blocks()
{ 
  return ccx_core.get_blocks();
}

int CalculiXCoreInterface::get_ccx_element_side(int element_type,int side)
{
  return ccx_core.get_ccx_element_side(element_type,side);
}

bool CalculiXCoreInterface::add_sideset_face(std::string sideset_id, std::string sideset_name, std::string face, std::string element_type)
{
  return ccx_core.add_sideset_face(sideset_id, sideset_name, face, element_type);
}

std::vector<std::vector<std::string>> CalculiXCoreInterface::get_sideset_face(int sideset_id)
{
  return ccx_core.get_sideset_face(sideset_id);
}

bool CalculiXCoreInterface::create_section(std::string section_type,int block_id, int material_id, std::vector<std::string> options)
{
  return ccx_core.create_section(section_type,block_id,material_id,options);
}

bool CalculiXCoreInterface::modify_section(std::string section_type,int section_id, std::vector<std::string> options, std::vector<int> options_marker)
{
  return ccx_core.modify_section(section_type,section_id,options, options_marker);
}

bool CalculiXCoreInterface::delete_section(int section_id)
{
  return ccx_core.delete_section(section_id);
}

bool CalculiXCoreInterface::create_constraint(std::string constraint_type, std::vector<std::string> options,std::vector<std::vector<double>> options2)
{
  return ccx_core.create_constraint(constraint_type,options, options2);
}

bool CalculiXCoreInterface::modify_constraint(std::string constraint_type,int constraint_id, std::vector<std::string> options, std::vector<int> options_marker,std::vector<std::vector<double>> options2)
{
  return ccx_core.modify_constraint(constraint_type,constraint_id,options, options_marker,options2);
}

bool CalculiXCoreInterface::delete_constraint(int constraint_id)
{
  return ccx_core.delete_constraint(constraint_id);
}

bool CalculiXCoreInterface::create_constraint_tie_from_cubitcontactpair(std::string name, std::string position_tolerance)
{
  return ccx_core.create_constraint_tie_from_cubitcontactpair(name, position_tolerance);
}

bool CalculiXCoreInterface::create_surfaceinteraction(std::string surfacebehavior_type, std::vector<std::string> options, std::vector<std::vector<std::string>> options2)
{
  return ccx_core.create_surfaceinteraction(surfacebehavior_type,options,options2);
}

bool CalculiXCoreInterface::modify_surfaceinteraction(std::string modify_type, int surfaceinteraction_id, std::vector<std::string> options, std::vector<int> options_marker, std::vector<std::vector<std::string>> options2)
{
  return ccx_core.modify_surfaceinteraction(modify_type,surfaceinteraction_id,options,options_marker,options2);
}

bool CalculiXCoreInterface::delete_surfaceinteraction(int surfaceinteraction_id)
{
  return ccx_core.delete_surfaceinteraction(surfaceinteraction_id);
}

bool CalculiXCoreInterface::create_contactpair(std::vector<std::string> options)
{
  return ccx_core.create_contactpair(options);
}

bool CalculiXCoreInterface::modify_contactpair(int contactpair_id, std::vector<std::string> options, std::vector<int> options_marker)
{
  return ccx_core.modify_contactpair(contactpair_id,options,options_marker);
}

bool CalculiXCoreInterface::delete_contactpair(int contactpair_id)
{
  return ccx_core.delete_contactpair(contactpair_id);
}

bool CalculiXCoreInterface::create_contactpair_from_cubitcontactpair(int surfaceinteraction_id, std::string contactpairtype, std::string adjust, std::string adjust_nodeset)
{
  return ccx_core.create_contactpair_from_cubitcontactpair(surfaceinteraction_id,contactpairtype,adjust,adjust_nodeset);
}

bool CalculiXCoreInterface::create_amplitude(std::vector<std::string> options, std::vector<std::vector<std::string>> options2)
{
  return ccx_core.create_amplitude(options, options2);
}

bool CalculiXCoreInterface::modify_amplitude(int amplitude_id, std::vector<std::string> options, std::vector<int> options_marker, std::vector<std::vector<std::string>> options2)
{
  return ccx_core.modify_amplitude(amplitude_id,options,options_marker, options2);
}

bool CalculiXCoreInterface::delete_amplitude(int amplitude_id)
{
  return ccx_core.delete_amplitude(amplitude_id);
}

bool CalculiXCoreInterface::delete_amplitudes(std::vector<int> amplitude_ids)
{
  return ccx_core.delete_amplitudes(amplitude_ids);
}

bool CalculiXCoreInterface::create_orientation(std::vector<std::string> options, std::vector<std::vector<std::string>> options2)
{
  return ccx_core.create_orientation(options, options2);
}

bool CalculiXCoreInterface::modify_orientation(int orientation_id, std::vector<std::string> options, std::vector<int> options_marker, std::vector<std::vector<std::string>> options2)
{
  return ccx_core.modify_orientation(orientation_id, options, options_marker, options2);
}

bool CalculiXCoreInterface::delete_orientation(int orientation_id)
{
  return ccx_core.delete_orientation(orientation_id);
}

bool CalculiXCoreInterface::modify_damping(std::vector<std::string> options, std::vector<int> options_marker)
{
  return ccx_core.modify_damping(options, options_marker);
}

bool CalculiXCoreInterface::delete_damping(bool delete_alpha, bool delete_beta)
{
  return ccx_core.delete_damping(delete_alpha, delete_beta);
}

bool CalculiXCoreInterface::modify_physicalconstants(std::vector<std::string> options, std::vector<int> options_marker)
{
  return ccx_core.modify_physicalconstants(options, options_marker);
}

bool CalculiXCoreInterface::delete_physicalconstants(bool delete_absolute_zero, bool delete_stefan_boltzmann, bool delete_newton_gravity)
{
  return ccx_core.delete_physicalconstants(delete_absolute_zero, delete_stefan_boltzmann, delete_newton_gravity);
} 

bool CalculiXCoreInterface::modify_loadsforces(int force_id, std::vector<std::string> options, std::vector<int> options_marker)
{
  return ccx_core.modify_loadsforces(force_id,options,options_marker);
}

bool CalculiXCoreInterface::modify_loadspressures(int pressure_id, std::vector<std::string> options, std::vector<int> options_marker)
{
  return ccx_core.modify_loadspressures(pressure_id,options,options_marker);
}

bool CalculiXCoreInterface::modify_loadsheatfluxes(int heatflux_id, std::vector<std::string> options, std::vector<int> options_marker)
{
  return ccx_core.modify_loadsheatfluxes(heatflux_id,options,options_marker);
}

bool CalculiXCoreInterface::create_loadsgravity(std::vector<std::string> options)
{
  return ccx_core.create_loadsgravity(options);
}

bool CalculiXCoreInterface::modify_loadsgravity(int gravity_id, std::vector<std::string> options, std::vector<int> options_marker)
{
  return ccx_core.modify_loadsgravity(gravity_id,options,options_marker);
}

bool CalculiXCoreInterface::delete_loadsgravity(int gravity_id)
{
  return ccx_core.delete_loadsgravity(gravity_id);
}

bool CalculiXCoreInterface::create_loadscentrifugal(std::vector<std::string> options)
{
  return ccx_core.create_loadscentrifugal(options);
}

bool CalculiXCoreInterface::modify_loadscentrifugal(int centrifugal_id, std::vector<std::string> options, std::vector<int> options_marker)
{
  return ccx_core.modify_loadscentrifugal(centrifugal_id,options,options_marker);
}

bool CalculiXCoreInterface::delete_loadscentrifugal(int centrifugal_id)
{
  return ccx_core.delete_loadscentrifugal(centrifugal_id);
}

bool CalculiXCoreInterface::create_loadstrajectory(std::vector<std::string> options, std::vector<int> options2, std::vector<std::vector<double>> options3)
{
  return ccx_core.create_loadstrajectory(options, options2, options3);
}

bool CalculiXCoreInterface::modify_loadstrajectory(int trajectory_id, std::vector<std::string> options, std::vector<int> options_marker, std::vector<int> options2, std::vector<std::vector<double>> options3)
{
  return ccx_core.modify_loadstrajectory(trajectory_id,options,options_marker, options2, options3);
}

bool CalculiXCoreInterface::delete_loadstrajectory(int trajectory_id)
{
  return ccx_core.delete_loadstrajectory(trajectory_id);
}

std::vector<int> CalculiXCoreInterface::loadstrajectory_get_node_ids(int trajectory_id)
{
  return ccx_core.loadstrajectory_get_node_ids(trajectory_id);
}

std::vector<int> CalculiXCoreInterface::loadstrajectory_get_edge_ids(int trajectory_id)
{
  return ccx_core.loadstrajectory_get_edge_ids(trajectory_id);
}

std::vector<std::vector<double>> CalculiXCoreInterface::loadstrajectory_get_hit_coordinates(int trajectory_id)
{
  return ccx_core.loadstrajectory_get_hit_coordinates(trajectory_id);
}
  
std::vector<std::vector<std::vector<int>>> CalculiXCoreInterface::loadstrajectory_get_face_ids(int trajectory_id)
{
  return ccx_core.loadstrajectory_get_face_ids(trajectory_id);
}

std::vector<std::vector<std::vector<int>>> CalculiXCoreInterface::loadstrajectory_get_draw_face_ids(int trajectory_id)
{
  return ccx_core.loadstrajectory_get_draw_face_ids(trajectory_id);
}

std::vector<std::vector<double>> CalculiXCoreInterface::loadstrajectory_get_times(int trajectory_id)
{
  return ccx_core.loadstrajectory_get_times(trajectory_id);
} 

std::vector<std::vector<double>> CalculiXCoreInterface::loadstrajectory_get_radius(int trajectory_id)
{
  return ccx_core.loadstrajectory_get_radius(trajectory_id);
}

std::vector<std::vector<double>> CalculiXCoreInterface::loadstrajectory_get_magnitude(int trajectory_id)
{
  return ccx_core.loadstrajectory_get_magnitude(trajectory_id);
}

bool CalculiXCoreInterface::create_loadsfilm(std::vector<std::string> options)
{
  return ccx_core.create_loadsfilm(options);
}

bool CalculiXCoreInterface::modify_loadsfilm(int film_id, std::vector<std::string> options, std::vector<int> options_marker)
{
  return ccx_core.modify_loadsfilm(film_id, options, options_marker);
}

bool CalculiXCoreInterface::delete_loadsfilm(int film_id)
{
  return ccx_core.delete_loadsfilm(film_id);
}

bool CalculiXCoreInterface::create_loadsradiation(std::vector<std::string> options)
{
  return ccx_core.create_loadsradiation(options);
}

bool CalculiXCoreInterface::modify_loadsradiation(int radiation_id, std::vector<std::string> options, std::vector<int> options_marker)
{
  return ccx_core.modify_loadsradiation(radiation_id, options, options_marker);
}

bool CalculiXCoreInterface::delete_loadsradiation(int radiation_id)
{
  return ccx_core.delete_loadsradiation(radiation_id);
}

bool CalculiXCoreInterface::create_loadssurfacetraction(std::vector<std::string> options, std::vector<double> options2)
{
  return ccx_core.create_loadssurfacetraction(options, options2);
}

bool CalculiXCoreInterface::modify_loadssurfacetraction(int surfacetraction_id, std::vector<std::string> options, std::vector<double> options2, std::vector<int> options_marker)
{
  return ccx_core.modify_loadssurfacetraction(surfacetraction_id, options, options2, options_marker);
}

bool CalculiXCoreInterface::delete_loadssurfacetraction(int surfacetraction_id)
{
  return ccx_core.delete_loadssurfacetraction(surfacetraction_id);
}  

bool CalculiXCoreInterface::modify_bcsdisplacements(int displacement_id, std::vector<std::string> options, std::vector<int> options_marker)
{
  return ccx_core.modify_bcsdisplacements(displacement_id,options,options_marker);
}

bool CalculiXCoreInterface::modify_bcstemperatures(int temperature_id, std::vector<std::string> options, std::vector<int> options_marker)
{
  return ccx_core.modify_bcstemperatures(temperature_id,options,options_marker);
}

bool CalculiXCoreInterface::create_historyoutput(std::vector<std::string> options)
{
  return ccx_core.create_historyoutput(options);
}

bool CalculiXCoreInterface::modify_historyoutput(int output_id, int modify_type, std::vector<std::string> options, std::vector<int> options_marker)
{
  return ccx_core.modify_historyoutput(output_id, modify_type, options, options_marker);
}

bool CalculiXCoreInterface::delete_historyoutput(int output_id)
{
  return ccx_core.delete_historyoutput(output_id);
}

std::vector<std::string> CalculiXCoreInterface::get_historyoutput_node_keys()
{
  return  ccx_core.get_historyoutput_node_keys();
}

std::vector<std::string> CalculiXCoreInterface::get_historyoutput_element_keys()
{
  return  ccx_core.get_historyoutput_element_keys();
}

std::vector<std::string> CalculiXCoreInterface::get_historyoutput_contact_keys()
{
  return  ccx_core.get_historyoutput_contact_keys();
}

bool CalculiXCoreInterface::create_fieldoutput(std::vector<std::string> options)
{
  return ccx_core.create_fieldoutput(options);
}

bool CalculiXCoreInterface::modify_fieldoutput(int output_id, int modify_type, std::vector<std::string> options, std::vector<int> options_marker)
{
  return ccx_core.modify_fieldoutput(output_id, modify_type, options, options_marker);
}

bool CalculiXCoreInterface::delete_fieldoutput(int output_id)
{
  return ccx_core.delete_fieldoutput(output_id);
}

std::vector<std::string> CalculiXCoreInterface::get_fieldoutput_node_keys()
{
  return  ccx_core.get_fieldoutput_node_keys();
}

std::vector<std::string> CalculiXCoreInterface::get_fieldoutput_element_keys()
{
  return  ccx_core.get_fieldoutput_element_keys();
}

std::vector<std::string> CalculiXCoreInterface::get_fieldoutput_contact_keys()
{
  return  ccx_core.get_fieldoutput_contact_keys();
}

bool CalculiXCoreInterface::create_initialcondition(std::vector<std::string> options)
{
  return ccx_core.create_initialcondition(options);
}

bool CalculiXCoreInterface::modify_initialcondition(int initialcondition_id, int modify_type, std::vector<std::string> options, std::vector<int> options_marker)
{
  return ccx_core.modify_initialcondition(initialcondition_id, modify_type, options, options_marker);
}

bool CalculiXCoreInterface::delete_initialcondition(int initialcondition_id)
{
  return ccx_core.delete_initialcondition(initialcondition_id);
}

bool CalculiXCoreInterface::hbc_add_bcs(int bcs_id, int bc_type, std::vector<int> bc_ids)
{
  return ccx_core.hbc_add_bcs(bcs_id, bc_type, bc_ids);
}

bool CalculiXCoreInterface::hbc_remove_bcs(int bcs_id, int bc_type, std::vector<int> bc_ids)
{
  return ccx_core.hbc_remove_bcs(bcs_id, bc_type, bc_ids);
}

bool CalculiXCoreInterface::create_step(std::vector<std::string> options)
{
  return ccx_core.create_step(options);
}

bool CalculiXCoreInterface::modify_step(int step_id, int modify_type, std::vector<std::string> options, std::vector<int> options_marker)
{
  return ccx_core.modify_step(step_id, modify_type, options, options_marker);
}

bool CalculiXCoreInterface::delete_step(int step_id)
{
  return ccx_core.delete_step(step_id);
}

bool CalculiXCoreInterface::step_add_loads(int step_id, int load_type, std::vector<int> load_ids)
{
  return ccx_core.step_add_loads(step_id,load_type,load_ids);
}

bool CalculiXCoreInterface::step_add_bcs(int step_id, int bc_type, std::vector<int> bc_ids)
{
  return ccx_core.step_add_bcs(step_id,bc_type,bc_ids);
}

bool CalculiXCoreInterface::step_add_historyoutputs(int step_id, std::vector<int> historyoutput_ids)
{
  return ccx_core.step_add_historyoutputs(step_id,historyoutput_ids);
}

bool CalculiXCoreInterface::step_add_fieldoutputs(int step_id, std::vector<int> fieldoutput_ids)
{
  return ccx_core.step_add_fieldoutputs(step_id,fieldoutput_ids);
}

bool CalculiXCoreInterface::step_remove_loads(int step_id, int load_type, std::vector<int> load_ids)
{
  return ccx_core.step_remove_loads(step_id, load_type, load_ids);
}

bool CalculiXCoreInterface::step_remove_bcs(int step_id, int bc_type, std::vector<int> bc_ids)
{
  return ccx_core.step_remove_bcs(step_id, bc_type, bc_ids);
}

bool CalculiXCoreInterface::step_remove_historyoutputs(int step_id,std::vector<int> historyoutput_ids)
{
  return ccx_core.step_remove_historyoutputs(step_id,historyoutput_ids);
}

bool CalculiXCoreInterface::step_remove_fieldoutputs(int step_id, std::vector<int> fieldoutput_ids)
{
  return ccx_core.step_remove_fieldoutputs(step_id,fieldoutput_ids);
}

bool CalculiXCoreInterface::create_job(std::vector<std::string> options)
{
  return ccx_core.create_job(options);
}

bool CalculiXCoreInterface::modify_job(int job_id, std::vector<std::string> options, std::vector<int> options_marker)
{
  return ccx_core.modify_job(job_id, options, options_marker);
}

bool CalculiXCoreInterface::delete_job(int job_id)
{
  return ccx_core.delete_job(job_id);
}

bool CalculiXCoreInterface::run_job(int job_id, int option)
{
  return ccx_core.run_job(job_id, option);
}

bool CalculiXCoreInterface::check_jobs()
{
  return ccx_core.check_jobs();
}

bool CalculiXCoreInterface::wait_job(int job_id)
{
  return ccx_core.wait_job(job_id);
}

bool CalculiXCoreInterface::kill_job(int job_id)
{
  return ccx_core.kill_job(job_id);
}

bool CalculiXCoreInterface::set_job_conversion(int job_id, int conversion)
{
  return ccx_core.set_job_conversion(job_id,conversion);
}

bool CalculiXCoreInterface::result_cgx_job(int job_id)
{
  return ccx_core.result_cgx_job(job_id);
}

bool CalculiXCoreInterface::result_paraview_job(int job_id)
{
  return ccx_core.result_paraview_job(job_id);
}

bool CalculiXCoreInterface::result_plot_job_frd(int job_id,int x_node_id, std::string x_block_type, std::string x_block_component, bool x_increment,bool x_time,int y_node_id, std::string y_block_type, std::string y_block_component, bool y_increment, bool y_time,QString title,QString x_axis,QString y_axis,bool save, QString save_filepath)
{
  return ccx_core.result_plot_job_frd(job_id,x_node_id,x_block_type,x_block_component,x_increment,x_time,y_node_id,y_block_type,y_block_component,y_increment,y_time,title,x_axis,y_axis,save, save_filepath);
}

bool CalculiXCoreInterface::result_plot_job_dat(int job_id,int x_node_id,int x_element_id,int x_element_ip, std::string x_block_set,std::string x_block_type, std::string x_block_component, bool x_time,int y_node_id,int y_element_id,int y_element_ip, std::string y_block_set,std::string y_block_type, std::string y_block_component, bool y_time, QString title,QString x_axis,QString y_axis,bool save, QString save_filepath)
{
  return ccx_core.result_plot_job_dat(job_id,x_node_id, x_element_id, x_element_ip, x_block_set, x_block_type, x_block_component, x_time,y_node_id,y_element_id,y_element_ip, y_block_set,y_block_type, y_block_component, y_time,title,x_axis,y_axis,save,save_filepath);
}

bool CalculiXCoreInterface::result_csv_job_frd(int job_id,std::string block_type, std::string block_component, std::string increment,int node_id,int block_id,int nodeset_id,int sideset_id, bool overwrite, std::string save_filepath)
{
  return ccx_core.result_csv_job_frd(job_id, block_type, block_component, increment, node_id, block_id, nodeset_id, sideset_id, overwrite, save_filepath);
}

bool CalculiXCoreInterface::result_csv_job_dat(int job_id,std::string block_type,std::string block_set, std::string block_component, std::string time,int node_id,int element_id,bool overwrite, std::string save_filepath)
{
  return ccx_core.result_csv_job_dat(job_id, block_type, block_set, block_component, time, node_id, element_id, overwrite, save_filepath);
}

std::vector<std::string> CalculiXCoreInterface::get_job_data(int job_id)
{
  return ccx_core.get_job_data(job_id);
}

std::vector<std::string> CalculiXCoreInterface::get_job_console_output(int job_id)
{
  return ccx_core.get_job_console_output(job_id);
}

std::vector<std::string> CalculiXCoreInterface::get_job_cvg(int job_id)
{
  return ccx_core.get_job_cvg(job_id);
}

std::vector<std::string> CalculiXCoreInterface::get_job_sta(int job_id)
{
  return ccx_core.get_job_sta(job_id);
}

int CalculiXCoreInterface::get_job_status(int job_id)
{
  return ccx_core.get_job_status(job_id);
}

bool CalculiXCoreInterface::create_result(int job_id)
{
  return ccx_core.create_result(job_id);
}

bool CalculiXCoreInterface::delete_result(int job_id)
{
  return ccx_core.delete_result(job_id);
}

bool CalculiXCoreInterface::load_result(int job_id)
{
  return ccx_core.load_result(job_id);
}

int CalculiXCoreInterface::convert_result(int job_id, std::vector<int> options, std::vector<int> block_ids, std::vector<int> nodeset_ids, std::vector<int> sideset_ids)
{
  return ccx_core.convert_result(job_id, options, block_ids, nodeset_ids, sideset_ids);
}

bool CalculiXCoreInterface::project_result(int job_id,int step,int totalincrement,double scale)
{
  return ccx_core.project_result(job_id,step,totalincrement,scale);
}

double CalculiXCoreInterface::compute_von_mises_stress(std::vector<double> vec)
{
  return ccx_core.compute_von_mises_stress(vec);
}

double CalculiXCoreInterface::compute_von_mises_strain(std::vector<double> vec)
{
  return ccx_core.compute_von_mises_strain(vec);
}

std::vector<double> CalculiXCoreInterface::compute_principal_stresses(std::vector<double> vec)
{
  return ccx_core.compute_principal_stresses(vec);
}

std::vector<double> CalculiXCoreInterface::compute_principal_strains(std::vector<double> vec)
{
  return ccx_core.compute_principal_strains(vec);
}

bool CalculiXCoreInterface::create_customline(std::vector<std::string> options)
{
  return ccx_core.create_customline(options);
}

bool CalculiXCoreInterface::modify_customline(int customline_id, std::vector<std::string> options, std::vector<int> options_marker)
{
  return ccx_core.modify_customline(customline_id, options, options_marker);
}

bool CalculiXCoreInterface::delete_customline(int customline_id)
{
  return ccx_core.delete_customline(customline_id);
}

bool CalculiXCoreInterface::create_materiallibrary_group(std::string name)
{
  return ccx_core.create_materiallibrary_group(name);
}

bool CalculiXCoreInterface::modify_materiallibrary_group(std::string name,  std::string data, int mode)
{
  return ccx_core.modify_materiallibrary_group(name, data, mode);
}

bool CalculiXCoreInterface::delete_materiallibrary_group(std::string name)
{
  return ccx_core.delete_materiallibrary_group(name);
}

bool CalculiXCoreInterface::create_materiallibrary_material(std::string name, std::string groupname)
{
  return ccx_core.create_materiallibrary_material(name, groupname);
}

bool CalculiXCoreInterface::modify_materiallibrary_material(std::string name, std::string groupname, std::string data, int mode, std::vector<double> value_data)
{
  return ccx_core.modify_materiallibrary_material(name, groupname, data, mode, value_data);
}

bool CalculiXCoreInterface::delete_materiallibrary_material(std::string name, std::string groupname)
{
  return ccx_core.delete_materiallibrary_material(name, groupname);
}

bool CalculiXCoreInterface::export_materiallibrary_material(std::string name, std::string groupname, std::string cubit_name)
{
  return ccx_core.export_materiallibrary_material(name, groupname, cubit_name);
}

bool CalculiXCoreInterface::import_materiallibrary_material(std::string name, std::string groupname, std::string cubit_name)
{
  return ccx_core.import_materiallibrary_material(name, groupname, cubit_name);
}

std::vector<std::string> CalculiXCoreInterface::get_customline_data(std::string position,std::string keyword,int keyword_id)
{
  return ccx_core.get_customline_data(position,keyword,keyword_id);
}

std::vector<std::vector<std::string>> CalculiXCoreInterface::get_entities(std::string entity, int id)
{
  return ccx_core.get_entities(entity,id);
}

std::vector<std::vector<double>> CalculiXCoreInterface::get_draw_data_for_load_force(int id)
{
  return ccx_core.get_draw_data_for_load_force(id);
}

std::vector<std::vector<double>> CalculiXCoreInterface::get_draw_data_for_load_pressure(int id)
{
  return ccx_core.get_draw_data_for_load_pressure(id);
}

std::vector<std::vector<double>> CalculiXCoreInterface::get_draw_data_for_load_heatflux(int id)
{
  return ccx_core.get_draw_data_for_load_heatflux(id);
}

std::vector<std::vector<double>> CalculiXCoreInterface::get_draw_data_for_load_gravity(int id)
{
  return ccx_core.get_draw_data_for_load_gravity(id);
}

std::vector<std::vector<double>> CalculiXCoreInterface::get_draw_data_for_load_centrifugal(int id)
{
  return ccx_core.get_draw_data_for_load_centrifugal(id);
}

std::vector<std::vector<double>> CalculiXCoreInterface::get_draw_data_for_load_film(int id)
{
  return ccx_core.get_draw_data_for_load_film(id);
}

std::vector<std::vector<double>> CalculiXCoreInterface::get_draw_data_for_load_radiation(int id)
{
  return ccx_core.get_draw_data_for_load_radiation(id);
}

std::vector<std::vector<double>> CalculiXCoreInterface::get_draw_data_for_load_surface_traction(int id)
{
  return ccx_core.get_draw_data_for_load_surface_traction(id);
}

std::vector<std::vector<double>> CalculiXCoreInterface::get_draw_data_for_bc_displacement(int id) // returns coord(3) and dof
{
  return ccx_core.get_draw_data_for_bc_displacement(id);
}

std::vector<std::vector<double>> CalculiXCoreInterface::get_draw_data_for_bc_temperature(int id) // returns coord(3) and dof
{
  return ccx_core.get_draw_data_for_bc_temperature(id);
}  

std::vector<std::vector<double>> CalculiXCoreInterface::get_draw_data_for_orientation(int id)
{
  return ccx_core.get_draw_data_for_orientation(id);
}

std::vector<std::vector<double>> CalculiXCoreInterface::get_draw_data_for_equation(int id)
{
  return ccx_core.get_draw_data_for_equation(id);
}

bool CalculiXCoreInterface::draw_all(double size) // draw all bc,loads,orientations, equations
{
  return ccx_core.draw_all(size);
}

bool CalculiXCoreInterface::draw_load_force(std::vector<int> force_ids,double size)
{
  return ccx_core.draw_load_force(force_ids,size);
}

bool CalculiXCoreInterface::draw_load_pressure(std::vector<int> pressure_ids,double size)
{
  return ccx_core.draw_load_pressure(pressure_ids,size);
}

bool CalculiXCoreInterface::draw_load_heatflux(std::vector<int> heatflux_ids,double size)
{
  return ccx_core.draw_load_heatflux(heatflux_ids,size);
}

bool CalculiXCoreInterface::draw_load_gravity(std::vector<int> gravity_ids,double size)
{
  return ccx_core.draw_load_gravity(gravity_ids,size);
}

bool CalculiXCoreInterface::draw_load_centrifugal(std::vector<int> centrifugal_ids,double size)
{
  return ccx_core.draw_load_centrifugal(centrifugal_ids,size);
}

bool CalculiXCoreInterface::draw_load_trajectory(std::vector<int> trajectory_ids,double size)
{
  return ccx_core.draw_load_trajectory(trajectory_ids,size);
}

bool CalculiXCoreInterface::draw_load_film(std::vector<int> film_ids,double size)
{
  return ccx_core.draw_load_film(film_ids,size);
}

bool CalculiXCoreInterface::draw_load_radiation(std::vector<int> radiation_ids,double size)
{
  return ccx_core.draw_load_radiation(radiation_ids,size);
}

bool CalculiXCoreInterface::draw_load_surface_traction(std::vector<int> surface_traction_ids,double size)
{
  return ccx_core.draw_load_surface_traction(surface_traction_ids,size);
}

bool CalculiXCoreInterface::draw_bc_displacement(std::vector<int> displacement_ids,double size)
{
  return ccx_core.draw_bc_displacement(displacement_ids,size);
}

bool CalculiXCoreInterface::draw_bc_temperature(std::vector<int> temperature_ids,double size)
{
  return ccx_core.draw_bc_temperature(temperature_ids,size);
}

bool CalculiXCoreInterface::draw_orientation(std::vector<int> orientation_ids,double size)
{
  return ccx_core.draw_orientation(orientation_ids,size);
}

bool CalculiXCoreInterface::draw_equation(std::vector<int> equation_ids,double size)
{
  return ccx_core.draw_equation(equation_ids,size);
}

bool CalculiXCoreInterface::draw_loads(double size)
{
  return ccx_core.draw_loads(size);
}

bool CalculiXCoreInterface::draw_bcs(double size)
{
  return ccx_core.draw_bcs(size);
}

bool CalculiXCoreInterface::draw_orientations(double size)
{
  return ccx_core.draw_orientations(size);
}

bool CalculiXCoreInterface::draw_equations(double size)
{
  return ccx_core.draw_equations(size);
}

bool CalculiXCoreInterface::draw_load_forces(double size)
{
  return ccx_core.draw_load_forces(size);
}

bool CalculiXCoreInterface::draw_load_pressures(double size)
{
  return ccx_core.draw_load_pressures(size);
}

bool CalculiXCoreInterface::draw_load_heatfluxes(double size)
{
  return ccx_core.draw_load_heatfluxes(size);
}

bool CalculiXCoreInterface::draw_load_gravities(double size)
{
  return ccx_core.draw_load_gravities(size);
}

bool CalculiXCoreInterface::draw_load_centrifugals(double size)
{
  return ccx_core.draw_load_centrifugals(size);
}

bool CalculiXCoreInterface::draw_load_trajectories(double size)
{
  return ccx_core.draw_load_trajectories(size);
}

bool CalculiXCoreInterface::draw_load_films(double size)
{
  return ccx_core.draw_load_films(size);
}

bool CalculiXCoreInterface::draw_load_radiations(double size)
{
  return ccx_core.draw_load_radiations(size);
}

bool CalculiXCoreInterface::draw_load_surface_tractions(double size)
{
  return ccx_core.draw_load_surface_tractions(size);
}

bool CalculiXCoreInterface::draw_bc_displacements(double size)
{
  return ccx_core.draw_bc_displacements(size);
}

bool CalculiXCoreInterface::draw_bc_temperatures(double size)
{
  return ccx_core.draw_bc_temperatures(size);
}

std::vector<int> CalculiXCoreInterface::frd_get_nodes(int job_id)
{
  return ccx_core.frd_get_nodes(job_id);
}

bool CalculiXCoreInterface::frd_check_node_exists(int job_id,int node_id)
{
  return ccx_core.frd_check_node_exists(job_id,node_id);
}  

std::vector<std::string> CalculiXCoreInterface::frd_get_result_block_types(int job_id)
{
  return ccx_core.frd_get_result_block_types(job_id);
}

std::vector<std::string> CalculiXCoreInterface::frd_get_result_block_components(int job_id, std::string result_block_type)
{
  return ccx_core.frd_get_result_block_components(job_id, result_block_type);
}

std::vector<int> CalculiXCoreInterface::frd_get_total_increments(int job_id)
{
  return ccx_core.frd_get_total_increments(job_id);
}

double CalculiXCoreInterface::frd_get_time_from_total_increment(int job_id, int total_increment)
{
  return ccx_core.frd_get_time_from_total_increment(job_id, total_increment);
}

std::vector<int> CalculiXCoreInterface::frd_get_node_ids_between_values(int job_id,int total_increment,std::string result_block_type,std::string result_block_component,double lower_value,double upper_value)
{
  return ccx_core.frd_get_node_ids_between_values(job_id,total_increment,result_block_type,result_block_component,lower_value,upper_value);
}

std::vector<int> CalculiXCoreInterface::frd_get_node_ids_smaller_value(int job_id,int total_increment,std::string result_block_type,std::string result_block_component,double value)
{
  return ccx_core.frd_get_node_ids_smaller_value(job_id,total_increment,result_block_type,result_block_component,value);
}

std::vector<int> CalculiXCoreInterface::frd_get_node_ids_greater_value(int job_id,int total_increment,std::string result_block_type,std::string result_block_component,double value)
{
  return ccx_core.frd_get_node_ids_greater_value(job_id,total_increment,result_block_type,result_block_component,value);
}

std::vector<int> CalculiXCoreInterface::frd_get_element_ids_between_values(int job_id,int total_increment,std::string result_block_type,std::string result_block_component,double lower_value,double upper_value)
{
  return ccx_core.frd_get_element_ids_between_values(job_id,total_increment,result_block_type,result_block_component,lower_value,upper_value);
}

std::vector<int> CalculiXCoreInterface::frd_get_element_ids_smaller_value(int job_id,int total_increment,std::string result_block_type,std::string result_block_component,double value)
{
  return ccx_core.frd_get_element_ids_smaller_value(job_id,total_increment,result_block_type,result_block_component,value);
}

std::vector<int> CalculiXCoreInterface::frd_get_element_ids_greater_value(int job_id,int total_increment,std::string result_block_type,std::string result_block_component,double value)
{
  return ccx_core.frd_get_element_ids_greater_value(job_id,total_increment,result_block_type,result_block_component,value);
}

std::vector<int> CalculiXCoreInterface::frd_get_element_ids_over_limit(int job_id,int total_increment,std::string result_block_type,std::string result_block_component,double limit)
{
  return ccx_core.frd_get_element_ids_over_limit(job_id,total_increment,result_block_type,result_block_component,limit);
}

double CalculiXCoreInterface::frd_get_node_value(int job_id,int node_id, int total_increment,std::string result_block_type,std::string result_block_component)
{
  return ccx_core.frd_get_node_value(job_id,node_id,total_increment,result_block_type,result_block_component);
}

std::vector<double> CalculiXCoreInterface::frd_get_node_values(int job_id,int node_id, int total_increment,std::string result_block_type)
{
  return ccx_core.frd_get_node_values(job_id,node_id,total_increment,result_block_type);
}

std::vector<std::string> CalculiXCoreInterface::dat_get_result_block_types(int job_id)
{
  return ccx_core.dat_get_result_block_types(job_id);
}

std::vector<std::string> CalculiXCoreInterface::dat_get_result_block_set(int job_id)
{
  return ccx_core.dat_get_result_block_set(job_id);
}

std::vector<std::string> CalculiXCoreInterface::dat_get_result_block_components(int job_id, std::string result_block_type)
{
  return ccx_core.dat_get_result_block_components(job_id, result_block_type);
}

std::vector<double> CalculiXCoreInterface::dat_get_result_block_times(int job_id, std::string result_block_type, std::string result_block_set)
{
  return ccx_core.dat_get_result_block_times(job_id, result_block_type, result_block_set);
}

std::vector<int> CalculiXCoreInterface::dat_get_result_block_nodes(int job_id, double time, std::string result_block_type, std::string result_block_set)
{
  return ccx_core.dat_get_result_block_nodes(job_id, time, result_block_type, result_block_set);
}

std::vector<int> CalculiXCoreInterface::dat_get_result_block_elements(int job_id, double time, std::string result_block_type, std::string result_block_set)
{
  return ccx_core.dat_get_result_block_elements(job_id, time, result_block_type, result_block_set);
}

std::vector<int> CalculiXCoreInterface::dat_get_node_ids_between_values(int job_id,double time,std::string result_block_type,std::string result_block_set,std::string result_block_component,double lower_value,double upper_value)
{
  return ccx_core.dat_get_node_ids_between_values(job_id,time,result_block_type,result_block_set,result_block_component,lower_value,upper_value);
}

std::vector<int> CalculiXCoreInterface::dat_get_node_ids_smaller_value(int job_id,double time,std::string result_block_type,std::string result_block_set,std::string result_block_component,double value)
{
  return ccx_core.dat_get_node_ids_smaller_value(job_id,time,result_block_type,result_block_set,result_block_component,value);
}

std::vector<int> CalculiXCoreInterface::dat_get_node_ids_greater_value(int job_id,double time,std::string result_block_type,std::string result_block_set,std::string result_block_component,double value)
{
  return ccx_core.dat_get_node_ids_greater_value(job_id,time,result_block_type,result_block_set,result_block_component,value);
}

std::vector<int> CalculiXCoreInterface::dat_get_element_ids_between_values(int job_id,double time,std::string result_block_type,std::string result_block_set,std::string result_block_component,double lower_value,double upper_value)
{
  return ccx_core.dat_get_element_ids_between_values(job_id,time,result_block_type,result_block_set,result_block_component,lower_value,upper_value);
}

std::vector<int> CalculiXCoreInterface::dat_get_element_ids_smaller_value(int job_id,double time,std::string result_block_type,std::string result_block_set,std::string result_block_component,double value)
{
  return ccx_core.dat_get_element_ids_smaller_value(job_id,time,result_block_type,result_block_set,result_block_component,value);
}

std::vector<int> CalculiXCoreInterface::dat_get_element_ids_greater_value(int job_id,double time,std::string result_block_type,std::string result_block_set,std::string result_block_component,double value)
{
  return ccx_core.dat_get_element_ids_greater_value(job_id,time,result_block_type,result_block_set,result_block_component,value);
}

std::vector<int> CalculiXCoreInterface::dat_get_element_ids_over_limit(int job_id,double time,std::string result_block_type,std::string result_block_set,std::string result_block_component,double limit)
{
  return ccx_core.dat_get_element_ids_over_limit(job_id,time,result_block_type,result_block_set,result_block_component,limit);
}

double CalculiXCoreInterface::dat_get_node_value(int job_id,int node_id, double time,std::string result_block_type,std::string result_block_set,std::string result_block_component)
{
  return ccx_core.dat_get_node_value(job_id,node_id,time,result_block_type,result_block_set,result_block_component);
}

std::vector<double> CalculiXCoreInterface::dat_get_node_values(int job_id,int node_id, double time,std::string result_block_type,std::string result_block_set)
{
  return ccx_core.dat_get_node_values(job_id,node_id,time,result_block_type,result_block_set);
}

std::vector<double> CalculiXCoreInterface::dat_get_element_values_for_component(int job_id,int element_id, double time,std::string result_block_type,std::string result_block_set,std::string result_block_component)
{
  return ccx_core.dat_get_element_values_for_component(job_id,element_id,time,result_block_type,result_block_set,result_block_component);
}

std::vector<std::vector<double>> CalculiXCoreInterface::dat_get_element_values(int job_id,int element_id, double time,std::string result_block_type,std::string result_block_set)
{
  return ccx_core.dat_get_element_values(job_id,element_id,time,result_block_type,result_block_set);
}

std::vector<std::vector<std::vector<double>>> CalculiXCoreInterface::dat_get_buckle(int job_id)
{
  return ccx_core.dat_get_buckle(job_id);
}

QIcon* CalculiXCoreInterface::getIcon(std::string name)
{
  return ccx_core.getIcon(name);
}

QIcon CalculiXCoreInterface::getIcon2(std::string name)
{
  return ccx_core.getIcon2(name);
}

std::vector<std::vector<std::string>> CalculiXCoreInterface::get_blocks_tree_data()
{ 
  return ccx_core.get_blocks_tree_data();
}

std::vector<std::vector<std::string>> CalculiXCoreInterface::get_nodeset_tree_data()
{ 
  return ccx_core.get_nodeset_tree_data();
}

std::vector<std::vector<std::string>> CalculiXCoreInterface::get_sideset_tree_data()
{ 
  return ccx_core.get_sideset_tree_data();
}

std::vector<std::vector<std::string>> CalculiXCoreInterface::get_material_tree_data()
{ 
  return ccx_core.get_material_tree_data();
}

std::vector<std::vector<std::string>> CalculiXCoreInterface::get_material_group_properties()
{ 
  return ccx_core.get_material_group_properties();
}

std::vector<std::vector<std::string>> CalculiXCoreInterface::get_materiallibrary_tree_data()
{ 
  return ccx_core.get_materiallibrary_tree_data();
}

std::vector<std::vector<std::string>> CalculiXCoreInterface::get_materiallibrary_material_properties(std::string name, std::string group)
{ 
  return ccx_core.get_materiallibrary_material_properties(name, group);
}

std::vector<std::vector<double>> CalculiXCoreInterface::get_materiallibrary_material_values(std::string name, std::string group, std::string property)
{
  return ccx_core.get_materiallibrary_material_values(name, group, property);
}

std::vector<std::vector<std::string>> CalculiXCoreInterface::get_sections_tree_data()
{ 
  return ccx_core.get_sections_tree_data();
}

std::vector<std::vector<std::string>> CalculiXCoreInterface::get_constraints_tree_data()
{ 
  return ccx_core.get_constraints_tree_data();
}

std::vector<std::vector<std::string>> CalculiXCoreInterface::get_surfaceinteractions_tree_data()
{ 
  return ccx_core.get_surfaceinteractions_tree_data();
}

std::vector<std::vector<std::string>> CalculiXCoreInterface::get_contactpairs_tree_data()
{ 
  return ccx_core.get_contactpairs_tree_data();
}

std::vector<std::vector<std::string>> CalculiXCoreInterface::get_amplitudes_tree_data()
{ 
  return ccx_core.get_amplitudes_tree_data();
}

std::vector<std::vector<std::string>> CalculiXCoreInterface::get_orientations_tree_data()
{ 
  return ccx_core.get_orientations_tree_data();
}

std::vector<std::vector<std::string>> CalculiXCoreInterface::get_damping_tree_data()
{ 
  return ccx_core.get_damping_tree_data();
}

std::vector<std::vector<std::string>> CalculiXCoreInterface::get_physicalconstants_tree_data()
{ 
  return ccx_core.get_physicalconstants_tree_data();
}

std::vector<std::vector<std::string>> CalculiXCoreInterface::get_loadsforces_tree_data()
{ 
  return ccx_core.get_loadsforces_tree_data();
}

std::vector<std::vector<std::string>> CalculiXCoreInterface::get_loadspressures_tree_data()
{ 
  return ccx_core.get_loadspressures_tree_data();
}

std::vector<std::vector<std::string>> CalculiXCoreInterface::get_loadsheatfluxes_tree_data()
{ 
  return ccx_core.get_loadsheatfluxes_tree_data();
}

std::vector<std::vector<std::string>> CalculiXCoreInterface::get_loadsgravity_tree_data()
{ 
  return ccx_core.get_loadsgravity_tree_data();
}

std::vector<std::vector<std::string>> CalculiXCoreInterface::get_loadscentrifugal_tree_data()
{ 
  return ccx_core.get_loadscentrifugal_tree_data();
}

std::vector<std::vector<std::string>> CalculiXCoreInterface::get_loadstrajectory_tree_data()
{ 
  return ccx_core.get_loadstrajectory_tree_data();
}

std::vector<std::vector<std::string>> CalculiXCoreInterface::get_loadsfilm_tree_data()
{ 
  return ccx_core.get_loadsfilm_tree_data();
}

std::vector<std::vector<std::string>> CalculiXCoreInterface::get_loadsradiation_tree_data()
{ 
  return ccx_core.get_loadsradiation_tree_data();
}

std::vector<std::vector<std::string>> CalculiXCoreInterface::get_loadssurfacetraction_tree_data()
{ 
  return ccx_core.get_loadssurfacetraction_tree_data();
}

std::vector<std::vector<std::string>> CalculiXCoreInterface::get_bcsdisplacements_tree_data()
{ 
  return ccx_core.get_bcsdisplacements_tree_data();
}

std::vector<std::vector<std::string>> CalculiXCoreInterface::get_bcstemperatures_tree_data()
{ 
  return ccx_core.get_bcstemperatures_tree_data();
}

std::vector<std::vector<std::string>> CalculiXCoreInterface::get_historyoutputs_tree_data()
{ 
  return ccx_core.get_historyoutputs_tree_data();
}

std::vector<std::vector<std::string>> CalculiXCoreInterface::get_fieldoutputs_tree_data()
{ 
  return ccx_core.get_fieldoutputs_tree_data();
}

std::vector<std::vector<std::string>> CalculiXCoreInterface::get_initialconditions_tree_data()
{ 
  return ccx_core.get_initialconditions_tree_data();
}

std::vector<std::vector<std::string>> CalculiXCoreInterface::get_hbcsdisplacements_tree_data()
{ 
  return ccx_core.get_hbcsdisplacements_tree_data();
}

std::vector<std::vector<std::string>> CalculiXCoreInterface::get_hbcstemperatures_tree_data()
{ 
  return ccx_core.get_hbcstemperatures_tree_data();
}

std::vector<std::vector<std::string>> CalculiXCoreInterface::get_steps_tree_data()
{ 
  return ccx_core.get_steps_tree_data();
}

std::vector<std::vector<std::string>> CalculiXCoreInterface::get_steps_loadsforces_tree_data(int step_id)
{ 
  return ccx_core.get_steps_loadsforces_tree_data(step_id);
}

std::vector<std::vector<std::string>> CalculiXCoreInterface::get_steps_loadspressures_tree_data(int step_id)
{ 
  return ccx_core.get_steps_loadspressures_tree_data(step_id);
}

std::vector<std::vector<std::string>> CalculiXCoreInterface::get_steps_loadsheatfluxes_tree_data(int step_id)
{ 
  return ccx_core.get_steps_loadsheatfluxes_tree_data(step_id);
}

std::vector<std::vector<std::string>> CalculiXCoreInterface::get_steps_loadsgravity_tree_data(int step_id)
{ 
  return ccx_core.get_steps_loadsgravity_tree_data(step_id);
}

std::vector<std::vector<std::string>> CalculiXCoreInterface::get_steps_loadscentrifugal_tree_data(int step_id)
{ 
  return ccx_core.get_steps_loadscentrifugal_tree_data(step_id);
}

std::vector<std::vector<std::string>> CalculiXCoreInterface::get_steps_loadstrajectory_tree_data(int step_id)
{ 
  return ccx_core.get_steps_loadstrajectory_tree_data(step_id);
}

std::vector<std::vector<std::string>> CalculiXCoreInterface::get_steps_loadsfilm_tree_data(int step_id)
{ 
  return ccx_core.get_steps_loadsfilm_tree_data(step_id);
}

std::vector<std::vector<std::string>> CalculiXCoreInterface::get_steps_loadsradiation_tree_data(int step_id)
{ 
  return ccx_core.get_steps_loadsradiation_tree_data(step_id);
}

std::vector<std::vector<std::string>> CalculiXCoreInterface::get_steps_loadssurfacetraction_tree_data(int step_id)
{ 
  return ccx_core.get_steps_loadssurfacetraction_tree_data(step_id);
}

std::vector<std::vector<std::string>> CalculiXCoreInterface::get_steps_bcsdisplacements_tree_data(int step_id)
{ 
  return ccx_core.get_steps_bcsdisplacements_tree_data(step_id);
}

std::vector<std::vector<std::string>> CalculiXCoreInterface::get_steps_bcstemperatures_tree_data(int step_id)
{ 
  return ccx_core.get_steps_bcstemperatures_tree_data(step_id);
}

std::vector<std::vector<std::string>> CalculiXCoreInterface::get_steps_historyoutputs_tree_data(int step_id)
{ 
  return ccx_core.get_steps_historyoutputs_tree_data(step_id);
}

std::vector<std::vector<std::string>> CalculiXCoreInterface::get_steps_fieldoutputs_tree_data(int step_id)
{ 
  return ccx_core.get_steps_fieldoutputs_tree_data(step_id);
}

std::vector<std::vector<std::string>> CalculiXCoreInterface::get_customlines_tree_data()
{ 
  return ccx_core.get_customlines_tree_data();
}

std::vector<std::vector<std::string>> CalculiXCoreInterface::get_jobs_tree_data()
{ 
  return ccx_core.get_jobs_tree_data();
}

bool CalculiXCoreInterface::prepare_export()
{
  return ccx_core.prepare_export();
}

bool CalculiXCoreInterface::clean_export()
{
  return ccx_core.clean_export();
}

std::string CalculiXCoreInterface::get_material_export_data() // gets the export data from materials core
{
  return ccx_core.get_material_export_data();
}

std::string CalculiXCoreInterface::get_section_export_data() // gets the export data from sections core
{
  return ccx_core.get_section_export_data();
}

std::string CalculiXCoreInterface::get_constraint_export_data() // gets the export data from constraints core
{
  return ccx_core.get_constraint_export_data();
}

std::string CalculiXCoreInterface::get_surfaceinteraction_export_data() // gets the export data from surfaceinteractions core
{
  return ccx_core.get_surfaceinteraction_export_data();
}

std::string CalculiXCoreInterface::get_contactpair_export_data() // gets the export data from contactpairs core
{
  return ccx_core.get_contactpair_export_data();
}

std::string CalculiXCoreInterface::get_amplitude_export_data() // gets the export data from amplitudes core
{
  return ccx_core.get_amplitude_export_data();
}

std::string CalculiXCoreInterface::get_orientation_export_data() // gets the export data from orientation core
{
  return ccx_core.get_orientation_export_data();
}

std::string CalculiXCoreInterface::get_damping_export_data() // gets the export data from damping core
{
  return ccx_core.get_damping_export_data();
}

std::string CalculiXCoreInterface::get_physicalconstants_export_data() // gets the export data from physicalconstants core
{
  return ccx_core.get_physicalconstants_export_data();
}

std::string CalculiXCoreInterface::get_initialcondition_export_data() // gets the export data from core
{
  return ccx_core.get_initialcondition_export_data();
}

std::string CalculiXCoreInterface::get_hbc_export_data() // gets the export data from core
{
  return ccx_core.get_hbc_export_data();
}

std::string CalculiXCoreInterface::get_step_export_data() // gets the export data from core
{
  return ccx_core.get_step_export_data();
}

std::vector<int> CalculiXCoreInterface::get_steps_ids() //gets the step ids from core
{
  return ccx_core.get_steps_ids();
}
