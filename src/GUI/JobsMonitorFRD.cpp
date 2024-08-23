#include "JobsMonitorFRD.hpp"
#include "CalculiXCoreInterface.hpp"

#include "CubitInterface.hpp"
#include "CubitMessage.hpp"
#include "Broker.hpp"
#include "Claro.hpp"

JobsMonitorFRD::JobsMonitorFRD()
{
  CalculiXCoreInterface *ccx_iface = new CalculiXCoreInterface();

  // main window
  //this->setGeometry(0,0,700,570);
  this->setWindowTitle("FRD Results");
  gridLayout = new QGridLayout(this);
  boxLayout_window = new QHBoxLayout();
  boxLayout_result_block = new QVBoxLayout();
  boxLayout_component = new QVBoxLayout();
  boxLayout_filter1 = new QVBoxLayout();
  boxLayout_filter2 = new QVBoxLayout();
  boxLayout_widget = new QVBoxLayout();
  gridLayout->addLayout(boxLayout_window,2,4, Qt::AlignRight);
  gridLayout->addLayout(boxLayout_result_block,0,0, Qt::AlignTop);
  gridLayout->addLayout(boxLayout_component,0,1, Qt::AlignTop);
  gridLayout->addLayout(boxLayout_filter1,0,2, Qt::AlignTop);
  gridLayout->addLayout(boxLayout_filter2,0,3, Qt::AlignTop);
  gridLayout->addLayout(boxLayout_widget,1,0,1,4, Qt::AlignTop);

  // buttons
  pushButton_refresh = new QPushButton();
  pushButton_refresh->setText("Refresh");
  boxLayout_window->addWidget(pushButton_refresh);

  pushButton_plot = new QPushButton();
  pushButton_plot->setText("Plot");
  boxLayout_window->addWidget(pushButton_plot);

  // labels
  label_result_block = new QLabel();
  //label_material->setGeometry(10,10,80,16);
  label_result_block->setText("Result Blocks");
  boxLayout_result_block->addWidget(label_result_block);

  label_component = new QLabel();
  //label_available->setGeometry(300,10,100,16);
  label_component->setText("Components");
  boxLayout_component->addWidget(label_component);

  label_filter1 = new QLabel();
  label_filter1->setText("Filter");
  boxLayout_filter1->addWidget(label_filter1);

  label_filter2 = new QLabel();
  label_filter2->setText(" ");
  boxLayout_filter2->addWidget(label_filter2);

  // lists
  list_result_block = new QListWidget();
  boxLayout_result_block->addWidget(list_result_block);

  list_component = new QListWidget();
  boxLayout_component->addWidget(list_component);

  list_filter = new QListWidget();
  list_filter->setFrameShape(QFrame::Box);
  list_filter->setFrameShadow(QFrame::Raised);
  label_increment1 = new QLabel("Increment from");
  textField1 = new QSpinBox;
  label_increment2 = new QLabel("Increment until");
  textField2 = new QSpinBox;
  label_node1 = new QLabel("Node from");
  textField3 = new QSpinBox;
  label_node2 = new QLabel("Node until");
  textField4 = new QSpinBox;
  label_block1 = new QLabel("Block from");
  textField5 = new QSpinBox;
  label_block2 = new QLabel("Block until");
  textField6 = new QSpinBox;
  label_sideset1 = new QLabel("Sideset from");
  textField7 = new QSpinBox;
  label_sideset2 = new QLabel("Sideset until");
  textField8 = new QSpinBox;
  pushButton_apply_filter = new QPushButton("Apply Filter");
  boxLayout_filter1->addWidget(label_increment1);
  boxLayout_filter1->addWidget(textField1);
  boxLayout_filter1->addWidget(label_increment2);
  boxLayout_filter1->addWidget(textField2);
  boxLayout_filter1->addWidget(label_node1);
  boxLayout_filter1->addWidget(textField3);
  boxLayout_filter1->addWidget(label_node2);
  boxLayout_filter1->addWidget(textField4);
  boxLayout_filter2->addWidget(label_block1);
  boxLayout_filter2->addWidget(textField5);
  boxLayout_filter2->addWidget(label_block2);
  boxLayout_filter2->addWidget(textField6);
  boxLayout_filter2->addWidget(label_sideset1);
  boxLayout_filter2->addWidget(textField7);
  boxLayout_filter2->addWidget(label_sideset2);
  boxLayout_filter2->addWidget(textField8);
  boxLayout_filter2->addWidget(pushButton_apply_filter);

  /* std::vector<int> total_increments = ccx_iface->frd_get_total_increments(current_job_id);
  std::vector<int> total_nodes = CubitInterface::get_nodeset_id_list();
  std::vector<int> total_blocks = ccx_iface->get_blocks();
  std::vector<int> total_sidesets = CubitInterface::get_sideset_id_list();
  auto max_increment = std::max_element(total_increments.begin(), total_increments.end());
  int increment_max = *max_increment;
  auto max_node = std::max_element(total_nodes.begin(), total_nodes.end());
  int node_max = *max_node;
  auto max_block = std::max_element(total_blocks.begin(), total_blocks.end());
  int block_max = *max_block;
  auto max_sideset = std::max_element(total_sidesets.begin(), total_sidesets.end());
  int sideset_max = *max_sideset;
  textField1->setMaximum(increment_max);
  textField2->setMaximum(increment_max);
  textField3->setMaximum(node_max);
  textField4->setMaximum(node_max);
  textField5->setMaximum(block_max);
  textField6->setMaximum(block_max);
  textField7->setMaximum(sideset_max);
  textField8->setMaximum(sideset_max); */

  //table
  table_result = new QTableWidget();
  table_result->setMinimumSize(700,350);
  table_result->setLineWidth(1);
  table_result->setMidLineWidth(0);
  table_result->setFrameStyle(QFrame::Box | QFrame::Raised);
  boxLayout_widget->addWidget(table_result);

  //result_frame->show();

  // Signals
  QObject::connect(pushButton_refresh, SIGNAL(clicked(bool)),this,  SLOT(on_pushButton_refresh_clicked(bool)));
  QObject::connect(pushButton_plot, SIGNAL(clicked(bool)),this,  SLOT(on_pushButton_plot_clicked(bool)));
  QObject::connect(pushButton_apply_filter, SIGNAL(clicked(bool)),this,  SLOT(on_pushButton_apply_filter_clicked(bool)));
  QObject::connect(list_result_block, SIGNAL(itemClicked(QListWidgetItem*)),this,  SLOT(result_block_clicked(QListWidgetItem*)));
  QObject::connect(list_result_block, SIGNAL(currentItemChanged(QListWidgetItem*, QListWidgetItem*)),this,  SLOT(result_block_changed(QListWidgetItem*,QListWidgetItem*)));
  QObject::connect(list_component, SIGNAL(itemClicked(QListWidgetItem*)),this,  SLOT(component_clicked(QListWidgetItem*)));
  QObject::connect(list_component, SIGNAL(currentItemChanged(QListWidgetItem*, QListWidgetItem*)),this,  SLOT(component_changed(QListWidgetItem*,QListWidgetItem*)));

  // Update list items and data
  this->update();
}

