#ifndef LOADSTRAJECTORYTREE_HPP
#define LOADSTRAJECTORYTREE_HPP

#include <QObject>
#include <QTreeWidgetItem>
#include <QIcon>

class CalculiXCoreInterface;

class LoadsTrajectoryTree : public QObject, public QTreeWidgetItem
{
  Q_OBJECT

public:
  LoadsTrajectoryTree(QTreeWidgetItem *parent);
  ~LoadsTrajectoryTree();

  void initialize();

  void clear(); // remove all children from tree 

  void update(); // updates the children from the tree

private:
  bool isInitialized;

  void addLoad(QString load_id, QString load_name); // adds a new load to the tree
  void removeLoad(QTreeWidgetItem *load); // removes the load from to the tree

  int get_child_id(std::string load_id); // check if the item for the given load_id exists, returns the id or -1 if failed;

  CalculiXCoreInterface *ccx_iface;
};

#endif // LOADSTRAJECTORYTREE_HPP
