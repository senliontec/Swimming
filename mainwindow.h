#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMap>
#include <QList>
#include <QString>

#include <QDir>
#include <QMainWindow>
#include <QFileDialog>
#include <QMapIterator>
#include <QMetaType>

#include "filtervalue.h"
#include "newdata.h"
#include "sheetform.h"
#include "showfilterdata.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    int tablerowcount;
    int tablecolcount;
    QString serialnum;
    QString stroke;
    QString stroketype;
    QMap<QString,int> fieldnum = {
        {"序号",1},{"性别",2},{"体重",3},{"年龄",4},
        {"泳姿",5},{"类别",6},{"运动等级",7},{"测试距离",8},
        {"最大力1",9},{"最大力2",10},{"最大力3",11},{"测试日期",12}
    };
    QList<QMap<QString, QMap<QString,QMap<QString,QString>>>> allSelectData;
    QString infilename;

    FilterValue *filtervalue=NULL;
    NewData *newdata = NULL;
    showFilterData *showfilterdata = NULL;


    void initPython();
    void createsheet();
    void set_tableview(int);
    void loadFromFile(QString &Filename,int tabindex);
    void insertres(QList<int> rownum);


public:
    int tabindex;
    QString filename;
    QString tabname;
    QStringList headerList;
    QMap<int,SheetForm*> sheetMap;
    QMap<QString,int> headerMap;
    QList<QMap<QString,QString>> rowDataList;
    QMap<QString,QList<QString>> colDataMap;
    QList<QMap<QString,QString>> showDataList;
    QMap<QString,int> serialnummap;  // 序号与序列号映射
    SheetForm *sheetform;
    void getFilterData();
    void init_showData_Model();
    void selColData();

private slots:
    void on_actOpenFile_triggered();

    void on_actNewDoc_triggered();

    void on_actSaveas_triggered();

    void on_actRowDel_triggered();

    void on_actDataFilter_triggered();

    void on_actInsertTable_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
