#include "sheetform.h"
#include "ui_sheetform.h"
#include "headerview.h"
#include <QMessageBox>
#include <QDebug>
#include <QVector>

using std::count;

SheetForm::SheetForm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SheetForm)
{
    ui->setupUi(this);

    theModel = new QStandardItemModel(1200,600,this);
    theSelModel = new QItemSelectionModel(theModel);

    connect(theSelModel,SIGNAL(currentChanged(QModelIndex,QModelIndex)),this,SLOT(on_currentChanged(QModelIndex,QModelIndex)));
//    connect(ui->tableView->horizontalHeader(),SIGNAL(sectionClicked(int)),this,SLOT(on_horizontalHeaderClicked(int)));
//    connect(ui->tableView->verticalHeader(), SIGNAL(sectionClicked(int)),this,SLOT(on_verticalHeader(int)));
//    connect(ui->tableView->verticalHeader(),SIGNAL(sectionClicked(int)),parent,SLOT(on_enableRowDel(int)));

    ui->tableView->setModel(theModel);
    ui->tableView->setSelectionModel(theSelModel);
    tableviewp = ui->tableView->horizontalHeader();
    tableviewpp = ui->tableView;
}

SheetForm::~SheetForm()
{
    delete ui;
}

void SheetForm::on_horizontalHeaderClicked(int i)
{
}

void SheetForm::on_verticalHeader(int i)
{
    rowdelindex = i;
}

void SheetForm::on_currentChanged(const QModelIndex & current, const QModelIndex &previous)
{
    if(current.isValid())
    {
        QString info = QString::asprintf("当前单元格：%d行，%d列",current.row(),current.column());
    }
}

void SheetForm::on_currentRowChanged(const QModelIndex &current, const QModelIndex &previous)
{

}

void SheetForm::on_currentColumnChanged(const QModelIndex &current, const QModelIndex &previous)
{

}

int SheetForm::getrowdelindex()
{
    return rowdelindex;
}

void SheetForm::rowdel()
{
    QModelIndex curIndex = theSelModel->currentIndex();
    if(curIndex.row() == theModel->rowCount()-1)
    {
        theModel->removeRow(curIndex.row());
    }
    else
    {
        theModel->removeRow(curIndex.row());
        theSelModel->setCurrentIndex(curIndex,QItemSelectionModel::Select);
    }
}



void SheetForm::releaseLine()
{
    ui->tableView->verticalHeader()->blockSignals(false);
}

void SheetForm::createHeaderChx(int col_num, SheetForm *sheet, TableQHeaderView* header)
{

}


void SheetForm::onStateChanged(int state)
{

}

