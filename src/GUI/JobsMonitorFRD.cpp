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
  boxLayout_increment = new QVBoxLayout();
  boxLayout_filter = new QVBoxLayout();
  boxLayout_widget = new QVBoxLayout();
  boxLayout_pages = new QHBoxLayout();
  gridLayout->addLayout(boxLayout_window,2,4, Qt::AlignRight);
  gridLayout->addLayout(boxLayout_result_block,0,0, Qt::AlignTop);
  gridLayout->addLayout(boxLayout_component,0,1, Qt::AlignTop);
  gridLayout->addLayout(boxLayout_increment,0,2, Qt::AlignTop);
  gridLayout->addLayout(boxLayout_filter,0,3, Qt::AlignTop);
  gridLayout->addLayout(boxLayout_widget,1,0,1,4, Qt::AlignTop);
  gridLayout->addLayout(boxLayout_pages,2,0,1,4, Qt::AlignTop);

  // buttons
  pushButton_refresh = new QPushButton();
  pushButton_refresh->setText("Refresh");
  boxLayout_window->addWidget(pushButton_refresh);

  pushButton_plot = new QPushButton();
  pushButton_plot->setText("Plot");
  boxLayout_window->addWidget(pushButton_plot);

  // labels
  label_result_block = new QLabel();
  label_result_block->setText("Result Blocks");
  boxLayout_result_block->addWidget(label_result_block);

  label_component = new QLabel();
  label_component->setText("Components");
  boxLayout_component->addWidget(label_component);

  label_increment = new QLabel();
  label_increment->setText("Increments");
  boxLayout_increment->addWidget(label_increment);

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

  list_increment = new QListWidget();
  list_increment->setFrameShape(QFrame::Box);
  list_increment->setFrameShadow(QFrame::Raised);
  boxLayout_increment->addWidget(list_increment);

  combobox_filter1 = new QComboBox();
  combobox_filter1->addItem(" ");
  combobox_filter1->addItem("Block");
  combobox_filter1->addItem("Sideset");
  combobox_filter1->addItem("Nodeset");
  combobox_filter1->addItem("Node");
  combobox_filter2 = new QComboBox();
  boxLayout_filter->addWidget(combobox_filter1);

  pushButton_apply_filter = new QPushButton("Apply Filter");
  boxLayout_filter->addWidget(pushButton_apply_filter);

  //table
  table_result = new QTableWidget();
  table_result->setMinimumSize(700,350);
  table_result->setLineWidth(1);
  table_result->setMidLineWidth(0);
  table_result->setFrameStyle(QFrame::Box | QFrame::Raised);
  table_counter = new QLabel;
  pushButton_prev = new QPushButton("Previous Results");
  pushButton_next = new QPushButton("Next Results");
  boxLayout_widget->addWidget(table_result);
  boxLayout_pages->addWidget(pushButton_prev);
  boxLayout_pages->addWidget(table_counter);
  boxLayout_pages->addWidget(pushButton_next);

  // Signals
  QObject::connect(pushButton_refresh, SIGNAL(clicked(bool)),this,  SLOT(on_pushButton_refresh_clicked(bool)));
  QObject::connect(pushButton_plot, SIGNAL(clicked(bool)),this,  SLOT(on_pushButton_plot_clicked(bool)));
  QObject::connect(pushButton_apply_filter, SIGNAL(clicked(bool)),this,  SLOT(on_pushButton_apply_filter_clicked(bool)));
  QObject::connect(list_result_block, SIGNAL(itemClicked(QListWidgetItem*)),this,  SLOT(result_block_clicked(QListWidgetItem*)));
  QObject::connect(list_result_block, SIGNAL(currentItemChanged(QListWidgetItem*, QListWidgetItem*)),this,  SLOT(result_block_changed(QListWidgetItem*,QListWidgetItem*)));
  QObject::connect(list_component, SIGNAL(itemClicked(QListWidgetItem*)),this,  SLOT(component_clicked(QListWidgetItem*)));
  QObject::connect(list_component, SIGNAL(currentItemChanged(QListWidgetItem*, QListWidgetItem*)),this,  SLOT(component_changed(QListWidgetItem*,QListWidgetItem*)));
  QObject::connect(pushButton_prev, SIGNAL(clicked(bool)), this, SLOT(on_pushButton_previous_clicked(bool)));
  QObject::connect(pushButton_next, SIGNAL(clicked(bool)), this, SLOT(on_pushButton_next_clicked(bool)));
  QObject::connect(combobox_filter1, SIGNAL(currentIndexChanged(int)), this, SLOT(update_filter(int)));

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

  list_result_block->clear();
  list_component->clear();
  list_increment->clear();
  table_result->setRowCount(0);
  table_result->setColumnCount(0);
  this->current_block = nullptr;
  this->current_component = nullptr;

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
  
  list_component->clear();

  std::vector<std::string> components = ccx_iface->frd_get_result_block_components(current_job_id, result_block);
  components.insert(components.begin(), "all");

  for (size_t i = 0; i < components.size(); i++)
  {
    this->addListItem(components[i],list_component);
  }
}

