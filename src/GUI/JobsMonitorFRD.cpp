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
  textField1 = new QLineEdit;
  textField2 = new QLineEdit;
  textField3 = new QLineEdit;
  textField4 = new QLineEdit;
  textField1->setPlaceholderText("Time from");
  textField2->setPlaceholderText("Time until");
  /* textField1->setRange(0.0, 1.0); //Time from until einfügen
  textField2->setRange(0.0, 1.0);
  textField1->setDecimals(3);
  textField2->setDecimals(3);
  textField1->setSingleStep(0.05);
  textField2->setSingleStep(0.05); */
  textField3->setPlaceholderText("Node from");
  textField4->setPlaceholderText("Node until");
  pushButton_apply_filter = new QPushButton("Apply Filter");
  boxLayout_filter->addWidget(textField1);
  boxLayout_filter->addWidget(textField2);
  boxLayout_filter->addWidget(textField3);
  boxLayout_filter->addWidget(textField4);
  boxLayout_filter->addWidget(pushButton_apply_filter);

  // card widgets
  list_result = new QListWidget();
  list_result->setMinimumSize(700,350);
  list_result->setLineWidth(1);
  list_result->setMidLineWidth(0);
  list_result->setFrameStyle(QFrame::Box | QFrame::Raised);
  boxLayout_widget->addWidget(list_result);

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

void JobsMonitorFRD::update_result(std::vector<int> node_ids, int total_increment)
{
  if(current_job_id == -1)
  {
    return;
  }

  std::string current_result_block = get_current_block()->text().toStdString();
  std::string current_component = get_current_component()->text().toStdString();

  for (size_t i = 0; i < node_ids.size(); i++)
  {
    int node_id = node_ids[i];

    double node_result = ccx_iface->frd_get_node_value(current_job_id, node_id, total_increment, current_result_block ,current_component);

    this->addListItem(std::to_string(total_increment) + " " + std::to_string(node_id) + " " + std::to_string(node_result),list_result);
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

  this->removeListItems_from_List(list_result);

  QString string_time_lower = textField1->text();
  QString string_time_upper = textField2->text();
  QString string_node_lower = textField3->text();
  QString string_node_upper = textField4->text();
  
  double time_lower = string_time_lower.toDouble(); //Clemens what if not a number?
  double time_upper = string_time_upper.toDouble();
  double node_lower = string_node_lower.toDouble();
  double node_upper = string_node_upper.toDouble();

  std::vector<int> times; //Clemens how to hendl time?
  std::vector<int> nodes;

  std::string current_result_block = get_current_block()->text().toStdString();
  std::string current_component = get_current_component()->text().toStdString();

  if((!string_time_lower.isEmpty())&&(!string_time_upper.isEmpty()))
  { 
    for (size_t i = time_lower; i <= time_upper; i++)
    {
      times.push_back(i);
    }
  } else if ((string_time_lower.isEmpty())&&(!string_time_upper.isEmpty()))
  {
    for (size_t i = 1; i <= time_upper; i++)
    {
      times.push_back(i);
    }
  } else if ((!string_time_lower.isEmpty())&&(string_time_upper.isEmpty()))
  {
    std::vector<int> increments = ccx_iface->frd_get_total_increments(current_job_id);
    if (!increments.empty())
    {
      auto max_it = std::max_element(increments.begin(), increments.end());
      int time_max = *max_it;
      for (size_t i = time_lower; i <= time_max; i++)
      {
        times.push_back(i);
      }
    }
  } else {
    return;
  }

  for (size_t i = 0; i < times.size(); i++)
  {
    int total_increment = times[i];
    if((!string_node_lower.isEmpty())&&(!string_node_upper.isEmpty()))
    { 
      nodes = ccx_iface->frd_get_node_ids_between_values(current_job_id, total_increment, current_result_block, current_component, node_lower, node_upper);
    } else if ((string_node_lower.isEmpty())&&(!string_node_upper.isEmpty()))
    {
      nodes = ccx_iface->frd_get_node_ids_smaller_value(current_job_id, total_increment, current_result_block, current_component, node_upper);
    } else if ((!string_node_lower.isEmpty())&&(string_node_upper.isEmpty()))
    {
      nodes = ccx_iface-> frd_get_node_ids_greater_value(current_job_id, total_increment, current_result_block, current_component, node_lower);
    } else {
      return;
    }

    this->update_result(nodes, total_increment); // Clemens if in loop, only the last one is shown in the window
  }
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