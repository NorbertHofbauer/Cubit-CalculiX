#include "MaterialManagementTable.hpp"
#include "MaterialManagementItem.hpp"

#include "CubitMessage.hpp"

MaterialManagementTable::MaterialManagementTable(QWidget* parent, QString group_name):
  QTableWidget(parent),
  isInitialized(false)
{
  if(isInitialized)
    return;

  this->group = group_name.toStdString();
  
  //delegator = new QAbstractItemDelegate();
  //this->setItemDelegateForColumn(0,delegator);
  this->setMinimumSize(1100,240);
  //this->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  
  // Signals
  QObject::connect(this, SIGNAL(currentItemChanged(QTableWidgetItem*, QTableWidgetItem*)),this,  SLOT(currentItemChanged(QTableWidgetItem*,QTableWidgetItem*)));
  QObject::connect(this, SIGNAL(currentCellChanged(int,int,int,int)),this,  SLOT(currentCellChanged(int,int,int,int)));
  QObject::connect(this, SIGNAL(cellChanged(int,int)),this,  SLOT(cellChanged(int,int)));

  isInitialized = true;
}

MaterialManagementTable::~MaterialManagementTable()
{
}

void MaterialManagementTable::update(MaterialManagementItem *material)
{
  bool_update=true;
  this->setRowCount(0);
  
  if (this->group=="CCX_ELASTIC_ISO_MODULUS_VS_POISSON_VS_TEMPERATURE")
  {
    this->setColumnCount(3);
    this->setHorizontalHeaderLabels({"Young's Modulus","Poisson's ratio","Temperature"});
    this->setColumnWidth(0,150);
  }else if (this->group=="CCX_ELASTIC_ORTHO_CONSTANTS_VS_TEMPERATURE")
  {
    this->setColumnCount(10);
    this->setHorizontalHeaderLabels({"D1111","D1122","D2222","D1133","D2233","D3333","D1212","D1313","D2323","TEMPERATURE"});
  }else if (this->group=="CCX_ELASTIC_EC_CONSTANTS_VS_TEMPERATURE")
  {
    this->setColumnCount(10);
    this->setHorizontalHeaderLabels({"E1","E2","E3","v12","v13","v23","G12","G13","G23","TEMPERATURE"});
  }else if (this->group=="CCX_ELASTIC_ANISO_CONSTANTS_VS_TEMPERATURE")
  {
    this->setColumnCount(22);
    this->setHorizontalHeaderLabels({"D1111","D1122","D2222","D1133","D2233","D3333","D1112","D2212","D3312","D1212","D1113","D2213","D3313","D1213","D1313","D1123","D2223","D3323","D1223","D1323","D2323","TEMPERATURE"});
  }else if (this->group=="CCX_PLASTIC_ISO_YIELD_STRESS_VS_STRAIN_VS_TEMPERATURE")
  {
    this->setColumnCount(3);
    this->setHorizontalHeaderLabels({"von Mises Stress","Plastic Strain","Temperature"});
    this->setColumnWidth(0,150);
    this->setColumnWidth(1,150);
  }else if (this->group=="CCX_PLASTIC_KIN_YIELD_STRESS_VS_STRAIN_VS_TEMPERATURE")
  {
    this->setColumnCount(3);
    this->setHorizontalHeaderLabels({"von Mises Stress","Plastic Strain","Temperature"});
    this->setColumnWidth(0,150);
    this->setColumnWidth(1,150);
  }else if (this->group=="CCX_PLASTIC_COMBINED_YIELD_STRESS_VS_STRAIN_VS_TEMPERATURE")
  {
    this->setColumnCount(3);
    this->setHorizontalHeaderLabels({"von Mises Stress","Plastic Strain","Temperature"});
    this->setColumnWidth(0,150);
    this->setColumnWidth(1,150);
  }else if (this->group=="CCX_PLASTIC_JOHNSON_COOK")
  {
    this->setColumnCount(6);
    this->setHorizontalHeaderLabels({"A","B","n","m","Tm","T0"});
    this->setColumnWidth(0,150);
    this->setColumnWidth(1,150);
  }else if (this->group=="CCX_DENSITY_DENSITY")
  {
    this->setColumnCount(2);
    this->setHorizontalHeaderLabels({"Density","Temperature"});
  }else if (this->group=="CCX_SPECIFIC_HEAT_SPECIFIC_HEAT")
  {
    this->setColumnCount(2);
    this->setHorizontalHeaderLabels({"Specific heat","Temperature"});
  }else if (this->group=="CCX_EXPANSION_ISO_A_TEMPERATURE")
  {
    this->setColumnCount(2);
    this->setHorizontalHeaderLabels({u8"\u03B1","Temperature"});
  }else if (this->group=="CCX_EXPANSION_ORTHO_CONSTANTS_VS_TEMPERATURE")
  {
    this->setColumnCount(4);
    this->setHorizontalHeaderLabels({u8"\u03B111",u8"\u03B122",u8"\u03B133","Temperature"});
  }else if (this->group=="CCX_EXPANSION_ANISO_CONSTANTS_VS_TEMPERATURE")
  {
    this->setColumnCount(7);
    this->setHorizontalHeaderLabels({u8"\u03B111",u8"\u03B122",u8"\u03B133",u8"\u03B112",u8"\u03B113",u8"\u03B123","Temperature"});
  }else if (this->group=="CCX_CONDUCTIVITY_ISO_K_TEMPERATURE")
  {
    this->setColumnCount(2);
    this->setHorizontalHeaderLabels({u8"\u03BA","Temperature"});
  }else if (this->group=="CCX_CONDUCTIVITY_ORTHO_CONSTANTS_VS_TEMPERATURE")
  {
    this->setColumnCount(4);
    this->setHorizontalHeaderLabels({u8"\u03BA11",u8"\u03BA22",u8"\u03BA33","Temperature"});
  }else if (this->group=="CCX_CONDUCTIVITY_ANISO_CONSTANTS_VS_TEMPERATURE")
  {
    this->setColumnCount(7);
    this->setHorizontalHeaderLabels({u8"\u03BA11",u8"\u03BA22",u8"\u03BA33",u8"\u03BA12",u8"\u03BA13",u8"\u03BA23","Temperature"});
  }else if (this->group=="CCX_DEFORMATION_PLASTICITY_RAMBERG_OSGOOD")
  {
    this->setColumnCount(6);
    this->setHorizontalHeaderLabels({"Young's Modulus", "Poisson's ratio", "Yield Stress", "Exponent", "Yield Offset","Temperature"});
    this->setColumnWidth(0,150);
    this->setColumnWidth(1,150);
    this->setColumnWidth(2,150);
    this->setColumnWidth(3,150);
    this->setColumnWidth(4,150);
    this->setColumnWidth(5,150);
  }else if (this->group=="CCX_MOHR_COULOMB_MOHR_COULOMB")
  {
    this->setColumnCount(3);
    this->setHorizontalHeaderLabels({"Friction angle φ in degrees", "Dilation angle ψ in degrees","Temperature"});
    this->setColumnWidth(0,300);
    this->setColumnWidth(1,300);
    this->setColumnWidth(2,150);
  }else if (this->group=="CCX_MOHR_COULOMB_HARDENING_MOHR_COULOMB_HARDENING")
  {
    this->setColumnCount(3);
    this->setHorizontalHeaderLabels({"Cohesion yield stress c", "Equivalent plastic strain","Temperature"});
    this->setColumnWidth(0,300);
    this->setColumnWidth(1,300);
    this->setColumnWidth(2,150);
  }else if (this->group=="CCX_CYCLIC_HARDENING_CYCLIC_HARDENING")
  {
    this->setColumnCount(3);
    this->setHorizontalHeaderLabels({"Von Mises stress", "Equivalent plastic strain","Temperature"});
    this->setColumnWidth(0,300);
    this->setColumnWidth(1,300);
    this->setColumnWidth(2,150);
  }else if (this->group=="CCX_RATE_DEPENDENT_RATE_DEPENDENT")
  {
    this->setColumnCount(2);
    this->setHorizontalHeaderLabels({"C", u8"\u03B5_dot_0"});
  }else if (this->group=="CCX_CREEP_CREEP")
  {
    this->setColumnCount(4);
    this->setHorizontalHeaderLabels({"A","n","m","Temperature"});
    this->setColumnWidth(3,150);
  }else if (this->group=="CCX_HYPERELASTIC_ARRUDA_BOYCE")
  {
    this->setColumnCount(4);
    this->setHorizontalHeaderLabels({u8"\u03BC",u8"\u03BBm","D","Temperature"});
    this->setColumnWidth(3,150);
  }else if (this->group=="CCX_HYPERELASTIC_MOONEY_RIVLIN")
  {
    this->setColumnCount(4);
    this->setHorizontalHeaderLabels({"C10","C01","D1","Temperature"});
    this->setColumnWidth(3,150);
  }else if (this->group=="CCX_HYPERELASTIC_NEO_HOOKE")
  {
    this->setColumnCount(3);
    this->setHorizontalHeaderLabels({"C10","D1","Temperature"});
    this->setColumnWidth(2,150);
  }else if (this->group=="CCX_HYPERELASTIC_OGDEN_N1")
  {
    this->setColumnCount(4);
    this->setHorizontalHeaderLabels({u8"\u03BC1",u8"\u03B11","D1","Temperature"});
    this->setColumnWidth(3,150);
  }else if (this->group=="CCX_HYPERELASTIC_OGDEN_N2")
  {
    this->setColumnCount(7);
    this->setHorizontalHeaderLabels({u8"\u03BC1",u8"\u03B11","D1",u8"\u03BC2",u8"\u03B12","D2","Temperature"});
    this->setColumnWidth(6,150);
  }else if (this->group=="CCX_HYPERELASTIC_OGDEN_N3")
  {
    this->setColumnCount(10);
    this->setHorizontalHeaderLabels({u8"\u03BC1",u8"\u03B11","D1",u8"\u03BC2",u8"\u03B12","D2",u8"\u03BC3",u8"\u03B13","D3","Temperature"});
    this->setColumnWidth(9,150);
  }else if (this->group=="CCX_HYPERELASTIC_POLYNOMIAL_N1")
  {
    this->setColumnCount(4);
    this->setHorizontalHeaderLabels({"C10","C01","D1","Temperature"});
    this->setColumnWidth(3,150);
  }else if (this->group=="CCX_HYPERELASTIC_POLYNOMIAL_N2")
  {
    this->setColumnCount(8);
    this->setHorizontalHeaderLabels({"C10","C01","C20","C11","C02","D1","D2","Temperature"});
    this->setColumnWidth(7,150);
  }else if (this->group=="CCX_HYPERELASTIC_POLYNOMIAL_N3")
  {
    this->setColumnCount(13);
    this->setHorizontalHeaderLabels({"C10","C01","C20","C11","C02","C30","C21","C12","C03","D1","D2","D3","Temperature"});
    this->setColumnWidth(12,150);
  }else if (this->group=="CCX_HYPERELASTIC_REDUCED_POLYNOMIAL_N1")
  {
    this->setColumnCount(3);
    this->setHorizontalHeaderLabels({"C10","D1","Temperature"});
    this->setColumnWidth(2,150);
  }else if (this->group=="CCX_HYPERELASTIC_REDUCED_POLYNOMIAL_N2")
  {
    this->setColumnCount(5);
    this->setHorizontalHeaderLabels({"C10","C20","D1","D2","Temperature"});
    this->setColumnWidth(4,150);
  }else if (this->group=="CCX_HYPERELASTIC_REDUCED_POLYNOMIAL_N3")
  {
    this->setColumnCount(7);
    this->setHorizontalHeaderLabels({"C10","C20","C30","D1","D2","D3","Temperature"});
    this->setColumnWidth(6,150);
  }else if (this->group=="CCX_HYPERELASTIC_YEOH")
  {
    this->setColumnCount(7);
    this->setHorizontalHeaderLabels({"C10","C20","C30","D1","D2","D3","Temperature"});
    this->setColumnWidth(6,150);
  }else if (this->group=="CCX_HYPERFOAM_HYPERFOAM_N1")
  {
    this->setColumnCount(4);
    this->setHorizontalHeaderLabels({u8"\u03BC1",u8"\u03B11",u8"\u03BD1","Temperature"});
    this->setColumnWidth(3,150);
  }else if (this->group=="CCX_HYPERFOAM_HYPERFOAM_N2")
  {
    this->setColumnCount(7);
    this->setHorizontalHeaderLabels({u8"\u03BC1",u8"\u03B11",u8"\u03BC2",u8"\u03B12",u8"\u03BD1",u8"\u03BD2","Temperature"});
    this->setColumnWidth(6,150);
  }else if (this->group=="CCX_HYPERFOAM_HYPERFOAM_N3")
  {
    this->setColumnCount(10);
    this->setHorizontalHeaderLabels({u8"\u03BC1",u8"\u03B11",u8"\u03BC2",u8"\u03B12",u8"\u03BC3",u8"\u03B13",u8"\u03BD1",u8"\u03BD2",u8"\u03BD3","Temperature"});
    this->setColumnWidth(9,150);
  }else if (this->group=="CCX_COMPRESSION_ONLY_COMPRESSION_ONLY")
  {
    this->setColumnCount(3);
    this->setHorizontalHeaderLabels({"E","maximum allowed value","Temperature"});
    this->setColumnWidth(1,300);
    this->setColumnWidth(2,150);
  }else if (this->group=="CCX_TENSION_ONLY_TENSION_ONLY")
  {
    this->setColumnCount(3);
    this->setHorizontalHeaderLabels({"E","maximum allowed value","Temperature"});
    this->setColumnWidth(1,300);
    this->setColumnWidth(2,150);
  }/*else if (this->group=="CCX_DAMPING_DAMPING")
  {
    this->setColumnCount(1);
    this->setHorizontalHeaderLabels({"Structural"});
    this->setColumnWidth(0,150);
  }*/

  verticalHeaderLabels = QStringList();
  this->material = material;
  property_matrix_gui = material->getMatrixPropertyGUI(group);
  //inser data from material
  for (size_t i = 0; i < property_matrix_gui.size(); i++)
  {
    this->insertNewRow(property_matrix_gui[i]);
  }
  
  // insert last row
  this->insertLastRow();
  bool_update = false;
}