void JobsMonitorFRD::update_increment()
{
  if (current_job_id ==-1)
  {
    return;
  }
  
  list_increment->clear();

  std::vector<int> increments = ccx_iface->frd_get_total_increments(current_job_id);
  std::vector<std::variant<int, std::string>> total_increments;
  total_increments.push_back("all");
  for (int increment : increments)
  {
    total_increments.push_back(increment);
  }
  for (const auto& item : total_increments)
  {
    if (std::holds_alternative<int>(item))
    {
      this->addListItem(QString::number(std::get<int>(item)).toStdString(), list_increment);
    } else {
      this->addListItem(std::get<std::string>(item), list_increment);
    }
  }
}

void JobsMonitorFRD::update_filter(int index) //Clemens updatet nicht, wenn filter geändert wird 
{
  /* if (this->combobox2_exists==true)
  {
    this->combobox2_exists = false;
    this->textFields_exists = false;
    removeWidgetFromLayout(boxLayout_filter, combobox_filter2);
  } else if (this->textFields_exists==true)
  {
    this->combobox2_exists = false;
    this->textFields_exists = false;
    removeWidgetFromLayout(boxLayout_filter, combobox_filter2);
    removeWidgetFromLayout(boxLayout_filter, textField1);
    removeWidgetFromLayout(boxLayout_filter, textField2);
    removeWidgetFromLayout(boxLayout_filter, label_filter_lower);
    removeWidgetFromLayout(boxLayout_filter, label_filter_upper);
  } else {
    return;
  } */

  std::string applied_filter = combobox_filter1->currentText().toStdString();
  if (applied_filter==" ")
  {
    combobox2_exists = false;
    textFields_exists = false;
    return;
  } else if (applied_filter=="Block")
  {
    combobox2_exists = true;
    textFields_exists = false;
    combobox_filter2->addItem(" ");
    std::vector<int> blocks = ccx_iface->get_blocks();
    for (size_t i = 1; i < blocks.size(); i++)
    {
      QString block_name = QString::fromStdString(ccx_iface->get_block_name(i));
      combobox_filter2->addItem(block_name);
    }
    boxLayout_filter->addWidget(combobox_filter2);
  } else if (applied_filter=="Sideset")
  {
    combobox2_exists = true;
    textFields_exists = false;
    combobox_filter2->addItem(" ");
    std::vector<int> sidesets = CubitInterface::get_sideset_id_list();
    for (size_t i = 1; i < sidesets.size(); i++)
    {
      QString sideset_name = QString::fromStdString(ccx_iface->get_sideset_name(i));
      combobox_filter2->addItem(sideset_name);
    }
    boxLayout_filter->addWidget(combobox_filter2);
  } else if (applied_filter=="Nodeset")
  {
    combobox2_exists = true;
    textFields_exists = false;
    combobox_filter2->addItem(" ");
    std::vector<int> nodesets = CubitInterface::get_nodeset_id_list();
    for (size_t i = 1; i < nodesets.size(); i++)
    {
      QString nodeset_name = QString::fromStdString(ccx_iface->get_nodeset_name(i));
      combobox_filter2->addItem(nodeset_name);
    }
    boxLayout_filter->addWidget(combobox_filter2);
  } else if (applied_filter=="Node")
  {
    combobox2_exists = false;
    textFields_exists = true;
    textField1 = new QSpinBox;
    textField2 = new QSpinBox;
    label_filter_lower = new QLabel;
    label_filter_lower->setText("From");
    label_filter_upper = new QLabel;
    label_filter_upper->setText("Until");
    boxLayout_filter->addWidget(label_filter_lower);
    boxLayout_filter->addWidget(textField1);
    boxLayout_filter->addWidget(label_filter_upper);
    boxLayout_filter->addWidget(textField2);
  }
}

