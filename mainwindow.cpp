#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <filtervalue.h>
#include <showfilterdata.h>


#include <QMessageBox>
#include <QDebug>
#include <QTextEdit>
#include <QtGlobal>
#include "xlsxdocument.h"
#include "xlsxchartsheet.h"
#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxrichstring.h"
#include "xlsxworkbook.h"
#include <QFile>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabWidget->setVisible(false);
    ui->tabWidget->clear();//清除所有页面
    ui->tabWidget->tabsClosable(); //Page有关闭按钮，可被关闭

    this->setCentralWidget(ui->tabWidget);
    this->setWindowState(Qt::WindowMaximized); //窗口最大化显示
    this->setAutoFillBackground(true);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actOpenFile_triggered()
{
    QString curPath = QDir::currentPath();
    QString dlgTitle = "请选择数据文件";
    QString filter = "xlsx文件(*.xlsx);;xls文件(*.xls);;所有文件(*.*)";
    filename = QFileDialog::getOpenFileName(this,dlgTitle,curPath,filter);
    if (filename!=NULL)
    {
        int tabindex = ui->tabWidget->currentIndex();
        loadFromFile(filename,tabindex);
    }
}

void MainWindow::on_actNewDoc_triggered()
{
    createsheet();
}

void MainWindow::on_actRowDel_triggered()
{

    if (ui->tabWidget->count()<=0)
    {
        QMessageBox::critical(this,QString("Error"),QString("当前没有数据可供删除!"),QMessageBox::Yes);
    }
    else
    {
        sheetform->rowdel();
    }
}

void MainWindow::on_actDataFilter_triggered()
{
    if (filtervalue == NULL)
        filtervalue=new FilterValue(this);

    int ret = filtervalue->exec();
    if (ret==QDialog::Accepted)
    {
        filtervalue->getFilterValue();
        if (showfilterdata == NULL)
            showfilterdata=new showFilterData(this);
            showfilterdata->headerMap = headerMap;
            showfilterdata->theheaderList = headerList;
        getFilterData();
        int ret1=showfilterdata->exec();
        qDebug() << "111111111111111111111111111"<< ret;
        if (ret1==QDialog::Accepted)
        {
            showDataList.clear();
            showfilterdata->theModel->clear();
            showfilterdata->theResModel->clear();
            filtervalue->filtervalueMap.clear();
            qDebug()<<filtervalue->filtervalueMap;
            qDebug()<<showfilterdata->theModel;
        }
    }
}

void MainWindow:: on_actInsertTable_triggered()
{
    QList<QStandardItem*> aItemList;
    if (newdata==NULL)
        newdata=new NewData(this);
    int ret=newdata->exec();
    if (ret==QDialog::Accepted)
    {
        QStandardItem *aItem;
        QStringList itemstrlist = newdata->insertData();
        for (int i=0; i<=itemstrlist.size()-1; i++)
        {
            aItem=new QStandardItem(itemstrlist[i]);
            aItem->setTextAlignment(Qt::AlignCenter);
            aItemList<<aItem;
        }
        sheetform->theModel->insertRow(tablerowcount-1,aItemList);
        qDebug() << aItemList;
    }
}

void MainWindow:: on_actSaveas_triggered()
{
    QString str;
    QString headerdata;;
    QString filepath = QFileDialog::getSaveFileName(this, "保存文件",""
                                                     , "xlsx(*.xlsx)");
    QXlsx::Document xlsx;
    if (filepath!="")
    {
        // 表头数据
        for (int h=0; h<=tablecolcount; h++)
        {
            headerdata = sheetform->theModel->headerData(h,Qt::Horizontal).toString();
            qDebug() << headerdata;
        }
        // 数据区
        for (int i=0; i<=tablerowcount-2; i++)
        {
            qDebug() <<  i + QString::asprintf("这是第%d行",i);
            for (int j=0; j<=tablecolcount-1; j++)
            {
                str = sheetform->theModel->item(i,j)->text();
                qDebug() << str;
                xlsx.write(i+1,j+1,str);
            }
        }
        xlsx.saveAs(filepath);
        QMessageBox::information(this, "保存", "保存成功！", QMessageBox::Ok);
    }else{
        QMessageBox::information(this,"为保存","未保存",QMessageBox::Cancel);
    }

}

