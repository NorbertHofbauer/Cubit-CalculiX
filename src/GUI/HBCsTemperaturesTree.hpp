
#ifndef HBCSTEMPERATURESTREE_HPP
#define HBCSTEMPERATURESTREE_HPP

#include <QObject>
#include <QTreeWidgetItem>
#include <QIcon>

class CalculiXCoreInterface;

class HBCsTemperaturesTree : public QObject, public QTreeWidgetItem
{
  Q_OBJECT

public:
  HBCsTemperaturesTree(QTreeWidgetItem *parent);
  ~HBCsTemperaturesTree();

  void initialize();

  void clear(); // remove all children from tree 

  void update(); // updates the children from the tree

private:
  bool isInitialized;

  void addBC(QString bc_id, QString bc_name); // adds a new bc to the tree
  void removeBC(QTreeWidgetItem *bc); // removes the bc from to the tree

  int get_child_id(std::string bc_id); // check if the item for the given bc_id exists, returns the id or -1 if failed;

  CalculiXCoreInterface *ccx_iface;
};

#endif // HBCSTEMPERATURESTREE_HPP