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
#include <QDoubleSpinBox>

class CalculiXCoreInterface;

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
  void update_increment(std::string result_block);
  void update_result(std::vector<int> increment_ids, std::vector<int> node_ids);
  void set_current_job_id(int job_id);

  void addListItem(std::string item_name, QListWidget* parent_list); // adds a new item to the list
  void addTableItem(std::string item_name, QTableWidget* parent_list); //adds a new item to the table
  void removeListItem(std::string item_name, QListWidget* parent_list); // removes the item from the list

  void createListItems(); // creates the list items for selected material
  void removeListItems(); // removes current list items
  void removeListItems_from_List(QListWidget* list); // removes current list items from list
  void removeTableItems_from_Table(QTableWidget* table); // removes current table items from table
  void selectListItem(QListWidgetItem* item); // unselect all list items except the given

private slots:
  void on_pushButton_refresh_clicked(bool);
  void on_pushButton_plot_clicked(bool);
  void on_pushButton_apply_filter_clicked(bool);
  void result_block_clicked(QListWidgetItem* item);
  void result_block_changed(QListWidgetItem* current_item, QListWidgetItem* prev_item);
  void component_clicked(QListWidgetItem* item);
  void component_changed(QListWidgetItem* current_item, QListWidgetItem* prev_item);

  QListWidgetItem* get_current_block() const;
  QListWidgetItem* get_current_component() const;
  
private:
  std::string log;
  QGridLayout* gridLayout;
  QHBoxLayout* boxLayout_window;
  QVBoxLayout* boxLayout_result_block;
  QVBoxLayout* boxLayout_component;
  QVBoxLayout* boxLayout_increment;
  QVBoxLayout* boxLayout_widget;
  QVBoxLayout* boxLayout_filter;
  QHBoxLayout* time1_layout;
  QHBoxLayout* time2_layout;
  QHBoxLayout* node1_layout;
  QHBoxLayout* node2_layout;
  QPushButton* pushButton_refresh;
  QPushButton* pushButton_plot;
  QPushButton* pushButton_apply_filter;
  QLabel* label_result_block;
  QLabel* label_component;
  QLabel* label_increment;
  QLabel* label_filter;
  QLabel* label_result;
  QLabel* label_increment1;
  QLabel* label_increment2;
  QLabel* label_node1;
  QLabel* label_node2;
  QLabel* label_block1;
  QLabel* label_block2;
  QLabel* label_sideset1;
  QLabel* label_sideset2;
  QListWidget* list_result_block;
  QListWidget* list_component;
  QListWidget* list_filter;
  QTableWidget* table_increment;
  QLineEdit* textField1;
  QLineEdit* textField2;
  QLineEdit* textField3;
  QLineEdit* textField4;
  QLineEdit* textField5;
  QLineEdit* textField6;
  QLineEdit* textField7;
  QLineEdit* textField8;

  // results
  QTableWidget* table_result;
  QListWidgetItem* current_block = nullptr;  //store the current block
  QListWidgetItem* current_component = nullptr;  //store the current component
};

#endif // JOBSMONITORFRD_HPP