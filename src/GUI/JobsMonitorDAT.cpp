#include "JobsMonitorDAT.hpp"
#include "CalculiXCoreInterface.hpp"
#include "JobsMonitorDATPlot.hpp"

#include "CubitInterface.hpp"
#include "CubitMessage.hpp"
#include "Broker.hpp"
#include "Claro.hpp"
#include "PickWidget.hpp"

JobsMonitorDAT::JobsMonitorDAT()
{
  CalculiXCoreInterface *ccx_iface = new CalculiXCoreInterface();

  // main window
  //this->setGeometry(0,0,700,570);
  this->setWindowTitle("FRD Results");
  gridLayout = new QGridLayout(this);
  boxLayout_result_block = new QVBoxLayout();
  boxLayout_result_set = new QVBoxLayout();
  boxLayout_component = new QVBoxLayout();
  boxLayout_time = new QVBoxLayout();
  boxLayout_filter =  new  QVBoxLayout() ;
  //boxLayout_filter_by_set = new QVBoxLayout();
  boxLayout_filter_by_node = new QHBoxLayout();
  vertical_spacer_filter = new QSpacerItem(1,1,QSizePolicy::Minimum,QSizePolicy::Expanding);
  boxLayout_filter_by_element = new QHBoxLayout();
  boxLayout_result_buttons = new QHBoxLayout();
  boxLayout_widget = new QVBoxLayout();
  boxLayout_pages = new QHBoxLayout();
  gridLayout->addLayout(boxLayout_result_set,0,0, Qt::AlignTop);
  gridLayout->addLayout(boxLayout_result_block,0,1, Qt::AlignTop);
  gridLayout->addLayout(boxLayout_component,0,2, Qt::AlignTop);
  gridLayout->addLayout(boxLayout_time,0,3, Qt::AlignTop);
  gridLayout->addLayout(boxLayout_filter,0,4, Qt::AlignTop);
  gridLayout->addLayout(boxLayout_widget,1,0,1,5, Qt::AlignTop);
  gridLayout->addLayout(boxLayout_pages,2,0,1,5, Qt::AlignTop);

  // buttons
  pushButton_reset = new QPushButton();
  pushButton_reset->setText("Reset");
  pushButton_plot = new QPushButton();
  pushButton_plot->setText("Plot");
  pushButton_query_results = new QPushButton("Get Results");

  boxLayout_result_buttons->addWidget(pushButton_reset);
  boxLayout_result_buttons->addWidget(pushButton_query_results);
  boxLayout_result_buttons->addWidget(pushButton_plot);

  // labels
  label_result_block = new QLabel();
  label_result_block->setText("Result Blocks");
  boxLayout_result_block->addWidget(label_result_block);

  label_result_set = new QLabel();
  label_result_set->setText("Result Sets");
  boxLayout_result_set->addWidget(label_result_set);

  label_component = new QLabel();
  label_component->setText("Components");
  boxLayout_component->addWidget(label_component);

  label_time = new QLabel();
  label_time->setText("Times");
  boxLayout_time->addWidget(label_time);

  //label_filter_by_set = new QLabel();
  //label_filter_by_set->setText("Filter by Set");
  //boxLayout_filter_by_set->addWidget(label_filter_by_set);

  label_filter_by_node = new QLabel();
  label_filter_by_node->setText("Filter by Node");
  label_filter_node_id = new QLabel();
  label_filter_node_id->setText("Node ID");
  boxLayout_filter_by_node->addWidget(label_filter_node_id);

  label_filter_by_element = new QLabel();
  label_filter_by_element->setText("Filter by Element");
  label_filter_element_id = new QLabel();
  label_filter_element_id->setText("Element ID");
  boxLayout_filter_by_element->addWidget(label_filter_element_id);

  // lists
  list_result_block = new QListWidget();
  boxLayout_result_block->addWidget(list_result_block);

  list_result_set = new QListWidget();
  boxLayout_result_set->addWidget(list_result_set);

  list_component = new QListWidget();
  boxLayout_component->addWidget(list_component);

  list_time = new QListWidget();
  boxLayout_time->addWidget(list_time);

  //filter
  //combobox_filter_by_set = new QComboBox();
  //combobox_filter_by_set->addItem("none");
  //combobox_filter_by_set->addItem(ccx_iface->getIcon2("BlocksTree"),"Block");
  //combobox_filter_by_set->addItem(ccx_iface->getIcon2("NodesetTree"),"Nodeset");
  //combobox_filter_by_set->addItem(ccx_iface->getIcon2("SidesetTree"),"Sideset");
  //boxLayout_filter_by_set->addWidget(combobox_filter_by_set);
  //table_filter_by_set = new QTableWidget();
  //table_filter_by_set->setLineWidth(1);
  //table_filter_by_set->setMidLineWidth(0);
  //table_filter_by_set->setFrameStyle(QFrame::Box | QFrame::Raised);
  
  //boxLayout_filter_by_set->addWidget(table_filter_by_set);

  PickWidget_filter_node_id = new PickWidget();
  PickWidget_filter_node_id->setPickType(PickWidget::Node);
  PickWidget_filter_node_id->activate();
  boxLayout_filter_by_node->addWidget(PickWidget_filter_node_id);

  PickWidget_filter_element_id = new PickWidget();
  PickWidget_filter_element_id->setPickType(PickWidget::Element);
  PickWidget_filter_element_id->activate();
  boxLayout_filter_by_element->addWidget(PickWidget_filter_element_id);
  
  //boxLayout_filter->addLayout(boxLayout_filter_by_set);
  boxLayout_filter->addWidget(label_filter_by_node);
  boxLayout_filter->addLayout(boxLayout_filter_by_node);
  boxLayout_filter->addWidget(label_filter_by_element);
  boxLayout_filter->addLayout(boxLayout_filter_by_element);
  boxLayout_filter->addItem(vertical_spacer_filter);
  boxLayout_filter->addLayout(boxLayout_result_buttons);

  //table
  table_result = new QTableWidget();
  table_result->setMinimumSize(700,350);
  table_result->setLineWidth(1);
  table_result->setMidLineWidth(0);
  table_result->setFrameStyle(QFrame::Box | QFrame::Raised);
  table_counter = new QLabel;
  table_counter->setText("");
  pushButton_prev = new QPushButton("Previous Results");
  pushButton_next = new QPushButton("Next Results");
  pushButton_prev->setDisabled(true);
  pushButton_next->setDisabled(true);
  pushButton_export = new QPushButton("Export to CSV");
  boxLayout_widget->addWidget(table_result);
  boxLayout_pages->addWidget(pushButton_prev);
  boxLayout_pages->addWidget(table_counter);
  boxLayout_pages->addWidget(pushButton_next);
  boxLayout_pages->addWidget(pushButton_export);
  

  PlotWidget = new JobsMonitorDATPlot();
  PlotWidget->hide();

  // Signals
  QObject::connect(pushButton_reset, SIGNAL(clicked(bool)),this,  SLOT(on_pushButton_reset_clicked(bool)));
  QObject::connect(pushButton_plot, SIGNAL(clicked(bool)),this,  SLOT(on_pushButton_plot_clicked(bool)));
  QObject::connect(pushButton_query_results, SIGNAL(clicked(bool)),this,  SLOT(on_pushButton_query_results_clicked(bool)));
  QObject::connect(list_result_block, SIGNAL(itemClicked(QListWidgetItem*)),this,  SLOT(result_block_clicked(QListWidgetItem*)));
  QObject::connect(list_result_block, SIGNAL(currentItemChanged(QListWidgetItem*, QListWidgetItem*)),this,  SLOT(result_block_changed(QListWidgetItem*,QListWidgetItem*)));
  QObject::connect(list_result_set, SIGNAL(itemClicked(QListWidgetItem*)),this,  SLOT(result_set_clicked(QListWidgetItem*)));
  QObject::connect(list_result_set, SIGNAL(currentItemChanged(QListWidgetItem*, QListWidgetItem*)),this,  SLOT(result_set_changed(QListWidgetItem*,QListWidgetItem*)));
  QObject::connect(list_component, SIGNAL(itemClicked(QListWidgetItem*)),this,  SLOT(component_clicked(QListWidgetItem*)));
  QObject::connect(list_component, SIGNAL(currentItemChanged(QListWidgetItem*, QListWidgetItem*)),this,  SLOT(component_changed(QListWidgetItem*,QListWidgetItem*)));
  QObject::connect(list_time, SIGNAL(itemClicked(QListWidgetItem*)),this,  SLOT(time_clicked(QListWidgetItem*)));
  QObject::connect(list_time, SIGNAL(currentItemChanged(QListWidgetItem*, QListWidgetItem*)),this,  SLOT(time_changed(QListWidgetItem*,QListWidgetItem*)));
  QObject::connect(pushButton_prev, SIGNAL(clicked(bool)), this, SLOT(on_pushButton_previous_clicked(bool)));
  QObject::connect(pushButton_next, SIGNAL(clicked(bool)), this, SLOT(on_pushButton_next_clicked(bool)));
  QObject::connect(pushButton_export, SIGNAL(clicked(bool)),this, SLOT(on_pushButton_export_clicked(bool)));

  // Update list items and data
  this->update();
}

