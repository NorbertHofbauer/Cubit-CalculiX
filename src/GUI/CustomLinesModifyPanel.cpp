#include "CustomLinesModifyPanel.hpp"
#include "CalculiXCoreInterface.hpp"

#include "CubitInterface.hpp"
#include "Broker.hpp"
#include "Claro.hpp"

CustomLinesModifyPanel::CustomLinesModifyPanel(QWidget *parent) :
  QWidget(parent),
  isInitialized(false)
{
  if(isInitialized)
    return;
  CalculiXCoreInterface *ccx_iface = new CalculiXCoreInterface();
  int labelWidth = 120;
  //this->setMinimumSize(1000,300);
  GridLayout = new QGridLayout(this);
  VBoxLayout = new QVBoxLayout();
  vertical_spacer = new QSpacerItem(1,1,QSizePolicy::Minimum,QSizePolicy::Expanding);
  HBoxLayout_0 = new QHBoxLayout();
  HBoxLayout_1 = new QHBoxLayout();
  HBoxLayout_2 = new QHBoxLayout();
  HBoxLayout_3 = new QHBoxLayout();
  HBoxLayout_4 = new QHBoxLayout();
  HBoxLayout_5 = new QHBoxLayout();
  label_0 = new QLabel();
  label_1 = new QLabel();
  label_2 = new QLabel();
  label_3 = new QLabel();
  label_4 = new QLabel();
  label_5 = new QLabel();
  label_0->setFixedWidth(labelWidth);
  label_1->setFixedWidth(labelWidth);
  label_2->setFixedWidth(labelWidth);
  label_3->setFixedWidth(labelWidth);
  label_4->setFixedWidth(labelWidth);
  label_5->setFixedWidth(labelWidth);
  label_0->setText("Custom Line ID");
  label_1->setText("Name");
  label_2->setText("Position");
  label_3->setText("Item");
  label_4->setText("Item ID");
  label_5->setText("Custom Line");
  lineEdit_0 = new QLineEdit();
  lineEdit_1 = new QLineEdit();
  comboBox_2 = new QComboBox();
  comboBox_2->addItem("");
  comboBox_2->addItem("before");
  comboBox_2->addItem("after");
  comboBox_2->addItem("begin");
  comboBox_2->addItem("end");
  comboBox_3 = new QComboBox();
  lineEdit_4 = new QLineEdit();
  //lineEdit_1->setPlaceholderText("Optional");
  //lineEdit_2->setPlaceholderText("Optional");
  lineEdit_5 = new QLineEdit();

  pushButton_apply = new QPushButton();
  pushButton_apply->setText("Apply");
  HBoxLayout_pushButton_apply = new QHBoxLayout();
  horizontal_spacer_pushButton_apply = new QSpacerItem(1,1,QSizePolicy::Expanding,QSizePolicy::Minimum);
  
  // Layout
  GridLayout->addLayout(VBoxLayout,0,0, Qt::AlignTop);
  VBoxLayout->addLayout(HBoxLayout_0);
  VBoxLayout->addLayout(HBoxLayout_1);
  VBoxLayout->addLayout(HBoxLayout_2);
  VBoxLayout->addLayout(HBoxLayout_3);
  VBoxLayout->addLayout(HBoxLayout_4);
  VBoxLayout->addLayout(HBoxLayout_5);
  VBoxLayout->addItem(vertical_spacer);
  VBoxLayout->addLayout(HBoxLayout_pushButton_apply);

  HBoxLayout_0->addWidget(label_0);
  HBoxLayout_0->addWidget(lineEdit_0);
  HBoxLayout_1->addWidget(label_1);
  HBoxLayout_1->addWidget(lineEdit_1);
  HBoxLayout_2->addWidget(label_2);
  HBoxLayout_2->addWidget(comboBox_2);
  HBoxLayout_3->addWidget(label_3);
  HBoxLayout_3->addWidget(comboBox_3);
  HBoxLayout_4->addWidget(label_4);
  HBoxLayout_4->addWidget(lineEdit_4);
  HBoxLayout_5->addWidget(label_5);
  HBoxLayout_5->addWidget(lineEdit_5);
  
  HBoxLayout_pushButton_apply->addItem(horizontal_spacer_pushButton_apply);
  HBoxLayout_pushButton_apply->addWidget(pushButton_apply);

  QObject::connect(pushButton_apply, SIGNAL(clicked(bool)),this,  SLOT(on_pushButton_apply_clicked(bool)));
  QObject::connect(comboBox_2, SIGNAL(currentIndexChanged(int)),this,  SLOT(on_comboBox_index_changed(int)));

  this->on_comboBox_index_changed(0);

  isInitialized = true;
}

CustomLinesModifyPanel::~CustomLinesModifyPanel()
{}

void CustomLinesModifyPanel::on_pushButton_apply_clicked(bool)
{
  QStringList commands;
  QString command = "";

  if ((lineEdit_0->text()!=""))
  {
    command.append("ccx modify customline " +lineEdit_0->text());

    if ((lineEdit_1->text()!=""))
    {
      command.append(" name \"" +lineEdit_1->text() + "\"");
    }
    
    if (comboBox_2->currentIndex()>0)
    {
      command.append(" " + comboBox_2->currentText());
    }

    if (comboBox_3->currentIndex()>0)
    {
      command.append(" " + comboBox_3->currentText());
    }

    if ((lineEdit_4->text()!=""))
    {
      command.append(" item_id " +lineEdit_4->text());
    }

    if ((lineEdit_5->text()!=""))
    {
      command.append(" cline \"" +lineEdit_5->text() + "\"");
    }
  }
  
  if (command != "")
  {
    commands.push_back(command);
    lineEdit_0->setText("");
    lineEdit_1->setText("");
    comboBox_2->setCurrentIndex(0);
    //comboBox_3->clear();
    lineEdit_4->setText("");
    lineEdit_5->setText("");
  }
  
  for (size_t i = 0; i < commands.size(); i++)
  {
    //CubitInterface::cmd(commands[int(i)].toStdString().c_str());
    ccx_iface->cmd(commands[int(i)].toStdString());
  }
}

void CustomLinesModifyPanel::on_comboBox_index_changed(int index)
{
  if (index > 2)
  {
    comboBox_3->clear();
    comboBox_3->addItem("");
    comboBox_3->addItem("export");
    lineEdit_4->setText("");
    lineEdit_5->setText("");
    lineEdit_4->setEnabled(false);
  }else{
    comboBox_3->clear();
    comboBox_3->addItem("");
    comboBox_3->addItem("elset");
    comboBox_3->addItem("nset");
    comboBox_3->addItem("sideset");
    comboBox_3->addItem("material");
    comboBox_3->addItem("section");
    comboBox_3->addItem("constraint");
    comboBox_3->addItem("surfaceinteraction");
    comboBox_3->addItem("contactpair");
    comboBox_3->addItem("amplitude");
    comboBox_3->addItem("orientation");
    comboBox_3->addItem("force");
    comboBox_3->addItem("pressure");
    comboBox_3->addItem("heatflux");
    comboBox_3->addItem("gravity");
    comboBox_3->addItem("centrifugal");
    comboBox_3->addItem("displacement");
    comboBox_3->addItem("temperature");
    comboBox_3->addItem("historyoutput");
    comboBox_3->addItem("fieldoutput");
    comboBox_3->addItem("initialcondition");
    comboBox_3->addItem("step_begin");
    comboBox_3->addItem("step_end");
    lineEdit_4->setEnabled(true);
  }
}