std::vector<std::vector<double>> MaterialManagementTable::getMatrixPropertyGUI()
{
  std::vector<std::vector<double>> matrix_return;
  std::vector<double> matrix_row;
  matrix_return.clear();
  //log = "ROW COUNT " + std::to_string(this->rowCount()) + "COLUMN COUNT " + std::to_string(this->columnCount()) + " \n";
  //PRINT_INFO("%s", log.c_str());

  for (size_t i = 0; i < this->rowCount()-1; i++)
  {
    matrix_row.clear();
    for (size_t ii = 0; ii < this->columnCount(); ii++)
    {
      QTableWidgetItem* item;
      item = this->item(int(i),int(ii));
      if (item!=NULL)
      {
        if (item->text()!="")
        {
          matrix_row.push_back(item->text().toDouble());
        }else{
          matrix_row.push_back(0.);
        }
      }else{
        matrix_row.push_back(0.);
      }
    }
    matrix_return.push_back(matrix_row);
  }

  return matrix_return;
}

void MaterialManagementTable::insertNewRow(std::vector<double> values)
{
  this->insertRow(this->rowCount());
  this->currentRow = this->rowCount()-1;
  verticalHeaderLabels.append(QString::number(this->rowCount()));

  for (size_t i = 0; i < values.size(); i++)
  {
    QTableWidgetItem* item;
    item = new QTableWidgetItem();
    item->setText(QString::number(values[i]));
    this->setItem(this->currentRow,int(i),item);
  }
}

