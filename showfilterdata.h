#ifndef SELDATA_H
#define SELDATA_H
#include <QDialog>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QItemSelectionModel>
#include <QTableView>
#include <QToolBar>
#include <QAction>
#include <QFile>
#include "kmeans.h"


namespace Ui {
class showFilterData;
class Point;
class Cluster;
class KMeans;
}

class showFilterData:public QDialog
{
    Q_OBJECT

public:
    explicit showFilterData(QWidget *parent = nullptr);
    ~showFilterData();

    QToolBar *toolbar;
    QAction *cluster_act;
    QStandardItemModel  *theModel;
    QItemSelectionModel *theSelModel;
    QStandardItemModel  *theResModel;

    QMap<QString,QList<QStandardItem*>> colDataMap;
    QMap<QString,int> headerMap;
    QList<int> indexList;
    QStringList theheaderList;
    QList<QList<QStandardItem*>> selcolList;
    QVector<QVector<int>> allpoints;



private:
    void createToolBar();
    void getSelData();
    void initResModel();
    void outputClusterRes();

private slots:
    void on_selectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
    void on_triggered();

public:
    Ui::showFilterData *ui;
};

#endif // SELDATA_H
