#ifndef INITIALCONDITIONSMODIFYPANEL_HPP
#define INITIALCONDITIONSMODIFYPANEL_HPP

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

class InitialConditionsModifyPanel : public QWidget
{
  Q_OBJECT
  
public:
  explicit InitialConditionsModifyPanel(QWidget *parent = 0);
  ~InitialConditionsModifyPanel();

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
  QHBoxLayout* HBoxLayout_1;
  QHBoxLayout* HBoxLayout_2;
  QHBoxLayout* HBoxLayout_3;
  QLabel* label_1;
  QLabel* label_2;
  QLabel* label_3;
  QLineEdit* lineEdit_1;
  QComboBox* comboBox_2;
  QLineEdit* lineEdit_3;
};

#endif // INITIALCONDITIONSMODIFYPANEL_HPP