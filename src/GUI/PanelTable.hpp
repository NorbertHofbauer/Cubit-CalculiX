#ifndef PANELTABLE_HPP
#define PANELTABLE_HPP

#include <QWidget>
#include <QString>
#include <QStringList>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QAbstractItemDelegate>
#include <QHeaderView>

class PanelTable : public QTableWidget
{
  Q_OBJECT
  
public:
  PanelTable(QWidget *parent);
  ~PanelTable();
  void update(QStringList columns,std::vector<std::vector<double>> matrix); // updates the data in the table
  std::vector<std::vector<double>> getMatrix(); // gets the matrix property values
  void insertNewRow(std::vector<double> values); // inserts new row at the bottom
  void insertLastRow(); // inserts new last row at the bottom
  bool checkRowEmtpy(int row); // checks if the columns in the row are empty

  bool isInitialized;
  std::string panel_type = ""; // to specify a panel type, like amplitude, so that zero time data is possible
private slots:
  void currentItemChanged(QTableWidgetItem* current_item, QTableWidgetItem** prev_item);
  void currentCellChanged(int currentRow,int currentColumn,int previousRow,int previousColumn);
  void cellChanged(int row,int column);

private: 
bool bool_update=true;
std::string log;
std::vector<std::vector<double>> matrix;
std::string group;
int currentRow;
QStringList verticalHeaderLabels;
std::vector<std::vector<double>> property_matrix_gui;

};

#endif // PANELTABLE_HPP