void MaterialManagementTable::insertLastRow()
{
  this->insertRow(this->rowCount());
  //log = std::to_string(this->rowCount()) + " - row count\n";
  //PRINT_INFO("%s", log.c_str());

  for (size_t i = 0; i < this->columnCount(); i++)
  {
    QTableWidgetItem* item;
    item = new QTableWidgetItem();
    item->setText("");
    this->setItem(this->rowCount()-1,int(i),item);
  }

  if (verticalHeaderLabels.count()!=0)
  {
    verticalHeaderLabels[verticalHeaderLabels.count()-1]=QString::number(verticalHeaderLabels.count());
  }
  verticalHeaderLabels.append("*");
  this->setVerticalHeaderLabels(verticalHeaderLabels);
}

bool MaterialManagementTable::checkRowEmtpy(int row)
{
  QTableWidgetItem* item;
  bool bool_empty = true;

  for (size_t i = 0; i < this->columnCount()-1; i++)
  {
    item = this->item(row,int(i));
    if (item!=NULL)
    {
      if (item->text().toDouble()!=0.)
      {
        bool_empty = false;
      }
    }
  }
  
  return bool_empty;
}

void MaterialManagementTable::currentItemChanged(QTableWidgetItem* current_item, QTableWidgetItem** prev_item)
{
  if (current_item!=nullptr)
  {
    
  }
}

