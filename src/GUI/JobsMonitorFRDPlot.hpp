#ifndef JOBSMONITORFRDPLOT_HPP
#define JOBSMONITORFRDPLOT_HPP

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
#include <QComboBox>
#include <QString>
#include <QComboBox>
#include <QLineEdit>
#include <QObject>
#include <QSpacerItem>

class CalculiXCoreInterface;
class PickWidget;

class JobsMonitorFRDPlot : public QWidget
{
  Q_OBJECT
  
public:
  JobsMonitorFRDPlot();
  ~JobsMonitorFRDPlot();

  CalculiXCoreInterface *ccx_iface;

  int current_job_id = -1;

  void reset();

private:
  QGridLayout* gridLayout;
  QHBoxLayout* boxLayout_x;
  QHBoxLayout* boxLayout_y;
  QVBoxLayout* boxLayout_labels; 
  QHBoxLayout* boxLayout_buttons;
  QSpacerItem* horizontal_spacer_x;
  QSpacerItem* horizontal_spacer_y;
  QLabel* label_x;
  QLabel* label_y;
  QComboBox* combobox_x_1;
  QComboBox* combobox_y_1;
  QLabel* label_node_x;
  QLabel* label_node_y;
  PickWidget* PickWidget_node_x;
  PickWidget* PickWidget_node_y;
  QComboBox* combobox_x_2;
  QComboBox* combobox_y_2;
  QComboBox* combobox_x_3;
  QComboBox* combobox_y_3;
  QLabel* label_title;
  QLabel* label_x_axis;
  QLabel* label_y_axis;
  QLabel* label_save_path;
  QLineEdit* lineEdit_title;
  QLineEdit* lineEdit_x_axis;
  QLineEdit* lineEdit_y_axis;
  QLineEdit* lineEdit_save_path;
  QPushButton* pushButton_reset;
  QPushButton* pushButton_plot;
  QPushButton* pushButton_close;

private slots:
 void on_pushButton_reset_clicked(bool);
 void on_pushButton_plot_clicked(bool);
 void on_pushButton_close_clicked(bool);
 void combobox_x_1_index_changed(int index);
 void combobox_y_1_index_changed(int index);
 void combobox_x_2_index_changed(int index);
 void combobox_y_2_index_changed(int index);
  
};

#endif // JOBSMONITORFRDPLOT_HPP