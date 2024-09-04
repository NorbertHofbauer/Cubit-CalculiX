#ifndef JOBSMONITORFRD_HPP
#define JOBSMONITORFRD_HPP

#include <QWidget>
#include <QFrame>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QList>
#include <QPushButton>
#include <QLabel>
#include <QListWidget>
#include <QListWidgetItem>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QMessageBox>
#include <QInputDialog>
#include <QComboBox>
#include <QString>
#include <QStringList>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <algorithm>
#include <QComboBox>
<<<<<<< HEAD
=======
#include <QLineEdit>
>>>>>>> upstream/main
#include <QObject>

class CalculiXCoreInterface;
class JobsMonitorFRDPlot;
class PickWidget;

class JobsMonitorFRD : public QWidget
{
  Q_OBJECT
  
public:
  JobsMonitorFRD();
  ~JobsMonitorFRD();

  CalculiXCoreInterface *ccx_iface;

  int current_job_id = -1;
  
  void clear(); // remove all data
  void update();
  void update_component(std::string result_block);
  void update_increment();
  void update_result();
  void set_current_job_id(int job_id);

  void addListItem(std::string item_name, QListWidget* parent_list); // adds a new item to the list
  void addTableItem(std::string item_name, QTableWidget* parent_list); //adds a new item to the table
  void removeListItem(std::string item_name, QListWidget* parent_list); // removes the item from the list

  void createListItems(); // creates the list items for selected material
  void removeListItems(); // removes current list items
<<<<<<< HEAD
  void selectListItem(QListWidgetItem* item); // unselect all list items except the given
=======

  void removeWidgetFromLayout(QVBoxLayout* layout, QWidget* widget);
>>>>>>> upstream/main

  void removeWidgetFromLayout(QVBoxLayout* layout, QWidget* widget);

private slots:
  void on_pushButton_reset_clicked(bool);
  void on_pushButton_plot_clicked(bool);
<<<<<<< HEAD
  void on_pushButton_apply_filter_clicked(bool);
  void on_pushButton_previous_clicked(bool);
  void on_pushButton_next_clicked(bool);
  void update_filter(int index);
=======
  void on_pushButton_query_results_clicked(bool);
  void on_pushButton_previous_clicked(bool);
  void on_pushButton_next_clicked(bool);
  void update_filter_by_set(int index);
>>>>>>> upstream/main
  void result_block_clicked(QListWidgetItem* item);
  void result_block_changed(QListWidgetItem* current_item, QListWidgetItem* prev_item);
  void component_clicked(QListWidgetItem* item);
  void component_changed(QListWidgetItem* current_item, QListWidgetItem* prev_item);
<<<<<<< HEAD
=======
  void increment_clicked(QListWidgetItem* item);
  void increment_changed(QListWidgetItem* current_item, QListWidgetItem* prev_item);
>>>>>>> upstream/main

private:
  std::string log;
  QGridLayout* gridLayout;
  QVBoxLayout* boxLayout_result_block;
  QVBoxLayout* boxLayout_component;
  QVBoxLayout* boxLayout_increment;
  QVBoxLayout* boxLayout_filter;
<<<<<<< HEAD
  QVBoxLayout* boxLayout_widget;
  QHBoxLayout* boxLayout_pages;
  QPushButton* pushButton_refresh;
  QPushButton* pushButton_plot;
  QPushButton* pushButton_apply_filter;
=======
  QVBoxLayout* boxLayout_filter_by_set;
  QHBoxLayout* boxLayout_filter_by_node;
  QHBoxLayout* boxLayout_result_buttons;
  QVBoxLayout* boxLayout_widget;
  QHBoxLayout* boxLayout_pages;
  QPushButton* pushButton_reset;
  QPushButton* pushButton_plot;
  QPushButton* pushButton_query_results;
>>>>>>> upstream/main
  QPushButton* pushButton_prev;
  QPushButton* pushButton_next;
  QLabel* label_result_block;
  QLabel* label_component;
  QLabel* label_increment;
<<<<<<< HEAD
  QLabel* label_filter;
  QLabel* label_filter_lower;
  QLabel* label_filter_upper;
  QListWidget* list_result_block;
  QListWidget* list_component;
  QListWidget* list_increment;
  QListWidget* list_filter;
=======
  QLabel* label_filter_by_set;
  QLabel* label_filter_by_node;
  QLabel* label_filter_node_id;
  PickWidget* PickWidget_filter_node_id;
  QListWidget* list_result_block;
  QListWidget* list_component;
  QListWidget* list_increment;
  QTableWidget* table_filter_by_set;
>>>>>>> upstream/main
  QTableWidget* table_increment;
  QLabel* table_counter;
  QSpinBox* textField1;
  QSpinBox* textField2;
<<<<<<< HEAD
  QComboBox* combobox_filter1;
  QComboBox* combobox_filter2;
  QListWidgetItem* current_increment;
=======
  QComboBox* combobox_filter_by_set;
  JobsMonitorFRDPlot* PlotWidget;
>>>>>>> upstream/main
 
  // results
  QTableWidget* table_result;

  //storage
<<<<<<< HEAD
  bool combobox2_exists = false;
  bool textFields_exists = false;
  QListWidgetItem* current_block = nullptr; //stores the current block
  QListWidgetItem* current_component = nullptr; //stores the current component
=======
  QListWidgetItem* current_result_block = nullptr; //stores the current block
  QListWidgetItem* current_result_component = nullptr; //stores the current component
  QListWidgetItem* current_increment = nullptr; //stores the current inrement
  int items_per_page = 50;
>>>>>>> upstream/main
  int current_page; //stores the current result page
  std::vector<int> filter;
  int results_size;
};

#endif // JOBSMONITORFRD_HPP