#ifndef COREJOBS_HPP
#define COREJOBS_HPP

#include <vector>
#include <string>
#ifdef WIN32
  #include <windows.h>
  #include <thread>
#endif

class CalculiXCoreInterface;
class CubitProcess;
class ProgressTool;

class CoreJobs
{

public:
  CoreJobs();
  ~CoreJobs();

  std::vector<std::vector<std::string>> jobs_data;
  // jobs_data[0][0] job_id
  // jobs_data[0][1] name
  // jobs_data[0][2] filepath
  // jobs_data[0][3] status -1 no process, 1 process running, 2 process finished, 3 process killed, 4 process finished with errors, 5 process running currently waiting
  // jobs_data[0][4] process id
  // jobs_data[0][5] Output Console data id
  // jobs_data[0][6] converted to paraview -1 false, 1 true linked, 2 true unlinked
  // jobs_data[0][7] .cvg data id
  // jobs_data[0][8] .sta data id
  // jobs_data[0][9] auto conversion 1, no conversion -1

  std::vector<std::vector<std::string>> output_console;
  std::vector<std::vector<std::string>> cvg;
  std::vector<std::vector<std::string>> sta;

  #ifdef WIN32
    std::vector<HANDLE> ProcessPipe;
    std::vector<std::vector<int>> PPTID; //links the process PID, pipe PID and ThreadID 
    std::vector<int> PipePID; //pipe PID
    std::vector<std::thread> PipeThreads; // threads for reading the pipes
    std::vector<bool> PipeThreadsRun; // bools to keep the threads running
  #else
    std::vector<CubitProcess> CubitProcessHandler;
  #endif
  
  bool is_initialized = false;

  bool init(); // initialize
  bool update(); // check for changes of the jobs
  bool reset(); // delete all data and initialize afterwards
  bool check_initialized(); // check if object is initialized
  bool create_job(std::vector<std::string> options); // adds new job
  bool modify_job(int job_id, std::vector<std::string> options, std::vector<int> options_marker); // modify a job
  bool delete_job(int job_id); // deletes job from jobs_data
  bool add_job(int job_id, std::string name, std::string filepath); // adds new job to jobs_data
  bool run_job(int job_id, int option); // runs job
  bool wait_job(int job_id); // waits until the jobs exits
  bool kill_job(int job_id); // kill the jobs exits
  bool check_jobs(); // checks for changes of job processes
  bool get_cvgsta(int job_id); // gets filedata of .cvg and .sta
  //bool result_ccx2paraview_job(int job_id); // converts the result with ccx2paraview
  bool result_cgx_job(int job_id); // opens the results with cgx
  bool result_paraview_job(int job_id); // opens the results with paraview
  int  get_jobs_data_id_from_job_id(int job_id); // searches for the job_id in the jobs_data and returns the indices or -1 if it fails
  #ifdef WIN32
    int  get_ProcessPipe_data_id_from_PipePID(int PipePID); // searches for the Pipe Handle data id in the Processpipe and returns the indices or -1 if it fails
    int  get_PipePID_from_ProcessPID(int ProcessPID); // searches for the Pipe PID in the PPTID and returns the PipePID or -1 if it fails
    int  get_ThreadID_from_ProcessPID(int ProcessPID); // searches for the Thread ID in the PPTID and returns the Thread ID or -1 if it fails
    void read_pipe(int job_id,int bool_data_id); // make a reading thread for the jobs pipe
    void kill_pipe(int job_id); // kill the reading thread for the jobs pipe
  #else
    int  get_CubitProcessHandler_data_id_from_process_id(int process_id); // searches for the CubitProcessHandler_id in the CubitProcessHandler and returns the indices or -1 if it fails
  #endif
  bool set_job_conversion(int job_id, int conversion); // sets the paraview conversion value for the job
  std::vector<std::string> get_job_data(int job_id);
  std::vector<std::string> get_job_console_output(int job_id);
  std::vector<std::string> get_job_cvg(int job_id);
  std::vector<std::string> get_job_sta(int job_id);
  int get_job_status(int job_id); //status -2 no job -1 no process, 1 process running, 2 process finished, 3 process killed, 4 process finished with errors, 5 process running currently waiting
  bool is_whitespace(std::string line); // check if line consists only of whitespace
  std::string print_data(); // prints out the jobs_data

  CalculiXCoreInterface *ccx_iface;
  ProgressTool *progressbar; // progressbar
};

#endif // COREJOBS_HPP