#ifndef SHEETFORM_H
#define SHEETFORM_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QItemSelectionModel>
#include <QVector>
#include <headerview.h>
#include <QTableView>

namespace Ui {
class SheetForm;
}

class SheetForm : public QMainWindow
{
    Q_OBJECT

public:
    explicit SheetForm(QWidget *parent = nullptr);
    ~SheetForm();

public:
    QStandardItemModel  *theModel;
    QItemSelectionModel *theSelModel;
    QVector<int>addcolnum;
    QVector<int>::iterator it;
    void rowdel();
    int  getrowdelindex();
    void releaseLine();
    void createHeaderChx(int col_num, SheetForm *sheet, TableQHeaderView* header);
    QHeaderView* tableviewp;
    QTableView* tableviewpp;

private:
    int rowdelindex;

private slots:
    //当前选择单元格发生变化
    void on_currentChanged(const QModelIndex &current, const QModelIndex &previous);
    void on_currentRowChanged(const QModelIndex &current, const QModelIndex &previous);
    void on_currentColumnChanged(const QModelIndex &current, const QModelIndex &previous);
    //void on_selectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
    void on_horizontalHeaderClicked(int);
    void on_verticalHeader(int);
    void onStateChanged(int);



public:
    Ui::SheetForm *ui;
};

#endif // SHEETFORM_H