JobsMonitorDAT::~JobsMonitorDAT()
{}

void JobsMonitorDAT::clear()
{
}

void JobsMonitorDAT::update()
{
  if (current_job_id ==-1)
  {
    return;
  }

  list_result_block->clear();
  list_component->clear();
  list_time->clear();
  table_result->setRowCount(0);
  table_result->setColumnCount(0);
  this->current_result_block = nullptr;
  this->current_result_component = nullptr;
  pushButton_prev->setDisabled(true);
  pushButton_next->setDisabled(true);
  pushButton_export->setDisabled(true);
  table_counter->setText("");
  PickWidget_filter_node_id->setText("");
  PickWidget_filter_element_id->setText("");
    
  std::vector<std::string> result_block_types = ccx_iface->dat_get_result_block_types(current_job_id);
  
  if (result_block_types.size() == 0)
  {
    return;
  }

  for (size_t i = 0; i < result_block_types.size(); i++)
  {
    this->addListItem(result_block_types[i],list_result_block);
  }

  this->update_set();
  
  list_result_block->item(0)->setSelected(true);
  this->result_block_clicked(list_result_block->item(0));
}

void JobsMonitorDAT::update_set()
{ 
  if (current_job_id ==-1)
  {
    return;
  }
  
  list_result_set->clear();
  this->current_result_set = nullptr;
    
  std::vector<std::string> result_block_sets = ccx_iface->dat_get_result_block_set(current_job_id);
  
  for (size_t i = 0; i < result_block_sets.size(); i++)
  {
    this->addListItem(result_block_sets[i],list_result_set);
  }

  list_result_set->item(0)->setSelected(true);
  this->result_set_clicked(list_result_set->item(0));
}

