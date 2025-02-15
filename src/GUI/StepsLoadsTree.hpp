#ifndef STEPSLOADSTREE_HPP
#define STEPSLOADSTREE_HPP

#include <QObject>
#include <QTreeWidgetItem>
#include <QIcon>

class CalculiXCoreInterface;
class StepsLoadsForcesTree;
class StepsLoadsPressuresTree;
class StepsLoadsHeatfluxesTree;
class StepsLoadsGravityTree;
class StepsLoadsCentrifugalTree;
class StepsLoadsTrajectoryTree;
class StepsLoadsFilmTree;
class StepsLoadsRadiationTree;
class StepsLoadsSurfaceTractionTree;

class StepsLoadsTree : public QObject, public QTreeWidgetItem
{
  Q_OBJECT

public:
  StepsLoadsTree(QTreeWidgetItem *parent);
  ~StepsLoadsTree();

  void initialize(int step_id_init);

  void clear(); // remove all children from tree 

  void update(); // updates the children from the tree

private:
  bool isInitialized;
  int step_id = -1;

  CalculiXCoreInterface *ccx_iface;
  StepsLoadsForcesTree *myStepsLoadsForcesTree;
  StepsLoadsPressuresTree *myStepsLoadsPressuresTree;
  StepsLoadsHeatfluxesTree *myStepsLoadsHeatfluxesTree;
  StepsLoadsGravityTree *myStepsLoadsGravityTree;
  StepsLoadsCentrifugalTree *myStepsLoadsCentrifugalTree;
  StepsLoadsTrajectoryTree *myStepsLoadsTrajectoryTree;
  StepsLoadsFilmTree *myStepsLoadsFilmTree;
  StepsLoadsRadiationTree *myStepsLoadsRadiationTree;
  StepsLoadsSurfaceTractionTree *myStepsLoadsSurfaceTractionTree;
};

#endif // STEPSLOADSTREE_HPP