JobsMonitorFRD::~JobsMonitorFRD()
{}

void JobsMonitorFRD::clear()
{
  // Remove all of our tree items from material tree.
  /*while (tree_material->topLevelItemCount()>0)
  {
    tree_material->removeItemWidget(tree_material->topLevelItem(0),0);
  }
  this->removeListItems();*/
}

void JobsMonitorFRD::update()
{
  if (current_job_id ==-1)
  {
    return;
  }
  
  this->removeListItems();

  std::vector<std::string> result_block_types = ccx_iface->frd_get_result_block_types(current_job_id);
  
  for (size_t i = 0; i < result_block_types.size(); i++)
  {
    this->addListItem(result_block_types[i],list_result_block);
  }
}

void JobsMonitorFRD::update_component(std::string result_block)
{
  if (current_job_id ==-1)
  {
    return;
  }
  
  this->removeListItems_from_List(list_component);

  std::vector<std::string> components = ccx_iface->frd_get_result_block_components(current_job_id, result_block);
  
  for (size_t i = 0; i < components.size(); i++)
  {
    this->addListItem(components[i],list_component);
  }
}

void JobsMonitorFRD::update_result(std::vector<int> increment_ids, std::vector<int> node_ids, std::vector<int> block_ids, std::vector<int> sideset_ids)
{
  if(current_job_id == -1)
  {
    return;
  }

  table_result->setRowCount(0);
  table_result->setColumnCount(0);

  std::string current_result_block = get_current_block()->text().toStdString();
  std::string current_component = get_current_component()->text().toStdString();

  std::vector<std::vector<double>> results;

  // results[i][0] = increment id
  // results[i][1] = node id
  // results[i][2] = block id
  // results[i][3] = sideset id
  // results[i][4] = result (later)
  // results[i][5] = increment time (later)

  for (int i : increment_ids)
  {
    for (int j : node_ids)
    {
      for (int k : block_ids) //Clemens blocks & sidesets haben keinen Effekt
      {
        for (int l : sideset_ids)
        {
          results.push_back({i,j,k,l});
        }
      }
    }
  }

  if (results.size() == 0)
  {
    return;
  }

  for (size_t i = 0; i < results.size(); i++)
  {
    double node_result = ccx_iface->frd_get_node_value(current_job_id, results[i][1], results[i][0], current_result_block ,current_component);
    results[i].push_back(node_result);
    
    double increment_time = ccx_iface->frd_get_time_from_total_increment(current_job_id, results[i][0]);
    results[i].push_back(increment_time);

  }

  table_result->setRowCount(results.size());
  table_result->setColumnCount(results[0].size());
  table_result->setEditTriggers(QAbstractItemView::NoEditTriggers);
  table_result->setHorizontalHeaderLabels(QStringList() << "Increment Id" << "Node Id" << "Block Id" << "Sideset Id" << "Result" << "Increment Time");

  for (size_t i = 0; i < results.size(); i++)
  {
    for (size_t ii = 0; ii < results[0].size(); ii++)
    {
      QTableWidgetItem* item = new QTableWidgetItem(QString::number(results[i][ii]));
      table_result->setItem(i, ii, item);
    }
  }
}