void JobsMonitorDAT::update_component(std::string result_block)
{
  if (current_job_id ==-1)
  {
    return;
  }
  
  list_component->clear();
  list_time->clear();

  std::vector<std::string> components = ccx_iface->dat_get_result_block_components(current_job_id, result_block);
  components.insert(components.begin(), "all");

  for (size_t i = 0; i < components.size(); i++)
  {
    this->addListItem(components[i],list_component);
  }

  list_component->item(0)->setSelected(true);
  this->component_clicked(list_component->item(0));
}

void JobsMonitorDAT::update_time()
{
  if (current_job_id ==-1)
  {
    return;
  }
  if (current_result_block==nullptr)
  {
    return;
  }
  if (current_result_set==nullptr)
  {
    return;
  }
  
  
  list_time->clear();
  this->current_time = nullptr;
  std::string result_block;
  result_block = current_result_block->text().toStdString();
  std::string result_set;
  result_set = current_result_set->text().toStdString();

  std::vector<double> times = ccx_iface->dat_get_result_block_times(current_job_id,result_block,result_set);
  
  if (times.size()>0)
  {
    this->addListItem("all", list_time);
    for (size_t i = 0; i < times.size(); i++)
    {
      this->addListItem(std::to_string(times[i]),list_time);
    }
    
    list_time->item(0)->setSelected(true);
    this->time_clicked(list_time->item(0));
  }  
}


