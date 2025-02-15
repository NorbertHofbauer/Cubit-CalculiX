#include "StepsCreatePanel.hpp"
#include "PanelTable.hpp"
#include "CalculiXCoreInterface.hpp"

#include "CubitInterface.hpp"
#include "Broker.hpp"
#include "Claro.hpp"


StepsCreatePanel::StepsCreatePanel(QWidget *parent) :
  QWidget(parent),
  isInitialized(false)
{
  if(isInitialized)
    return;
  CalculiXCoreInterface *ccx_iface = new CalculiXCoreInterface();
  int labelWidth = 60;
  //this->setMinimumSize(1000,300);
  GridLayout = new QGridLayout(this);
  VBoxLayout = new QVBoxLayout();
  vertical_spacer = new QSpacerItem(1,1,QSizePolicy::Minimum,QSizePolicy::Expanding);
  HBoxLayout_1 = new QHBoxLayout();
  HBoxLayout_2 = new QHBoxLayout();
  label_1 = new QLabel();
  label_2 = new QLabel();
  label_1->setFixedWidth(labelWidth);
  label_2->setFixedWidth(labelWidth);
  label_1->setText("Name");
  label_2->setText("Type");
  lineEdit_1 = new QLineEdit();
  comboBox_2 = new QComboBox();
  comboBox_2->addItem("Static");
  comboBox_2->addItem("Frequency");
  comboBox_2->addItem("Buckle");
  comboBox_2->addItem("Heat Transfer");  
  comboBox_2->addItem("Coupled Temperature Displacement");
  comboBox_2->addItem("Uncoupled Temperature Displacement");
  comboBox_2->addItem("Dynamic");
  comboBox_2->addItem("Modal Dynamic");
  comboBox_2->addItem("Steady State Dynamics");
  comboBox_2->addItem("Complex Frequency");
  comboBox_2->addItem("No Analysis");
  //lineEdit_1->setPlaceholderText("Optional");
  
  pushButton_apply = new QPushButton();
  pushButton_apply->setText("Apply");
  HBoxLayout_pushButton_apply = new QHBoxLayout();
  horizontal_spacer_pushButton_apply = new QSpacerItem(1,1,QSizePolicy::Expanding,QSizePolicy::Minimum);
  
  // Layout
  GridLayout->addLayout(VBoxLayout,0,0, Qt::AlignTop);
  VBoxLayout->addLayout(HBoxLayout_1);
  VBoxLayout->addLayout(HBoxLayout_2);
  VBoxLayout->addItem(vertical_spacer);
  VBoxLayout->addLayout(HBoxLayout_pushButton_apply);

  HBoxLayout_1->addWidget(label_1);
  HBoxLayout_1->addWidget(lineEdit_1);
  HBoxLayout_2->addWidget(label_2);
  HBoxLayout_2->addWidget(comboBox_2);
    
  HBoxLayout_pushButton_apply->addItem(horizontal_spacer_pushButton_apply);
  HBoxLayout_pushButton_apply->addWidget(pushButton_apply);

  QObject::connect(pushButton_apply, SIGNAL(clicked(bool)),this,  SLOT(on_pushButton_apply_clicked(bool)));

  isInitialized = true;
}

StepsCreatePanel::~StepsCreatePanel()
{}

void StepsCreatePanel::on_pushButton_apply_clicked(bool)
{
  QStringList commands;
  QString command = "";

  if ((lineEdit_1->text()!=""))
  {
    command.append("ccx create step name \"" + lineEdit_1->text() + "\"");
    if (comboBox_2->currentIndex()==0)
    {
      command.append(" static");
    }else if (comboBox_2->currentIndex()==1)
    {
      command.append(" frequency");
    }else if (comboBox_2->currentIndex()==2)
    {
      command.append(" buckle");
    }else if (comboBox_2->currentIndex()==3)
    {
      command.append(" heattransfer");
    }else if (comboBox_2->currentIndex()==4)
    {
      command.append(" coupledtemperaturedisplacement");
    }else if (comboBox_2->currentIndex()==5)
    {
      command.append(" uncoupledtemperaturedisplacement");
    }else if (comboBox_2->currentIndex()==6)
    {
      command.append(" dynamic");
    }else if (comboBox_2->currentIndex()==7)
    {
      command.append(" modaldynamic");
    }else if (comboBox_2->currentIndex()==8)
    {
      command.append(" steadystatedynamics");
    }else if (comboBox_2->currentIndex()==9)
    {
      command.append(" complexfrequency");
    }else if (comboBox_2->currentIndex()==10)
    {
      command.append(" noanalysis");
    }
  }
  
  if (command != "")
  {
    commands.push_back(command);
    lineEdit_1->setText("");
    comboBox_2->setCurrentIndex(0);
  }
  
  for (size_t i = 0; i < commands.size(); i++)
  {
    //CubitInterface::cmd(commands[int(i)].toStdString().c_str());
    ccx_iface->cmd(commands[int(i)].toStdString());
  }
}
