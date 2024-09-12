#include "CalculiXComp.hpp"

#include "Claro.hpp"
#include "Broker.hpp"
#include "ComponentInfo.hpp"
#include "ExportManager.hpp"
#include "MenuManager.hpp"
#include "Observer.hpp"
#include "OptionsPanel.hpp"

#include "cmdPanelManager.hpp"
#include "CCXDockWindowModelTree.hpp"
#include "ToolbarManager.hpp"
#include "loadUserOptions.hpp"
#include "ConfigFile.hpp"
#include "UserOptionsPanel.hpp"
#include <iostream>

// Default constructor. Remember to include the component name (should match
// the module name in mycomp.i).
CalculiXComp::CalculiXComp() :
  Component("CalculiXComp"),
  myMenus(NULL),
  myToolbars(NULL),
  mycmdPanels(NULL),
  myCCXDockWindowModelTree(NULL),
  myExportManager(NULL),
  mListener(NULL)
{}

CalculiXComp::~CalculiXComp()
{
  if(myMenus)
    delete myMenus;

  if(myToolbars)
    delete myToolbars;

  if(mycmdPanels)
    delete mycmdPanels;

  if(myCCXDockWindowModelTree)
    delete myCCXDockWindowModelTree;

  if(myExportManager)
    delete myExportManager;

  if(mListener)
    delete mListener;
}

void CalculiXComp::start_up(int withGUI)
{
  restore_settings();
  if(withGUI)
  {
    //setup_menus();
    //setup_toolbars();
    setup_command_panels();
    setup_CCXDockWindowModelTree(); // command panels has to be setup before dockwindow
    //add_exports();
    load_options();
    boolwithGUI = true;
  }
  setup_observers(withGUI);
}

void CalculiXComp::clean_up()
{
  //cleanup_menus();
  //cleanup_toolbars();
  cleanup_command_panels();
  cleanup_CCXDockWindowModelTree();
  //cleanup_exports();
  cleanup_observers();
  save_settings();
  unload_options();
  // Let the framework know you are done.
  clean_up_complete();
}

void CalculiXComp::update()
{
  if(boolwithGUI)
  {
    if(myCCXDockWindowModelTree)
    myCCXDockWindowModelTree->update();
  }
}

void CalculiXComp::reset()
{
  if(boolwithGUI)
  {
    if(myCCXDockWindowModelTree)
    myCCXDockWindowModelTree->reset();
  }
}

void CalculiXComp::setup_menus()
{
  if(!myMenus)
    myMenus = new MenuManager;

  myMenus->add_to_existing_menu();
  myMenus->setup_custom_menu();
}

void CalculiXComp::cleanup_menus()
{
  if(myMenus)
    myMenus->remove_menu_items();
}

void CalculiXComp::setup_toolbars()
{
  if(!myToolbars)
    myToolbars = new ToolbarManager;

  myToolbars->add_to_existing_toolbar();
  myToolbars->setup_custom_toolbar();
}

void CalculiXComp::cleanup_toolbars()
{
  if(myToolbars)
    myToolbars->remove_toolbar_items();
}

void CalculiXComp::setup_command_panels()
{
  if(!mycmdPanels)
    mycmdPanels = new cmdPanelManager;

  mycmdPanels->initialize();
}

void CalculiXComp::cleanup_command_panels()
{
  if(mycmdPanels)
    mycmdPanels->clear();
}

void CalculiXComp::setup_CCXDockWindowModelTree()
{
  if(!myCCXDockWindowModelTree)
    myCCXDockWindowModelTree = new CCXDockWindowModelTree;

  myCCXDockWindowModelTree->initialize();
}

void CalculiXComp::cleanup_CCXDockWindowModelTree()
{
  if(myCCXDockWindowModelTree)
    myCCXDockWindowModelTree->clear();
}

void CalculiXComp::add_exports()
{
  if(!myExportManager)
  {
    myExportManager = new ExportManager();
    myExportManager->add_export_types();
  }
}

void CalculiXComp::cleanup_exports()
{
  if(myExportManager)
    myExportManager->remove_export_types();
}

void CalculiXComp::setup_observers(int withGUI)
{
  if(!mListener)
  {
    mListener = new Observer();

    // Let Cubit know that this class will be observing events
    mListener->register_observer();

    // get a connection down to the observer
    mListener->fetch_comp(this);
  }
}

void CalculiXComp::cleanup_observers()
{
  if(mListener)
  {
    // If cubitcomp is still loaded, we need to unregister the observer.
    ComponentInfo cubitcomp_info;
    Broker::instance()->get_component_info("cubitcomp", cubitcomp_info);
    if(cubitcomp_info.get_state() == "Loaded")
      mListener->unregister_observer();

    delete mListener;
    mListener = NULL;
  }
}

void CalculiXComp::restore_settings()
{
  ConfigFile config;
  config.read_entry("PathSolver", ccx_uo.mPathSolver);
  ccx_uo.mPathSolverName = "Path to CalculiX Solver";
  config.read_num_entry("SolverThreads", ccx_uo.mSolverThreads);
  ccx_uo.mSolverThreadsName = "Solver - Threads";
  config.read_num_entry("ConverterThreads", ccx_uo.mConverterThreads);
  ccx_uo.mConverterThreadsName = "Converter - Threads";
  config.read_entry("PathCGX", ccx_uo.mPathCGX);
  ccx_uo.mPathCGXName = "Path to CGX";
  config.read_entry("PathParaView", ccx_uo.mPathParaView);
  ccx_uo.mPathParaViewName = "Path to ParaView";
  config.read_entry("PathIcons", ccx_uo.mPathIcons);
  ccx_uo.mPathIconsName = "Path to Icons";
  config.read_entry("PathPythonInterface", ccx_uo.mPathPythonInterface);
  ccx_uo.mPathPythonInterfaceName = "Path to Python Interface";
}

void CalculiXComp::save_settings()
{
  ConfigFile config;
  
  config.clear();
  config.write_entry("PathSolver", ccx_uo.mPathSolver);
  config.write_num_entry("SolverThreads", ccx_uo.mSolverThreads);
  config.write_num_entry("ConverterThreads", ccx_uo.mConverterThreads);
  config.write_entry("PathCGX", ccx_uo.mPathCGX);
  config.write_entry("PathParaView", ccx_uo.mPathParaView);
  config.write_entry("PathIcons", ccx_uo.mPathIcons);
  config.write_entry("PathPythonInterface", ccx_uo.mPathPythonInterface);
}

void CalculiXComp::load_options()
{
  if(Claro::instance())
  {
    mUserOptionsPanel = new UserOptionsPanel();
    OptionsPanel *options = Claro::instance()->options();
    options->add_panel("CalculiX", mUserOptionsPanel);
    QObject::connect(options, SIGNAL(refreshSettings()),mUserOptionsPanel,  SLOT(refresh_settings()));
    QObject::connect(options, SIGNAL(saveSettings()),mUserOptionsPanel,  SLOT(save_settings()));
  }
}

void CalculiXComp::unload_options()
{
  if(Claro::instance())
  {
    OptionsPanel *options = Claro::instance()->options();
    options->remove_panel("CalculiX");
    delete mUserOptionsPanel;
  }
}