/* void JobsMonitorFRD::update_increment(std::string result_block)
{  // what if multiple Jobs??
  if(current_job_id == -1)
  {
    return;
  }

  this->removeTableItems_from_Table(table_increment);

  std::vector<int> increments = ccx_iface->frd_get_total_increments(current_job_id);

  table_increment->setRowCount(increments.size());
  
  for (size_t i = 0; i < increments.size(); i++)
  {
    double increment_time;
    increment_time = ccx_iface->frd_get_time_from_total_increment(current_job_id, increments[i]);

    QString intAsString = QString::number(increments[i]);
    QTableWidgetItem* increment_qtableitem = new QTableWidgetItem(intAsString);

    QString doubleAsString = QString::number(increment_time, 'f', 6); 
    QTableWidgetItem* increment_time_qtableitem = new QTableWidgetItem(doubleAsString);

    table_increment->setItem(i, 1, increment_qtableitem);
    table_increment->setItem(i, 2, increment_time_qtableitem);
  }
} */

void JobsMonitorFRD::set_current_job_id(int job_id)
{
  this->current_job_id = job_id;
  
  std::string log = "Current job id set is " + std::to_string(current_job_id) + "\n";
  PRINT_INFO("%s", log.c_str());

  this->update();
}

void JobsMonitorFRD::addListItem(std::string item_name, QListWidget* parent_list)
{
  QString name;
  name = QString::fromStdString(item_name);
  QListWidgetItem* new_list_item;
  new_list_item = new QListWidgetItem(name,parent_list);
}

void JobsMonitorFRD::addTableItem(std::string item_name, QTableWidget* parent_list)
{
  QString name;
  name = QString::fromStdString(item_name);
  QTableWidgetItem* new_list_item;
  new_list_item = new QTableWidgetItem(name);
}

void JobsMonitorFRD::removeListItem(std::string item_name, QListWidget* parent_list)
{
  QString name;
  name = QString::fromStdString(item_name);
}

void JobsMonitorFRD::createListItems()
{
  QListWidgetItem* list_conductivity;
  list_conductivity = new QListWidgetItem("Conductivity",list_result_block);

  list_result_block->sortItems();
}