void JobsMonitorDAT::update_result()
{
  std::string log;

  table_result->setRowCount(0);
  table_result->setColumnCount(0);

  if(current_job_id == -1)
  {
    log = "Can't update results -> no job set \n";
    PRINT_INFO("%s", log.c_str());
    return;
  }
  if (this->current_result_set==nullptr)
  {
    log = "Can't update results -> no result_set \n";
    PRINT_INFO("%s", log.c_str());
    return;
  }
  if (this->current_result_block==nullptr)
  {
    log = "Can't update results -> no result block set \n";
    PRINT_INFO("%s", log.c_str());
    return;
  }
  if(this->current_result_component==nullptr)
  {
    log = "Can't update results -> no result component set \n";
    PRINT_INFO("%s", log.c_str());
    return;
  }
  if (current_time==nullptr)
  {
    log = "Can't update results -> no increment set \n";
    PRINT_INFO("%s", log.c_str());
    return;
  }
  if ((PickWidget_filter_node_id->text()!="")&&(PickWidget_filter_element_id->text()!=""))
  {
    log = "Can't update results -> Can't filter for Node ID and Element ID at the same time! \n";
    PRINT_INFO("%s", log.c_str());
    return;
  }

  // check if filter was chosen
  int node_id = PickWidget_filter_node_id->text().toInt();
  int element_id = PickWidget_filter_element_id->text().toInt();
  
  //prepare components
  std::vector<std::string> components;
  if (current_result_component->text().toStdString()=="all")
  {
    components = ccx_iface->dat_get_result_block_components(current_job_id, current_result_block->text().toStdString());
  }else{
    components.push_back(current_result_component->text().toStdString());
  }

  //prepare times
  std::vector<double> times;
  if (current_time->text().toStdString()=="all")
  {
    times = ccx_iface->dat_get_result_block_times(current_job_id,current_result_block->text().toStdString(),current_result_set->text().toStdString());
  }else{
    times.push_back(current_time->text().toDouble());
  }

  //get nodes and elements
  std::vector<int> nodes;
  std::vector<int> elements;

  if (node_id>0)
  {
    nodes.push_back(node_id);
  }else{
    nodes = ccx_iface->dat_get_result_block_nodes(current_job_id,times[0],current_result_block->text().toStdString(),current_result_set->text().toStdString());
  }
  if (element_id>0)
  {
    elements.push_back(element_id);
  }else{
    elements = ccx_iface->dat_get_result_block_elements(current_job_id,times[0],current_result_block->text().toStdString(),current_result_set->text().toStdString());
  }
  
  if ((nodes.size()>0)&&(elements.size()>0))
  {
    log = "Can't update results -> Can't request for Nodes and Element Data at the same time! \n";
    PRINT_INFO("%s", log.c_str());
    return;
  }

  //get results
  std::vector<std::vector<double>> node_results;
  std::vector<std::vector<double>> element_results;
  std::string str_current_result_block = current_result_block->text().toStdString();
  std::string str_current_result_set = current_result_set->text().toStdString();
  int start = 0;
  int end = 0;

  if (nodes.size()>0) // node results
  {
    start = this->current_page * items_per_page;
    end = start + this->items_per_page - 1;
    end = std::min(end, int(nodes.size()*times.size()-1));
    this->results_size = int(nodes.size()*times.size());
    if (this->current_page==0)
    {
      pushButton_prev->setDisabled(true);
    }else{
      pushButton_prev->setEnabled(true);
    }
    if (end < int(nodes.size()*times.size()-1))
    {
      pushButton_next->setEnabled(true);
    }else{
      pushButton_next->setDisabled(true);
    }
    pushButton_export->setEnabled(true);
  }

  int ipc = 0;
  if (elements.size()>0) // element results
  {
    //delete duplicate element ids
    std::sort(elements.begin(),elements.end());
    elements.erase(std::unique(elements.begin(), elements.end()), elements.end());
    std::vector<double> tmp_element = ccx_iface->dat_get_element_values_for_component(current_job_id,elements[0],times[0],str_current_result_block,str_current_result_set,components[0]);
    ipc = int(tmp_element.size()); // number of integration points

    start = this->current_page * items_per_page;
    end = start + this->items_per_page - 1;
    end = std::min(end, int(elements.size()*ipc*times.size()-1));
    this->results_size = int(elements.size()*ipc*times.size());
    if (this->current_page==0)
    {
      pushButton_prev->setDisabled(true);
    }else{
      pushButton_prev->setEnabled(true);
    }
    if (end < int(elements.size()*ipc*times.size()-1))
    {
      pushButton_next->setEnabled(true);
    }else{
      pushButton_next->setDisabled(true);
    }
    pushButton_export->setEnabled(true);
  }

  if ((nodes.size()>0)&&(components.size()>0)&&(times.size()>0)) //check if data can be queried
  {
    int ic = 0;
    for (size_t i = 0; i < nodes.size(); i++)
    {
      for (size_t ii = 0; ii < times.size(); ii++)
      {
        if ((ic>=start)&&(ic<=end))// check if items are in range
        {
          std::vector<double> tmp_result;
          tmp_result.push_back(double(nodes[i]));
          tmp_result.push_back(double(times[ii]));
          for (size_t iii = 0; iii < components.size(); iii++)
          {
            double node_result = ccx_iface->dat_get_node_value(current_job_id, nodes[i],times[ii],str_current_result_block,str_current_result_set, components[iii]);
            tmp_result.push_back(node_result);
          }
          node_results.push_back(tmp_result);
        }
        ++ic;
      }
      if (ic>end)
      {
        break;
      }
    }
  }

  if ((elements.size()>0)&&(components.size()>0)&&(times.size()>0)) //check if data can be queried
  {
    int ic = 0;
    for (size_t i = 0; i < elements.size(); i++)
    {
      for (size_t ii = 0; ii < times.size(); ii++)
      { 
        std::vector<std::vector<double>> tmp_result;
        for (size_t iii = 0; iii < components.size(); iii++)
        {
          std::vector<double> element_result = ccx_iface->dat_get_element_values_for_component(current_job_id, elements[i],times[ii],str_current_result_block,str_current_result_set, components[iii]);
          if (iii == 0)
          {
            for (size_t iv = 0; iv < element_result.size(); iv++)
            {
              std::vector<double> tmp;
              tmp.push_back(double(elements[i]));
              tmp.push_back(double(times[ii]));
              tmp.push_back(element_result[iv]);
              tmp_result.push_back(tmp);
            }
          }else{
            for (size_t iv = 0; iv < element_result.size(); iv++)
            {
              tmp_result[iv].push_back(element_result[iv]);
            }
          }
        }
        for (size_t iii = 0; iii < tmp_result.size(); iii++)
        {
          if (((ic>=start)&&(ic<=end)))// check if items are in range
          {
            element_results.push_back(tmp_result[iii]);
          }
          ++ic;
          if (ic>end)
          {
            break;
          }
        }  
      }
      if (ic>end)
      {
        break;
      }
    }
  }

/*
  log = "element_results.size() " + std::to_string(element_results.size()) + "\n";
  PRINT_INFO("%s", log.c_str());
  log = "element_results[0].size() " + std::to_string(element_results[0].size()) + "\n";
  PRINT_INFO("%s", log.c_str());
*/

  table_result->setSortingEnabled(true);
  if (node_results.size()>0)
  {
    table_result->setRowCount(std::min(50,int(node_results.size())));
    table_result->setColumnCount(int(node_results[0].size()));    
  }
  if (element_results.size()>0)
  {
    table_result->setRowCount(std::min(50,int(element_results.size())));
    table_result->setColumnCount(int(element_results[0].size()));    
  }
  table_result->setEditTriggers(QAbstractItemView::NoEditTriggers);
  table_counter->setText(QString::fromStdString("Results " + std::to_string(start+1) + "-" + std::to_string(end+1) + " of " + std::to_string(results_size)));

  //fill table
  for (size_t i = 0; i < node_results.size(); i++)
  {
    if (i==0) // label headers
    {
      QStringList header_horizontal;
      header_horizontal.push_back("Node ID");
      header_horizontal.push_back("Time");
      for (size_t ii = 0; ii < components.size(); ii++)
      {
        header_horizontal.push_back(QString::fromStdString(components[ii]));
      }
      table_result->setHorizontalHeaderLabels(header_horizontal);
      
      QStringList header_vertical;
      for (size_t ii = start; ii < end+1; ii++)
      {
        header_vertical.push_back(QString::number(ii+1));
      }
      table_result->setVerticalHeaderLabels(header_vertical);
    }
    //push data
    for (size_t ii = 0; ii < node_results[i].size(); ii++)
    {
      if (ii > 2)
      {
        QString formatted_result_value = QString::number(node_results[i][ii], 'f', 6);
        QTableWidgetItem* item = new QTableWidgetItem(formatted_result_value);
        item->setData(Qt::DisplayRole, node_results[i][ii]);
        table_result->setItem(int(i), int(ii), item);
      } else {
        QTableWidgetItem* item = new QTableWidgetItem;
        item->setData(Qt::DisplayRole, node_results[i][ii]);
        table_result->setItem(int(i), int(ii), item);
      }
    }
  }
  for (size_t i = 0; i < element_results.size(); i++)
  {
    if (i==0) // label headers
    {
      QStringList header_horizontal;
      header_horizontal.push_back("Element ID");
      header_horizontal.push_back("Time");
      for (size_t ii = 0; ii < components.size(); ii++)
      {
        header_horizontal.push_back(QString::fromStdString(components[ii]));
      }
      table_result->setHorizontalHeaderLabels(header_horizontal);
      
      QStringList header_vertical;
      for (size_t ii = start; ii < end+1; ii++)
      {
        header_vertical.push_back(QString::number(ii+1));
      }
      table_result->setVerticalHeaderLabels(header_vertical);
    }
    //push data
    for (size_t ii = 0; ii < element_results[i].size(); ii++)
    {
      if (ii > 2)
      {
        QString formatted_result_value = QString::number(element_results[i][ii], 'f', 6);
        QTableWidgetItem* item = new QTableWidgetItem(formatted_result_value);
        item->setData(Qt::DisplayRole, element_results[i][ii]);
        table_result->setItem(int(i), int(ii), item);
      } else {
        QTableWidgetItem* item = new QTableWidgetItem;
        item->setData(Qt::DisplayRole, element_results[i][ii]);
        table_result->setItem(int(i), int(ii), item);
      }
    }
  }
}