void MainWindow::createsheet()
{
    sheetform = new SheetForm(this);
    sheetform->setAttribute(Qt::WA_DeleteOnClose);  // 关闭自动删除
    int cur=ui->tabWidget->addTab(sheetform,
                                  QString::asprintf("Sheet %d",ui->tabWidget->count()));
    sheetMap.insert(cur,sheetform);
    ui->tabWidget->setCurrentIndex(cur);
    ui->tabWidget->setVisible(true);
}

void MainWindow::getFilterData()
{

    if (!rowDataList.isEmpty()){
        QString f_gender = filtervalue->filtervalueMap["性别"];
        QString f_stroke = filtervalue->filtervalueMap["泳姿"];
        QString f_test_env = filtervalue->filtervalueMap["测试环境"];
        QString f_stroke_type = filtervalue->filtervalueMap["类别"];
        QString f_sport_level = filtervalue->filtervalueMap["运动等级"];
        if ( filtervalue->filtervalueMap["性别"] == "all"){
            filtervalue->filtervalueMap.remove("性别");
        }
        if ( filtervalue->filtervalueMap["泳姿"] == "all"){
            filtervalue->filtervalueMap.remove("泳姿");
        }
        if ( filtervalue->filtervalueMap["测试环境"] == "all"){
            filtervalue->filtervalueMap.remove("测试环境");
        }
        if ( filtervalue->filtervalueMap["类别"] == "all"){
            filtervalue->filtervalueMap.remove("类别");
        }
        if ( filtervalue->filtervalueMap["运动等级"] == "all"){
            filtervalue->filtervalueMap.remove("运动等级");
        }
        if (filtervalue->filtervalueMap.isEmpty())
        {
            showDataList = rowDataList;
        }
        if (!filtervalue->filtervalueMap.isEmpty())
        {
            for (int i; i<rowDataList.size(); i++){
                {
                    QList<bool> boolList;
                    QMap<QString, QString>::iterator iter = filtervalue->filtervalueMap.begin();
                    while (iter != filtervalue->filtervalueMap.end()) {

                        bool bool_value = rowDataList[i][iter.key()] == iter.value();
                        boolList.append(bool_value);
                        ++iter;
                    }
                    if( !boolList.contains(false)){
                        showDataList.append(rowDataList[i]);
                    }
                }
            }
        }
        QStandardItem   *aItem;
        for (int i=0; i<showDataList.size(); i++){
            int j =0;
            if (!showDataList[i].isEmpty())
            {
                showDataList[i].remove("");
                QMap<QString, QString>::iterator showiter = showDataList[i].begin();

                while (showiter != showDataList[i].end()) {
                    j++;
                    if (showiter.value() != NULL)
                    {
                        int index = headerList.indexOf(showiter.key());
                        aItem = new QStandardItem(showiter.value());
                        showfilterdata->theModel->setItem(i,index,aItem);
                    }
                    ++showiter;
                }
            }
        }
        showfilterdata->theModel->setHorizontalHeaderLabels(headerList);
    }
}


void MainWindow::loadFromFile(QString &filename, int tabindex)
{
    QStandardItem   *aItem;
    QXlsx::Document xlsx(filename.toUtf8());  // TODO 待解决中文名表名
    QXlsx::Workbook *workBook = xlsx.workbook();
    QXlsx::Worksheet *workSheet = static_cast<QXlsx::Worksheet*>(workBook->sheet(0));

    int rowcount = workSheet->dimension().rowCount();
    int colcount = workSheet->dimension().columnCount();
    tablerowcount = rowcount;
    tablecolcount = colcount;

    for (int i=1; i<=rowcount; i++)
    {
        QMap<QString,QString> rowdataMap;
        for (int j=1; j<=colcount; j++)
        {
            QXlsx::Cell *cell = workSheet->cellAt(i,j);
            aItem = new QStandardItem(cell->value().toString());
            aItem->setTextAlignment(Qt::AlignCenter);
            if (i==1)
            {// 添加表头
                QString header = cell->value().toString();
                headerList << header;
                headerMap.insert(header,j);
                sheetMap[tabindex]->theModel->setItem(0,j-1,aItem);
            }
            else {// 添加表内容
                sheetMap[tabindex]->theModel->setItem(i-1,j-1,aItem);
                rowdataMap.insert(headerList[j-1],cell->value().toString());
            }
        }
        rowDataList.append(rowdataMap);
    }
}