void JobsMonitorFRD::removeListItems()
{
  if (list_result_block->count()>0)
  {
    list_result_block->setCurrentItem(list_result_block->item(0));
    while (list_result_block->currentItem())
    {
      delete list_result_block->currentItem();
    }
  } 

  if (list_component->count()>0)
  {
    list_component->setCurrentItem(list_component->item(0));
    while (list_component->currentItem())
    {
      delete list_component->currentItem();
    }
  }
}

void JobsMonitorFRD::removeListItems_from_List(QListWidget* list)
{
  list->clear();
  /* if (list->count()>0)
  {
    list->setCurrentItem(list->item(0));
    while (list->currentItem())
    {
      delete list->currentItem();
    }
  } */
}

void JobsMonitorFRD::removeTableItems_from_Table(QTableWidget* table)
{
  table->clearContents();
  /* if (table->rowCount()>0)
  {
    table->setCurrentItem(table->item(0));
    while (table->currentItem())
    {
      delete table->currentItem();
    }
  } */
}

void JobsMonitorFRD::selectListItem(QListWidgetItem* item)
{
  QListWidgetItem* temp_item;

  for (size_t i = 0; i < list_result_block->count(); i++)
  {
    temp_item = list_result_block->item(int(i));
    if (temp_item != item)
    {
      temp_item->setSelected(false);
    }
  }
}

void JobsMonitorFRD::on_pushButton_refresh_clicked(bool)
{
  this->update();  
}

void JobsMonitorFRD::on_pushButton_plot_clicked(bool)
{

}