void JobsMonitorFRD::update_result()
{
  if(current_job_id == -1)
  {
    return;
  }

  table_result->setRowCount(0);
  table_result->setColumnCount(0);

  if (this->current_block==nullptr)
  {
    return;
  }
  if(this->current_component==nullptr)
  {
    return;
  }
  
  std::string current_result_block = this->current_block->text().toStdString();
  std::string current_component = this->current_component->text().toStdString();
  std::vector<int> nodes;
  std::string applied_filter = combobox_filter1->currentText().toStdString();
  
  if (applied_filter==" ")
  {
    return;
  }
  if (this->combobox2_exists==true)
  {
    std::string applied_node = combobox_filter2->currentText().toStdString();
    if (applied_node==" ")
    {
      return;
    }
    if (applied_filter=="Block")
    {
      std::string name = combobox_filter2->currentText().toStdString();
      int id = CubitInterface::get_id_from_name(name);
    } else if (applied_filter=="Sideset")
    {
      std::string name = combobox_filter2->currentText().toStdString();
      int id = CubitInterface::get_id_from_name(name);
      std::string int_list = "all in sideset " + std::to_string(id);
      nodes = CubitInterface::parse_cubit_list("node",int_list);
    } else if (applied_filter=="Nodeset")
    {
      std::string name = combobox_filter2->currentText().toStdString();
      int id = CubitInterface::get_id_from_name(name);
      nodes = CubitInterface::get_nodeset_nodes_inclusive(id);
    } else {
      return;
    }
  }
  
  if (this->textFields_exists==true)
  {
    QString string_filter_lower = textField1->text();
    QString string_filter_upper = textField2->text();
    
    double filter_lower = string_filter_lower.toInt();
    double filter_upper = string_filter_upper.toInt();

    if ((!filter_lower==0)&&(!filter_upper==0))
    {
      for (size_t i = filter_lower; i <= filter_upper; i++)
      {
        nodes.push_back(i);
      }
    } else if ((filter_lower==0)&&(!filter_upper==0))
    {
      for (size_t i = 1; i <= filter_upper; i++)
      {
        nodes.push_back(i);
      }
    } else if ((!filter_lower==0)&&(filter_upper==0))
    {
      std::vector<int> total_nodes = CubitInterface::get_nodeset_id_list();
      if(!total_nodes.empty())
      {
        auto max_node = std::max_element(total_nodes.begin(), total_nodes.end());
        int node_max = *max_node;
        for (size_t i = filter_lower; i <= node_max; i++)
        {
          nodes.push_back(i);
        }
      } else {
        return;
      }
    } else if ((filter_lower==0)&&(filter_upper==0))
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
      } else {
        return;
      }
    } else {
      return;
    }
  }

  std::vector<std::vector<double>> results;

  current_increment = new QListWidgetItem;
  current_increment = list_increment->currentItem();
  if (current_increment==nullptr)
  {
    return;
  }
  QString current_increment_text = current_increment->text();
  std::string current_increment_string = current_increment_text.toStdString();
  int current_increment_int = current_increment_text.toInt();
  
  if (current_component=="all")
  {
    return;
    //Clemens components all

  } else {
    if (current_increment_string=="all")
    {
      std::vector<int> increments = ccx_iface->frd_get_total_increments(current_job_id);
      if (!increments.empty())
      {
        for (int i : nodes)
        {
          for (int j : increments)
          {
            results.push_back({i,j});
          }
        }

        if (results.size()==0)
        {
          return;
        }

        for (size_t i = 0; i < results.size(); i++)
        {
          double increment_time = ccx_iface->frd_get_time_from_total_increment(current_job_id, results[i][0]);
          results[i].push_back(increment_time);

          double node_result = ccx_iface->frd_get_node_value(current_job_id, results[i][0] , current_increment_int, current_result_block, current_component);
          results[i].push_back(node_result);
        }
      } else {
        return;
      }
    } else {
      for (size_t i = 0; i < nodes.size(); i++)
      {
        std::vector<double> temp;
        temp.push_back(nodes[i]);
        results.push_back(temp);
      }

      if (results.size()==0)
      {
        return;
      }

      for (size_t i = 0; i < results.size(); i++)
      {
        double node_result = ccx_iface->frd_get_node_value(current_job_id, results[i][0] , current_increment_int, current_result_block, current_component);
        results[i].push_back(node_result);
      }
    }
  }

  int items_per_page = 50; //also adjust in on_pushButton_next_clicked
  int start = this->current_page * items_per_page;
  this->results_size = results.size();
  int end = std::min(start + items_per_page, results_size);

  table_result->setSortingEnabled(true);
  table_result->setRowCount(std::min(50,results_size-start));
  table_result->setColumnCount(results[0].size());
  table_result->setEditTriggers(QAbstractItemView::NoEditTriggers);
  table_counter->setText(QString::fromStdString("Results " + std::to_string(start+1) + "-" + std::to_string(end) + " of " + std::to_string(results_size)));

  for (size_t i = start; i < end; i++)
  {
    for (size_t ii = 0; ii < results[0].size(); ii++)
    {
      if (current_increment_string=="all")
      {
        if (ii > 1)
        {
          QString formatted_result_value = QString::number(results[i][ii], 'f', 6);

          QTableWidgetItem* item = new QTableWidgetItem(formatted_result_value);
          item->setData(Qt::DisplayRole, results[i][ii]);
          table_result->setItem(i-start, ii, item);
        } else {
          QTableWidgetItem* item = new QTableWidgetItem;
          item->setData(Qt::DisplayRole, results[i][ii]);
          table_result->setItem(i-start, ii, item);
        }
        table_result->setHorizontalHeaderLabels(QStringList() << "Node Id" << "Increment Id" << "Increment Time" << QString::fromStdString(current_component));
      } else {
        if (ii > 1)
        {
          QString formatted_result_value = QString::number(results[i][ii], 'f', 6);

          QTableWidgetItem* item = new QTableWidgetItem(formatted_result_value);
          item->setData(Qt::DisplayRole, results[i][ii]);
          table_result->setItem(i-start, ii, item);
        } else {
          QTableWidgetItem* item = new QTableWidgetItem;
          item->setData(Qt::DisplayRole, results[i][ii]);
          table_result->setItem(i-start, ii, item);
        }
        table_result->setHorizontalHeaderLabels(QStringList() << "Node Id" << QString::fromStdString(current_component));
      }
    }
  }
}

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

  this->current_page = 0;
  filter.clear();

  this->update_result();
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
  this->update_increment();
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

void JobsMonitorFRD::on_pushButton_previous_clicked(bool)
{
  if (current_page>0)
  {
    this->current_page = current_page-1;
    update_result();
  }
}

void JobsMonitorFRD::on_pushButton_next_clicked(bool)
{
  if (current_page < std::ceil(results_size/50))
  {
    current_page = current_page+1;
    update_result();
  }
}

void JobsMonitorFRD::removeWidgetFromLayout(QVBoxLayout* layout, QWidget* widget) {
  for (int i = 0; i < layout->count(); ++i) {
    QLayoutItem* item = layout->itemAt(i);
    if (item->widget() == widget) {
      layout->takeAt(i);
      delete item->widget();
      delete item;
      break;
    }
  }
}