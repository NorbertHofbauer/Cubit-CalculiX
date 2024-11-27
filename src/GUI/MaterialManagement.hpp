#ifndef MATERIALMANAGEMENT_HPP
#define MATERIALMANAGEMENT_HPP

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

class CalculiXCoreInterface;
class MaterialManagementItem;
class MaterialManagementElasticCard;
class MaterialManagementPlasticCard;
class MaterialManagementDensityCard;
class MaterialManagementSpecificHeatCard;
class MaterialManagementExpansionCard;
class MaterialManagementConductivityCard;

class MaterialManagement : public QWidget
{
  Q_OBJECT
  
public:
  MaterialManagement();
  ~MaterialManagement();

  CalculiXCoreInterface *ccx_iface;
  
  void clear(); // remove all data
  void update();
  void update_cubit(); //update cubit materials
  void update_materiallibrary(); //update library materials

  void addMaterial(QString material_id, QString material_name); // adds a new material to the tree
  void removeMaterial(MaterialManagementItem *material); // removes the material from to the tree
  int get_child_id(std::string material_id); // check if the item for the given material_id exists, returns the id or -1 if failed;
  void createListItems(MaterialManagementItem *material); // creates the list items for selected material
  void removeListItems(); // removes current list items
  void switchListItem(QListWidget* source, QListWidget* target); // switches the current item from sry list to target list
  void selectListItem(QListWidgetItem* item); // unselect all list items except the given
  void loadWidget(QListWidgetItem* item); // load Widget for given list item
  void setMaterial(QString material_id);
  void printproperties(); // prints out material with all properties
  // cards

private slots:
  void on_pushButton_ok_clicked(bool);
  void on_pushButton_apply_clicked(bool);
  void on_pushButton_close_clicked(bool);
  void on_pushButton_new_clicked(bool);
  void on_pushButton_delete_clicked(bool);
  void on_pushButton_add_clicked(bool);
  void on_pushButton_remove_clicked(bool);
  void material_clicked(QTreeWidgetItem* item, int column);
  void material_changed(QTreeWidgetItem* current_item, QTreeWidgetItem* prev_item);
  // cards
  void material_card_clicked(QListWidgetItem* item);
  void material_card_doubleclicked(QListWidgetItem* item);
  void material_card_changed(QListWidgetItem* current_item, QListWidgetItem* prev_item);
  
private:
  std::string log;
  MaterialManagementItem* material_item;
  MaterialManagementItem* current_material_item;
  QGridLayout* gridLayout;
  QHBoxLayout* boxLayout_window;
  QVBoxLayout* boxLayout_material1;
  QVBoxLayout* boxLayout_material2;
  QVBoxLayout* boxLayout_material_cards1;
  QVBoxLayout* boxLayout_material_cards2;
  QVBoxLayout* boxLayout_material_cards3;
  QVBoxLayout* boxLayout_materiallibrary1;
  QVBoxLayout* boxLayout_materiallibrary2;
  QVBoxLayout* boxLayout_widget;
  QPushButton* pushButton_ok;
  QPushButton* pushButton_apply;
  QPushButton* pushButton_close;
  QPushButton* pushButton_new;
  QPushButton* pushButton_delete;
  QPushButton* pushButton_rename;
  QPushButton* pushButton_export;
  QPushButton* pushButton_add;
  QPushButton* pushButton_remove;
  QPushButton* pushButton_library_import;
  QPushButton* pushButton_library_new;
  QPushButton* pushButton_library_delete;
  QPushButton* pushButton_library_rename;
  QPushButton* pushButton_library_new_group;
  QPushButton* pushButton_library_delete_group;
  QPushButton* pushButton_library_rename_group;
  QLabel* label_material;
  QLabel* label_available;
  QLabel* label_used;
  QLabel* label_materiallibrary;
  //QLabel* label_materiallibrary_material;
  QLabel* label_materiallibrary_group;
  QTreeWidget* tree_material;
  QListWidget* list_available;
  QListWidget* list_used;
  QTreeWidget* tree_materiallibrary;
  QListWidgetItem* list_elastic;
  QListWidgetItem* list_plastic;
  QListWidgetItem* list_density;
  QListWidgetItem* list_specific_heat;
  QListWidgetItem* list_expansion;
  QListWidgetItem* list_conductivity;
  // cards
  QFrame* card_frame;
  MaterialManagementElasticCard* elastic_widget;
  MaterialManagementPlasticCard* plastic_widget;
  MaterialManagementDensityCard* density_widget;
  MaterialManagementSpecificHeatCard* specific_heat_widget;
  MaterialManagementExpansionCard* expansion_widget;
  MaterialManagementConductivityCard* conductivity_widget;
};

#endif // MATERIALMANAGEMENT_HPP