void JobsMonitorFRD::on_pushButton_apply_filter_clicked(bool)
{ // Clemens, dies if not everything chosen
  if(current_job_id == -1)
  {
    return;
  }

  QString string_increment_lower = textField1->text();
  QString string_increment_upper = textField2->text();
  QString string_node_lower = textField3->text();
  QString string_node_upper = textField4->text();
  QString string_block_lower = textField5->text();
  QString string_block_upper = textField6->text();
  QString string_sideset_lower = textField7->text();
  QString string_sideset_upper = textField8->text();
  
  double increment_lower = string_increment_lower.toInt(); //Clemens what if not a number?
  double increment_upper = string_increment_upper.toInt();
  double node_lower = string_node_lower.toInt();
  double node_upper = string_node_upper.toInt();
  double block_lower = string_block_lower.toInt();
  double block_upper = string_block_upper.toInt();
  double sideset_lower = string_sideset_lower.toInt();
  double sideset_upper = string_sideset_upper.toInt();

  std::vector<int> increments;
  std::vector<int> nodes;
  std::vector<int> blocks;
  std::vector<int> sidesets;

  if((!increment_lower==0)&&(!increment_upper==0))
  { 
    for (size_t i = increment_lower; i <= increment_upper; i++)
    {
      increments.push_back(i);
    }
  } else if ((increment_lower==0)&&(!increment_upper==0))
  {
    for (size_t i = 1; i <= increment_upper; i++)
    {
      increments.push_back(i);
    }
  } else if ((!increment_lower==0)&&(increment_upper==0))
  {
    std::vector<int> total_increments = ccx_iface->frd_get_total_increments(current_job_id);
    if (!total_increments.empty())
    {
      auto max_increment = std::max_element(total_increments.begin(), total_increments.end());
      int increment_max = *max_increment;
      for (size_t i = increment_lower; i <= increment_max; i++)
      {
        increments.push_back(i);
      }
    }
  } else if ((increment_lower==0)&&(increment_upper==0))
  {
    std::vector<int> total_increments = ccx_iface->frd_get_total_increments(current_job_id);
    if (!total_increments.empty())
    {
      auto max_increment = std::max_element(total_increments.begin(), total_increments.end());
      int increment_max = *max_increment;
      for (size_t i = 1; i <= increment_max; i++)
      {
        increments.push_back(i);
      }
    }
  } else {
    return;
  }

  if((!node_lower==0)&&(!node_upper==0))
  { 
    for (size_t i = node_lower; i <= node_upper; i++)
    {
      nodes.push_back(i);
    }
  } else if ((node_lower==0)&&(!node_upper==0))
  {
    for (size_t i = 1; i <= node_upper; i++)
    {
      nodes.push_back(i);
    }
  } else if ((!node_lower==0)&&(node_upper==0))
  {
    std::vector<int> total_nodes = CubitInterface::get_nodeset_id_list();
    if(!total_nodes.empty())
    {
      auto max_node = std::max_element(total_nodes.begin(), total_nodes.end());
      int node_max = *max_node;
      for (size_t i = node_lower; i <= node_max; i++)
      {
        nodes.push_back(i);
      }
    }
  } else if ((node_lower==0)&&(node_upper==0))
  {
    std::vector<int> total_nodes = CubitInterface::get_nodeset_id_list();
    if(!total_nodes.empty())
    {
      auto max_node = std::max_element(total_nodes.begin(), total_nodes.end());
      int node_max = *max_node;
      for (size_t i = 1; i <= node_max; i++)
      {
        nodes.push_back(i);
      }
    }
  } else {
    return;
  }

  if((!block_lower==0)&&(!block_upper==0))
  { 
    for (size_t i = block_lower; i <= block_upper; i++)
    {
      blocks.push_back(i);
    }
  } else if ((block_lower==0)&&(!block_upper==0))
  {
    for (size_t i = 1; i <= block_upper; i++)
    {
      blocks.push_back(i);
    }
  } else if ((!block_lower==0)&&(block_upper==0))
  {
    std::vector<int> total_blocks = ccx_iface->get_blocks();
    if (!total_blocks.empty())
    {
      auto max_block = std::max_element(total_blocks.begin(), total_blocks.end());
      int block_max = *max_block;
      for (size_t i = block_lower; i <= block_max; i++)
      {
        blocks.push_back(i);
      }
    }
  } else if ((block_lower==0)&&(block_upper==0))
  {
    std::vector<int> total_blocks = ccx_iface->get_blocks();
    if (!total_blocks.empty())
    {
      auto max_block = std::max_element(total_blocks.begin(), total_blocks.end());
      int block_max = *max_block;
      for (size_t i = 1; i <= block_max; i++)
      {
        blocks.push_back(i);
      }
    }
  } else {
    return;
  }

  if((!sideset_lower==0)&&(!sideset_upper==0))
  { 
    for (size_t i = sideset_lower; i <= sideset_upper; i++)
    {
      sidesets.push_back(i);
    }
  } else if ((sideset_lower==0)&&(!sideset_upper==0))
  {
    for (size_t i = 1; i <= sideset_upper; i++)
    {
      sidesets.push_back(i);
    }
  } else if ((!sideset_lower==0)&&(sideset_upper==0))
  {
    std::vector<int> total_sidesets = CubitInterface::get_sideset_id_list();
    if (!total_sidesets.empty())
    {
      auto max_sideset = std::max_element(total_sidesets.begin(), total_sidesets.end());
      int sideset_max = *max_sideset;
      for (size_t i = sideset_lower; i <= sideset_max; i++)
      {
        sidesets.push_back(i);
      }
    }
  } else if ((sideset_lower==0)&&(sideset_upper==0))
  {
    std::vector<int> total_sidesets = CubitInterface::get_sideset_id_list();
    if (!total_sidesets.empty())
    {
      auto max_sideset = std::max_element(total_sidesets.begin(), total_sidesets.end());
      int sideset_max = *max_sideset;
      for (size_t i = 1; i <= sideset_max; i++)
      {
        sidesets.push_back(i);
      }
    }
  } else {
    return;
  }

  this->update_result(increments, nodes, blocks, sidesets);
}

void JobsMonitorFRD::result_block_clicked(QListWidgetItem* item)
{
 std::string result_block;
 result_block = item->text().toStdString();
 this->update_component(result_block);
 this->current_block = item;
}

void JobsMonitorFRD::result_block_changed(QListWidgetItem* current_item, QListWidgetItem* prev_item)
{
  if (current_item!=nullptr)
  {
    this->selectListItem(current_item);
    this->result_block_clicked(current_item);
  }
}

void JobsMonitorFRD::component_clicked(QListWidgetItem* component)
{
  this->current_component = component;
}

void JobsMonitorFRD::component_changed(QListWidgetItem* current_item, QListWidgetItem* prev_item)
{
  if (current_item!=nullptr)
  {
    this->selectListItem(current_item);
    this->component_clicked(current_item);
  }
}

QListWidgetItem* JobsMonitorFRD::get_current_block() const
{
  return this->current_block;
}

QListWidgetItem* JobsMonitorFRD::get_current_component() const
{
  return this->current_component;
}