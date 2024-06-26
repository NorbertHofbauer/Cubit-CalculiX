#ifndef COREORIENTATIONS_HPP
#define COREORIENTATIONS_HPP

#include <vector>
#include <string>

class CalculiXCoreInterface;

class CoreOrientations
{

public:
  CoreOrientations();
  ~CoreOrientations();

  // make 1 data storage for each orientation parameter
  // Name
  // System
  // Distribution
  // coordinates point a
  // coordinates point b
  // local axis
  // angle of rotation

  std::vector<std::vector<int>> orientations_data; // used to store the connection between a orientation id and orientation parameter id
  // orientations_data[0][0] orientation_id
  // orientations_data[0][1] name_id              option 0
  // orientations_data[0][2] system_type          option 1: 1 for rectangular, 2 for cylindrical
  // orientations_data[0][3] distribution_id      option 2: standard -1 not implemented yet
  // orientations_data[0][4] a_id                 option 3
  // orientations_data[0][5] b_id                 option 4
  // orientations_data[0][6] local axis           option 5: -1 if not used, 1 = x, 2 = y , 3 = z
  // orientations_data[0][7] rotation_id          option 6

  std::vector<std::vector<std::string>> name_data;
  // name_data[0][0] name_id
  // name_data[0][1] name

  std::vector<std::vector<std::string>> a_data;
  // a_data[0][0] a_id
  // a_data[0][1] x
  // a_data[0][2] y
  // a_data[0][3] z

  std::vector<std::vector<std::string>> b_data;
  // b_data[0][0] b_id
  // b_data[0][1] x
  // b_data[0][2] y
  // b_data[0][3] z

  std::vector<std::vector<std::string>> rotation_data;
  // rotation_data[0][0] rotation_id
  // rotation_data[0][1] angle


  bool is_initialized = false;

  bool init(); // initialize
  bool update(); // check for changes of the orientation
  bool reset(); // delete all data and initialize afterwards
  bool check_initialized(); // check if object is initialized
  bool create_orientation(std::vector<std::string> options, std::vector<std::vector<std::string>> options2); // adds new orientation
  bool modify_orientation(int orientation_id, std::vector<std::string> options, std::vector<int> options_marker, std::vector<std::vector<std::string>> options2); // modify a orientation
  bool delete_orientation(int orientation_id); // deletes orientation from orientations_data
  bool add_orientation(int orientation_id, int name_id, int system_type, int distribution_id, int a_id, int b_id, int local_axis, int rotation_id); // adds new orientation to orientations_data
  bool add_name(std::string name_id, std::string name); // adds new name to name_data
  bool add_a(std::string a_id, std::string x, std::string y, std::string z); // adds new a to a_data
  bool add_b(std::string b_id, std::string x, std::string y, std::string z); // adds new b to b_data
  bool add_rotation(std::string rotation_id, std::string angle); // adds new rotation to rotation_data
  int  get_orientations_data_id_from_orientation_id(int orientation_id); // searches for the orientation_id in the orientations_data and returns the indices or -1 if it fails
  int  get_name_data_id_from_name_id(int name_id); // searches for the name_id in the name_data and returns the indices or -1 if it fails
  int  get_a_data_id_from_a_id(int a_id); // searches for the a_id in the a_data and returns the indices or -1 if it fails
  int  get_b_data_id_from_b_id(int b_id); // searches for the b_id in the b_data and returns the indices or -1 if it fails
  int  get_rotation_data_id_from_rotation_id(int rotation_id); // searches for the rotation_id in the rotation_data and returns the indices or -1 if it fails
  std::string get_orientation_export(); // get CalculiX orientation exports
  std::string print_data(); // prints out the blocks_data

  CalculiXCoreInterface *ccx_iface;
};

#endif // COREORIENTATIONS_HPP