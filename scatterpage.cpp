#include "scatterpage.h"

#include "ui_scatterpage.h"

void ScatterPage::iniGraph3D()
{
    graph3D = new Q3DScatter();
    graphContainer = QWidget::createWindowContainer(graph3D); //Q3DBars继承自QWindow，必须如此创建

    QScatterDataProxy *proxy = new QScatterDataProxy(); //数据代理
    series = new QScatter3DSeries(proxy);  //创建序列
    series->setItemLabelFormat("(@xLabel @yLabel @zLabel)");
    series->setMeshSmooth(true);
    graph3D->addSeries(series);
    series->setBaseColor(Qt::blue);

//创建坐标轴
    graph3D->axisX()->setTitle("axis X");
    graph3D->axisX()->setTitleVisible(true);

    graph3D->axisY()->setTitle("axis Y");
    graph3D->axisY()->setTitleVisible(true);

    graph3D->axisZ()->setTitle("axis Z");
    graph3D->axisZ()->setTitleVisible(true);

    graph3D->activeTheme()->setLabelBackgroundEnabled(false);

    series->setMesh(QAbstract3DSeries::MeshSphere); //MeshPoint, MeshCylinder
    series->setItemSize(0.2);//default 0. value 0~1

    int N=41;
    int itemCount=N*N;
    QScatterDataArray *dataArray = new QScatterDataArray();
    dataArray->resize(itemCount);
    QScatterDataItem *ptrToDataArray = &dataArray->first();

    //墨西哥草帽,-10:0.5:10， N=41
    qDebug() << "xxxxxxxxxxxxxxxxxxxx" << xlist;
    for (int i=0; i < 5; i++)
    {
        ptrToDataArray->setPosition(QVector3D(xlist.at(i),zlist.at(i),ylist.at(i)));
        ptrToDataArray++;
    }

    series->dataProxy()->resetArray(dataArray);
}
QVector3D ScatterPage::randVector()
{
    return QVector3D(
                (float)(rand() % 100) / 2.0f - (float)(rand() % 100) / 2.0f,
                (float)(rand() % 100) / 100.0f - (float)(rand() % 100) / 100.0f,
                (float)(rand() % 100) / 2.0f - (float)(rand() % 100) / 2.0f);
}

ScatterPage::ScatterPage(QList<float> x,QList<float> y, QList<float> z, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ScatterPage)
{
    ui->setupUi(this);
    xlist = x;
    ylist = y;
    zlist = z;
    iniGraph3D();
    this->setCentralWidget(graphContainer);
}

ScatterPage::~ScatterPage()
{
    delete ui;
}
