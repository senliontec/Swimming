#include "showfilterdata.h"
#include "ui_showfilterdata.h"
#include "QDebug"

showFilterData::showFilterData(QWidget* parent):
    QDialog(parent),
    ui(new Ui::showFilterData)
{
    ui->setupUi(this);
    theModel = new QStandardItemModel(this);
    theSelModel = new QItemSelectionModel(theModel);
    theResModel = new QStandardItemModel(this);

    createToolBar();

    connect(theSelModel,SIGNAL(selectionChanged(QItemSelection,QItemSelection)),this,SLOT(on_selectionChanged(QItemSelection,QItemSelection)));
    connect(cluster_act,SIGNAL(triggered()),this,SLOT(on_triggered()));

    ui->showdataview->setModel(theModel);
    ui->showdataview->setSelectionModel(theSelModel);
    ui->resdataview->setModel(theResModel);
    ui->resdataview->hide();
}
showFilterData::~showFilterData()
{
    delete ui;
}

void showFilterData::on_selectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
    indexList.clear();
    QModelIndexList curindexlist =  theSelModel->selectedColumns(0);
    for (int i;i<curindexlist.size();i++ ) {
        int curindex = curindexlist[i].column();
        indexList.append(curindex+1);
    }
}

void showFilterData::on_triggered()
{
    ui->resdataview->show();
    getSelData();
}

void showFilterData::createToolBar()
{
    toolbar = new QToolBar(this);
    toolbar->setIconSize(QSize(16,16));
    toolbar->setFloatable(false);
    toolbar->setMovable(false);
    cluster_act = new QAction("聚类分析",NULL);
    cluster_act->setIcon(QIcon(":/images/images/(44,31).png"));
    toolbar->addAction(cluster_act);
    toolbar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->outverticalLayout->insertWidget(0,toolbar);
}

void showFilterData::getSelData()
{
    QList<QString> selheaderList;
    selcolList.clear();
    selheaderList.clear();
    if(!headerMap.isEmpty())
    {
        for (int i=0; i<indexList.size(); i++){
            QString header = headerMap.key(indexList[i]);
            selheaderList.append(header);
        }
    }

    QVector<QList<QStandardItem*>> colVector(theModel->columnCount());
    qDebug() << theModel->columnCount();
    for (int i=0; i<theModel->columnCount(); i++)
    {
        for (int j=0; j<theModel->rowCount(); j++)
        {
            QStandardItem *aItem;
            aItem = theModel->item(j,i);
            colVector[i].append(aItem);
        }
    }
    for (int i=0; i<theModel->columnCount();i++)
    {
        colDataMap.insert(theheaderList[i],colVector[i]);
    }

    for (int i=0; i<selheaderList.size(); i++)
    {
        QList<QStandardItem*> colList = colDataMap[selheaderList[i]];
        selcolList.append(colList);
    }

    initResModel();
}

void showFilterData::initResModel()
{
    for (int i; i<selcolList.size(); i++)
    {
        for (int j=0; j<selcolList[i].size(); j++)
        {
            QStandardItem *aItem;
            aItem = new QStandardItem(selcolList[i][j]->text());
            theResModel->setItem(j,i,aItem);
        }

    }

    int thecolnum = theResModel->columnCount();
    int K = 3;
    int iters = 100;
    int pointId = 1;
    vector<Point> all_points;
    for (int i=0;  i<theResModel->rowCount(); i++)
    {
        string line;
        string str="";
        for (int j=0; j<theResModel->columnCount(); j++)
        {
            QStandardItem *aItem;
            aItem = theResModel->item(i,j);
            line.append(str+aItem->text().toStdString()+"\t");
        }
        Point point(i,line);
        all_points.push_back(point);
        pointId++;
    }
    Kmeans kmeans(K, iters);
    kmeans.run(all_points);

    for (int i=0; i<K; i++)
    {
        int size = kmeans.clusters[i].getSize();
        for (int j=0; j<size; j++)
        {
            int row_index = kmeans.clusters[i].getPoint(j).getID();
            QStandardItem* aItem;
            aItem = new QStandardItem(QString::number(i+1));
            theResModel->setItem(row_index,thecolnum,aItem);
        }
    }
}