void JobsMonitorDAT::set_current_job_id(int job_id)
{
  this->current_job_id = job_id;
  PlotWidget->current_job_id = job_id;
  //std::string log = "Current job id set is " + std::to_string(current_job_id) + "\n";
  //PRINT_INFO("%s", log.c_str());
  this->update();
  PlotWidget->reset();
}

void JobsMonitorDAT::addListItem(std::string item_name, QListWidget* parent_list)
{
  QString name;
  name = QString::fromStdString(item_name);
  QListWidgetItem* new_list_item;
  new_list_item = new QListWidgetItem(name,parent_list);
}

void JobsMonitorDAT::addTableItem(std::string item_name, QTableWidget* parent_list)
{
  QString name;
  name = QString::fromStdString(item_name);
  QTableWidgetItem* new_list_item;
  new_list_item = new QTableWidgetItem(name);
}

void JobsMonitorDAT::on_pushButton_reset_clicked(bool)
{
  this->update();  
}

void JobsMonitorDAT::on_pushButton_plot_clicked(bool)
{
  PlotWidget->show();
}

void JobsMonitorDAT::on_pushButton_query_results_clicked(bool)
{ // Clemens, dies if not everything chosen
  if(current_job_id == -1)
  {
    return;
  }

  this->current_page = 0;

  this->update_result();
}

