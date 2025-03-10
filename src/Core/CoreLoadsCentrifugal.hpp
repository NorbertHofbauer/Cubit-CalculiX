#ifndef CORELOADSCENTRIFUGAL_HPP
#define CORELOADSCENTRIFUGAL_HPP

#include <vector>
#include <string>

class CalculiXCoreInterface;

class CoreLoadsCentrifugal
{

public:
  CoreLoadsCentrifugal();
  ~CoreLoadsCentrifugal();

  std::vector<std::vector<int>> loads_data; // used to store the connection between a centrifugal and its possible options
  // loads_data[0][0] load_id
  // loads_data[0][1] OP mode: 0 for OP=MOD | 1  for OP=NEW
  // loads_data[0][2] amplitude_id
  // loads_data[0][3] time_delay_id
  // loads_data[0][4] block_id
  // loads_data[0][5] direction_id
  // loads_data[0][6] magnitude_id
  // loads_data[0][7] coordinate_id
  // loads_data[0][8] name_id

  std::vector<std::vector<std::string>> time_delay_data;
  // time_delay_data[0][0] time_delay_id
  // time_delay_data[0][1] time_delay_value

  std::vector<std::vector<std::string>> direction_data;
  // direction_data[0][0] direction_id
  // direction_data[0][1] x
  // direction_data[0][2] y
  // direction_data[0][3] z

  std::vector<std::vector<std::string>> magnitude_data;
  // magnitude_data[0][0] magnitude_id
  // magnitude_data[0][1] magnitude

  std::vector<std::vector<std::string>> coordinate_data;
  // coordinate_data[0][0] coordinate_id
  // coordinate_data[0][1] x
  // coordinate_data[0][2] y
  // coordinate_data[0][3] z


  std::vector<std::vector<std::string>> name_data;
  // name_data[0][0] name_id
  // name_data[0][1] name

  bool is_initialized = false;

  bool init(); // initialize
  bool update(); // check for changes of the blocks
  bool reset(); // delete all data and initialize afterwards
  bool check_initialized(); // check if object is initialized
  bool create_load(std::vector<std::string> options); // adds new load
  bool add_load(int load_id, int op_mode, int amplitude_id, int time_delay_id, int block_id, int direction_id, int magnitude_id, int coordinate_id, int name_id); // adds new load to loads_data
  bool modify_load(int load_id, std::vector<std::string> options, std::vector<int> options_marker); // modify a load
  bool delete_load(int load_id); // deletes load from loads_data
  bool add_time_delay(std::string time_delay_id, std::string time_delay_value); // adds new time delay to time_delay_data
  bool add_direction(std::string direction_id, std::string x, std::string y, std::string z); // adds new direction to direction_data
  bool add_magnitude(std::string magnitude_id, std::string magnitude_value); // adds new magnitude to magnitude_data
  bool add_coordinate(std::string coordinate_id, std::string x, std::string y, std::string z); // adds new coordinate to coordinate_data
  bool add_name(std::string name_id, std::string name); // adds new name to name_data
  int  get_loads_data_id_from_load_id(int load_id); // searches for the load_id in the loads_data and returns the indices or -1 if it fails
  int  get_time_delay_data_id_from_time_delay_id(int time_delay_id); // searches for the time_delay_id in the time_delay_data and returns the indices or -1 if it fails
  int  get_magnitude_data_id_from_magnitude_id(int magnitude_id); // searches for the magnitude_id in the magnitude_data and returns the indices or -1 if it fails
  int  get_direction_data_id_from_direction_id(int direction_id); // searches for the direction_id in the direction_data and returns the indices or -1 if it fails
  int  get_coordinate_data_id_from_coordinate_id(int coordinate_id); // searches for the coordinate_id in the coordinate_data and returns the indices or -1 if it fails
  int  get_name_data_id_from_name_id(int name_id); // searches for the name_id in the name_data and returns the indices or -1 if it fails
  std::string get_load_export(int load_id); // gets the optional parameters for the export
  std::string print_data(); // prints out the loads_data

  CalculiXCoreInterface *ccx_iface;
};

#endif // CORELOADSCENTRIFUGAL_HPP