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
  boxLayout_filter = new QVBoxLayout();
  boxLayout_widget = new QVBoxLayout();
  gridLayout->addLayout(boxLayout_window,2,4, Qt::AlignRight);
  gridLayout->addLayout(boxLayout_result_block,0,0, Qt::AlignTop);
  gridLayout->addLayout(boxLayout_component,0,1, Qt::AlignTop);
/*   gridLayout->addLayout(boxLayout_increment,0,2, Qt::AlignTop); */
  gridLayout->addLayout(boxLayout_filter,0,2, Qt::AlignTop);
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

  label_filter = new QLabel();
  label_filter->setText("Filter");
  boxLayout_filter->addWidget(label_filter);

  // lists
  list_result_block = new QListWidget();
  boxLayout_result_block->addWidget(list_result_block);

  list_component = new QListWidget();
  boxLayout_component->addWidget(list_component);

  list_filter = new QListWidget();
  list_filter->setFrameShape(QFrame::Box);
  list_filter->setFrameShadow(QFrame::Raised);
  label_increment1 = new QLabel("Increment from");
  textField1 = new QLineEdit;
  label_increment2 = new QLabel("Increment until");
  textField2 = new QLineEdit;
  label_node1 = new QLabel("Node from");
  textField3 = new QLineEdit;
  label_node2 = new QLabel("Node until");
  textField4 = new QLineEdit;
  label_block1 = new QLabel("Block from");
  textField5 = new QLineEdit;
  label_block2 = new QLabel("Block until");
  textField6 = new QLineEdit;
  label_sideset1 = new QLabel("Sideset from");
  textField7 = new QLineEdit;
  label_sideset2 = new QLabel("Sideset until");
  textField8 = new QLineEdit;
  pushButton_apply_filter = new QPushButton("Apply Filter");
  boxLayout_filter->addWidget(label_increment1);
  boxLayout_filter->addWidget(textField1);
  boxLayout_filter->addWidget(label_increment2);
  boxLayout_filter->addWidget(textField2);
  boxLayout_filter->addWidget(label_node1);
  boxLayout_filter->addWidget(textField3);
  boxLayout_filter->addWidget(label_node2);
  boxLayout_filter->addWidget(textField4);
  boxLayout_filter->addWidget(pushButton_apply_filter);

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

void JobsMonitorFRD::update_result(std::vector<int> increment_ids, std::vector<int> node_ids)
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

  for (int i : increment_ids) //table looks like: {increment, node, result}
  {
    for (int j : node_ids)
    {
      results.push_back({i,j});
    }
  }

  if (results.size() == 0)
  {
    return;
  }

  table_result->setRowCount(results.size());
  table_result->setColumnCount(results[0].size()+1);

  for (size_t i = 0; i < results.size(); i++)
  {
    double node_result = ccx_iface->frd_get_node_value(current_job_id, results[i][1], results[i][0], current_result_block ,current_component);
    results[i].push_back(node_result);
  }

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
  
  double increment_lower = string_increment_lower.toDouble(); //Clemens what if not a number?
  double increment_upper = string_increment_upper.toDouble();
  double node_lower = string_node_lower.toDouble();
  double node_upper = string_node_upper.toDouble();

  std::vector<int> increments;
  std::vector<int> nodes;

  std::string current_result_block = get_current_block()->text().toStdString();
  std::string current_component = get_current_component()->text().toStdString();

  if((!string_increment_lower.isEmpty())&&(!string_increment_upper.isEmpty()))
  { 
    for (size_t i = increment_lower; i <= increment_upper; i++)
    {
      increments.push_back(i);
    }
  } else if ((string_increment_lower.isEmpty())&&(!string_increment_upper.isEmpty()))
  {
    for (size_t i = 1; i <= increment_upper; i++)
    {
      increments.push_back(i);
    }
  } else if ((!string_increment_lower.isEmpty())&&(string_increment_upper.isEmpty()))
  {
    std::vector<int> increments = ccx_iface->frd_get_total_increments(current_job_id);
    if (!increments.empty())
    {
      auto max_it = std::max_element(increments.begin(), increments.end());
      int time_max = *max_it;
      for (size_t i = increment_lower; i <= time_max; i++)
      {
        increments.push_back(i);
      }
    }
  } else {
    return;
  }

  if((!string_node_lower.isEmpty())&&(!string_node_upper.isEmpty()))
  { 
    for (size_t i = node_lower; i <= node_upper; i++)
    {
      nodes.push_back(i);
    }
  } else if ((string_node_lower.isEmpty())&&(!string_node_upper.isEmpty()))
  {
    for (size_t i = 1; i <= node_upper; i++)
    {
      nodes.push_back(i);
    }
  } else if ((!string_node_lower.isEmpty())&&(string_node_upper.isEmpty()))
  {
    std::vector<int> nodes = CubitInterface::get_nodeset_id_list();
    if(!nodes.empty())
    {
      auto max_node = std::max_element(nodes.begin(), nodes.end());
      int node_max = *max_node;
      for (size_t i = node_lower; i <= node_max; i++)
      {
        nodes.push_back(i);
      }
    }
  } else {
    return;
  }
  this->update_result(increments, nodes);
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