void JobsMonitorDAT::result_block_clicked(QListWidgetItem* item)
{
 this->current_result_block = item;
 std::string result_block;
 result_block = item->text().toStdString();
 this->update_component(result_block); 
}

void JobsMonitorDAT::result_block_changed(QListWidgetItem* current_item, QListWidgetItem* prev_item)
{
  if (current_item!=nullptr)
  {
    this->result_block_clicked(current_item);
  }
}

void JobsMonitorDAT::result_set_clicked(QListWidgetItem* item)
{
  this->current_result_set = item;
  if (current_result_block!=nullptr)
  {
    this->result_block_clicked(current_result_block);
  }
}

void JobsMonitorDAT::result_set_changed(QListWidgetItem* current_item, QListWidgetItem* prev_item)
{
  if (current_item!=nullptr)
  {
    this->result_set_clicked(current_item);
  }
}

void JobsMonitorDAT::component_clicked(QListWidgetItem* item)
{
  this->current_result_component = item;
  this->update_time();
}

void JobsMonitorDAT::component_changed(QListWidgetItem* current_item, QListWidgetItem* prev_item)
{
  if (current_item!=nullptr)
  {
    this->component_clicked(current_item);
  }
}

void JobsMonitorDAT::time_clicked(QListWidgetItem* item)
{
  this->current_time = item;
}

