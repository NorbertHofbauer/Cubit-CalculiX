#ifndef COREHISTORYOUTPUTS_HPP
#define COREHISTORYOUTPUTS_HPP

#include <vector>
#include <string>

class CalculiXCoreInterface;

class CoreHistoryOutputs
{

public:
  CoreHistoryOutputs();
  ~CoreHistoryOutputs();

  // make 1 data storage for each history output parameter
  // NAME
  // NODE PRINT
  // EL PRINT
  // CONTACT PRINT
  // SECTION PRINT

  std::vector<std::vector<int>> outputs_data; // used to store the connection between a output id and output parameter id
  // outputs_data[0][0] output_id
  // outputs_data[0][1] name_id           option 0
  // outputs_data[0][2] output_type 1 node print, 2 el print, 3 contact print, 4 section print       option 1
  // outputs_data[0][3] output_type_id         

  std::vector<std::vector<std::string>> name_data;
  // name_data[0][0] name_id
  // name_data[0][1] name

  std::vector<std::string> node_keys;
  std::vector<std::vector<std::string>> node_data;
  // node_data[0][0] node_id              
  // node_data[0][1] nodeset_id NSET      option[0]...
  // node_data[0][2] FREQUENCY
  // node_data[0][3] FREQUENCYF
  // node_data[0][4] TOTALS
  // node_data[0][5] GLOBAL
  // node_data[0][6] TIME POINTS
  // node_data[0][7] KEY: U
  // node_data[0][8] KEY: NT
  // node_data[0][9] KEY: TSF
  // node_data[0][10] KEY: TTF
  // node_data[0][11] KEY: PN
  // node_data[0][12] KEY: PSF
  // node_data[0][13] KEY: PTF
  // node_data[0][14] KEY: MACH
  // node_data[0][15] KEY: CP
  // node_data[0][16] KEY: VF
  // node_data[0][17] KEY: DEPF
  // node_data[0][18] KEY: TURB
  // node_data[0][19] KEY: MF
  // node_data[0][20] KEY: RF
  // node_data[0][21] KEY: RFL
  
  std::vector<std::string> element_keys;
  std::vector<std::vector<std::string>> element_data;
  // element_data[0][0] element_id            
  // element_data[0][1] elementset_id ELSET  BLOCK! option[0]...
  // element_data[0][2] FREQUENCY
  // element_data[0][3] FREQUENCYF
  // element_data[0][4] TOTALS
  // element_data[0][5] GLOBAL
  // element_data[0][6] TIME POINTS
  // element_data[0][7] KEY: S
  // element_data[0][8] KEY: SVF
  // element_data[0][9] KEY: E
  // element_data[0][10] KEY: ME
  // element_data[0][11] KEY: PEEQ
  // element_data[0][12] KEY: CEEQ
  // element_data[0][13] KEY: ENER
  // element_data[0][14] KEY: SDV
  // element_data[0][15] KEY: HFL
  // element_data[0][16] KEY: HFLF
  // element_data[0][17] KEY: COORD
  // element_data[0][18] KEY: ELSE
  // element_data[0][19] KEY: ELKE
  // element_data[0][20] KEY: EVOL
  // element_data[0][21] KEY: EMAS
  // element_data[0][22] KEY: EBHE
  // element_data[0][23] KEY: CENT
  
  std::vector<std::string> contact_keys;
  std::vector<std::vector<std::string>> contact_data;
  // contact_data[0][0] contact_id              
  // contact_data[0][1] contactpair_id // to define master and slave on export    option[0]...
  // contact_data[0][2] FREQUENCY
  // contact_data[0][3] TOTALS
  // contact_data[0][4] GLOBAL
  // contact_data[0][5] TIME POINTS
  // contact_data[0][6] KEY: CDIS
  // contact_data[0][7] KEY: CSTR
  // contact_data[0][8] KEY: CELS
  // contact_data[0][9] KEY: CNUM
  // contact_data[0][10] KEY: CF // needs contact pair
  // contact_data[0][11] KEY: CFN // needs contact pair
  // contact_data[0][12] KEY: CFS // needs contact pair 

  std::vector<std::string> section_keys;
  std::vector<std::vector<std::string>> section_data;
  // section_data[0][0] section_id              
  // section_data[0][1] sideset    option[0]...
  // section_data[0][2] FREQUENCYF
  // section_data[0][3] TIME POINTS
  // section_data[0][4] KEY: SOF
  // section_data[0][5] KEY: SOM
  // section_data[0][6] KEY: SOAREA
  // section_data[0][7] KEY: FLUX
  // section_data[0][8] KEY: DRAG

  bool is_initialized = false;

  bool init(); // initialize
  bool update(); // check for changes of the amplitude
  bool reset(); // delete all data and initialize afterwards
  bool check_initialized(); // check if object is initialized
  bool create_output(std::vector<std::string> options); // adds new output
  bool modify_output(int output_id,int modify_type, std::vector<std::string> options, std::vector<int> options_marker); // modify a output
  bool delete_output(int output_id); // deletes output from outputs_data
  bool add_output(int output_id, int name_id, int output_type, int output_type_id); // adds new output to outputs_data
  bool add_name(std::string name_id, std::string name); // adds new name to name_data
  bool add_node(std::string node_id); // adds new node to node_data with empty data
  bool add_element(std::string element_id); // adds new element to element_data with empty data
  bool add_contact(std::string contact_id); // adds new contact to contact_data with empty data
  bool add_section(std::string section_id); // adds new section to section_data with empty data
  int  get_outputs_data_id_from_output_id(int output_id); // searches for the output_id in the outputs_data and returns the indices or -1 if it fails
  int  get_name_data_id_from_name_id(int name_id); // searches for the name_id in the name_data and returns the indices or -1 if it fails
  int  get_node_data_id_from_node_id(int node_id); // searches for the node_id in the node_data and returns the indices or -1 if it fails
  int  get_element_data_id_from_element_id(int element_id); // searches for the element_id in the element_data and returns the indices or -1 if it fails
  int  get_contact_data_id_from_contact_id(int contact_id); // searches for the contact_id in the contact_data and returns the indices or -1 if it fails
  int  get_section_data_id_from_section_id(int contact_id); // searches for the contact_id in the contact_data and returns the indices or -1 if it fails
  std::string get_output_export(int output_id); // get CalculiX output export
  std::string print_data(); // prints out the data

  CalculiXCoreInterface *ccx_iface;
};

#endif // COREHISTORYOUTPUTS_HPP