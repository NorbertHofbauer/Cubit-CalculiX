#ifndef COREBCSDISPLACEMENTS_HPP
#define COREBCSDISPLACEMENTS_HPP

#include <vector>
#include <string>

class CalculiXCoreInterface;

class CoreBCsDisplacements
{

public:
  CoreBCsDisplacements();
  ~CoreBCsDisplacements();

  std::vector<std::vector<int>> bcs_data; // used to store the connection between a force and its possible options
  // bcs_data[0][0] bc_id
  // bcs_data[0][1] OP mode: 0 for OP=MOD | 1  for OP=NEW
  // bcs_data[0][2] amplitude_id
  // bcs_data[0][3] time_delay_id
  // bcs_data[0][4] fixed dof 1, 0 no | 1 yes
  // bcs_data[0][5] fixed dof 2, 0 no | 1 yes
  // bcs_data[0][6] fixed dof 3, 0 no | 1 yes
  // bcs_data[0][7] fixed dof 4, 0 no | 1 yes
  // bcs_data[0][8] fixed dof 5, 0 no | 1 yes
  // bcs_data[0][9] fixed dof 6, 0 no | 1 yes

  std::vector<std::vector<std::string>> time_delay_data;
  // time_delay_data[0][0] time_delay_id
  // time_delay_data[0][1] time_delay_value

  bool is_initialized = false;

  bool init(); // initialize
  bool update(); // check for changes of the blocks
  bool reset(); // delete all data and initialize afterwards
  bool check_initialized(); // check if object is initialized
  bool add_bc(int bc_id, int op_mode, int amplitude_id, int time_delay_id, int fixed_dof_1, int fixed_dof_2, int fixed_dof_3, int fixed_dof_4, int fixed_dof_5, int fixed_dof_6); // adds new bc to bcs_data
  bool modify_bc(int bc_id, std::vector<std::string> options, std::vector<int> options_marker); // modify a bc
  bool delete_bc(int bc_id); // deletes bc from bcs_data
  bool add_time_delay(std::string time_delay_id, std::string time_delay_value); // adds new time delay to time_delay_data
  int  get_bcs_data_id_from_bc_id(int bc_id); // searches for the load_id in the loads_data and returns the indices or -1 if it fails
  int  get_time_delay_data_id_from_time_delay_id(int time_delay_id); // searches for the time_delay_id in the time_delay_data and returns the indices or -1 if it fails
  std::string get_bc_parameter_export(int bc_id); // gets the optional parameters for the export
  std::string get_bc_parameter_fixed_export(int bc_id); // gets the optional parameters for the export if fixed is used
  bool check_fixed(int bc_id); // returns bool if any dof is fixed
  bool check_dof_fixed(int bc_id, int dof); // returns bool if dof is fixed
  std::string print_data(); // prints out the loads_data

  CalculiXCoreInterface *ccx_iface;
};

#endif // COREBCSDISPLACEMENTS_HPP