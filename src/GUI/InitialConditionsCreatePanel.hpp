#ifndef INITIALCONDITIONSCREATEPANEL_HPP
#define INITIALCONDITIONSCREATEPANEL_HPP

#include <QWidget>
#include <QList>
#include <QPushButton>
#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QComboBox>
#include <QLabel>
#include <QSpacerItem>
#include <QTableWidget>
#include <QLineEdit>
#include <QRadioButton>
#include <QCheckBox>

class CalculiXCoreInterface;

class InitialConditionsCreatePanel : public QWidget
{
  Q_OBJECT
  
public:
  explicit InitialConditionsCreatePanel(QWidget *parent = 0);
  ~InitialConditionsCreatePanel();

  bool isInitialized;
  CalculiXCoreInterface *ccx_iface;
  
private slots:
  void on_pushButton_apply_clicked(bool);

private:
  std::string log;

  QGridLayout* GridLayout;
  QVBoxLayout* VBoxLayout;
  QSpacerItem* vertical_spacer;
  QPushButton* pushButton_apply;
  QHBoxLayout* HBoxLayout_pushButton_apply;
  QSpacerItem* horizontal_spacer_pushButton_apply;
  //QHBoxLayout* HBoxLayout_1;
  QHBoxLayout* HBoxLayout_2;
  //QLabel* label_1;
  QLabel* label_2;
  //QLineEdit* lineEdit_1;
  QComboBox* comboBox_2;
};

#endif // INITIALCONDITIONSCREATEPANEL_HPP