void MaterialManagementTable::currentCellChanged(int currentRow,int currentColumn,int previousRow,int previousColumn)
{
  this->currentRow = currentRow;
}

void MaterialManagementTable::cellChanged(int row,int column)
{
  this->currentRow = row;

  // check if data was added to the last row
  if ((row==this->rowCount()-1) && (this->checkRowEmtpy(row)==false) && !bool_update)
  {
    this->insertLastRow();
    this->setCurrentCell(row, column);
  }

  //check if this row (except last row) is empty, when yes delete
  if (!(row==this->rowCount()-1) && (this->checkRowEmtpy(row)==true))
  {
    this->removeRow(row);
    
    verticalHeaderLabels.removeAt(row);
    for (size_t i = 0; i < verticalHeaderLabels.count()-1; i++)
    {
      verticalHeaderLabels[int(i)]=QString::number(i+1);
    }
    this->setVerticalHeaderLabels(verticalHeaderLabels);
  }

  material->setMatrixPropertyGUI(group,this->getMatrixPropertyGUI());
  /*
  log = "matrix gui \n";
  std::vector<std::vector<double>> matrix = this->getMatrixPropertyGUI();
  for (size_t i = 0; i < matrix.size(); i++)
  {
    for (size_t ii = 0; ii < matrix[i].size(); ii++)
    {
      log.append(std::to_string(matrix[i][ii]) + " ");
    }
    log.append(" \n");
  }
  PRINT_INFO("%s", log.c_str()); 
  */
}