void JobsMonitorDAT::time_changed(QListWidgetItem* current_item, QListWidgetItem* prev_item)
{
  if (current_item!=nullptr)
  {
    this->time_clicked(current_item);
  }
}

void JobsMonitorDAT::on_pushButton_previous_clicked(bool)
{
  if (current_page>0)
  {
    this->current_page = current_page-1;
    update_result();
  }
}

void JobsMonitorDAT::on_pushButton_next_clicked(bool)
{
  if (current_page < std::ceil(results_size/50))
  {
    current_page = current_page+1;
    update_result();
  }
}

void JobsMonitorDAT::on_pushButton_export_clicked(bool)
{
  int node_id=-1;
  int element_id=-1;
  std::string block_set="";
  std::string block_type="";
  std::string block_component="";
  std::string time = "";
  bool overwrite = false;
  std::string save_filepath;

  std::string log;
  if(current_job_id == -1)
  {
    log = "Can't export results -> no job set \n";
    PRINT_INFO("%s", log.c_str());
    return;
  }
  if (this->current_result_set==nullptr)
  {
    log = "Can't export results -> no result_set \n";
    PRINT_INFO("%s", log.c_str());
    return;
  }
  if (this->current_result_block==nullptr)
  {
    log = "Can't export results -> no result block set \n";
    PRINT_INFO("%s", log.c_str());
    return;
  }
  if(this->current_result_component==nullptr)
  {
    log = "Can't export results -> no result component set \n";
    PRINT_INFO("%s", log.c_str());
    return;
  }
  if (current_time==nullptr)
  {
    log = "Can't export results -> no increment set \n";
    PRINT_INFO("%s", log.c_str());
    return;
  }
  if ((PickWidget_filter_node_id->text()!="")&&(PickWidget_filter_element_id->text()!=""))
  {
    log = "Can't export results -> Can't filter for Node ID and Element ID at the same time! \n";
    PRINT_INFO("%s", log.c_str());
    return;
  }

  
  node_id = PickWidget_filter_node_id->text().toInt();
  element_id = PickWidget_filter_element_id->text().toInt();
  block_set = current_result_set->text().toStdString();
  block_type = current_result_block->text().toStdString();
  block_component = current_result_component->text().toStdString();
  time = current_time->text().toStdString();

  QString fileName;

  QFileDialog dialog;
  dialog.setWindowTitle("Save CSV");
  dialog.setDirectory(QDir::homePath());
  dialog.setNameFilter("CSV Files (*.csv);;All Files (*)");
  fileName = dialog.getSaveFileName();

  if(fileName.isEmpty())
  {
    log = "File save canceled.\n";
    PRINT_INFO("%s", log.c_str());
    return;
  }

  if (!fileName.endsWith(".csv", Qt::CaseInsensitive)) 
  {
    fileName += ".csv";
  }

  if (QFileInfo::exists(fileName)) 
  {
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(nullptr, "File Exists", "The file already exists. Do you want to overwrite it?", QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
      overwrite = true;
    }
  }

  //ccx result csv job <job_id> frd block_type <block_type> block_component <block_component> increment <increment> save <save_filepath> [overwrite] [{block_id <block_id>|nodeset_id <nodeset_id>|sideset_id <sideset_id>}] [node_id <node_id>] 
  std::string cmd = "";
  cmd.append("ccx result csv job " + std::to_string(this->current_job_id) + " dat ");
  cmd.append("block_set \'" + block_set + "\' ");
  cmd.append("block_type \'" + block_type + "\' ");
  cmd.append("block_component \'" + block_component + "\' ");
  cmd.append("inc_time \'" + time + "\' ");
  cmd.append("save \'" + fileName.toStdString() + "\' ");
  if (overwrite)
  {
    cmd.append("overwrite ");
  }
  if (node_id>0)
  {
    cmd.append("node_id " + std::to_string(node_id) + " ");
  }
  if (element_id>0)
  {
    cmd.append("element_id " + std::to_string(element_id) + " ");
  }
  ccx_iface->cmd(cmd);

  return;
}