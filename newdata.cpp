#include "newdata.h"
#include "ui_newdata.h"

#include <QDebug>
NewData::NewData(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewData)
{
    ui->setupUi(this);
    connect(ui->strokecombox,SIGNAL(Activated),this,SLOT(on_stroketypechange));
}

NewData::~NewData()
{
    delete ui;
}

QStringList NewData::insertData()
{
    QStringList itemStrList;
    QString gender;
    QString serialnumber = ui->serialnumber->text();
    QString name = ui->namelab->text();
    bool manbool = ui->manradbtn->isChecked();
    bool womanbool = ui->womanradbtn->isChecked();
    if (manbool)
    {
        gender = "男";
    }
    if (womanbool)
    {
        gender = "女";
    }
    QString birthdate = ui->bridateedit->text();
    QString weight = ui->weigthlab->text();
    QString team = ui->teamcombox->currentText();
    QString birdate = ui->bridateedit->text();
    QString sportlevel = ui->sportlevelcombox->currentText();
    QString stroke = ui->strokecombox->currentText();
    QString type = ui->typecombox->currentText();
    QString trainphasse = ui->trainphasse->currentText();
    QString testdate = ui->testdate->text();
    QString testenv = ui->testenv->currentText();
    QString testdistance = ui->testdistance->text();
    QString powerone = ui->powerone->text();
    QString powertwo = ui->powertwo->text();
    QString powerthree = ui->powerthree->text();
    QString notes = ui->plainTextEdit->toPlainText();
    QString age = getAge(birdate);

    itemStrList.append(serialnumber);
    itemStrList.append(gender);
    itemStrList.append(weight);
    itemStrList.append(age);
    itemStrList.append(stroke);
    itemStrList.append(type);
    itemStrList.append(sportlevel);
    itemStrList.append(testdistance);
    itemStrList.append(powerone);
    itemStrList.append(powertwo);
    itemStrList.append(powerthree);
    itemStrList.append(team);
    itemStrList.append(trainphasse);
    itemStrList.append(testdate);
    itemStrList.append(testenv);
    itemStrList.append(notes);

    return itemStrList;
}

QString NewData::dataFormat()
{

}

QString NewData::getAge(QString birdate)
{
    QDateTime curdate = QDateTime::currentDateTime();//获取系统现在的时间
    int curyear = curdate.toString("yyyy/MM/dd").split('/')[0].toInt();
    int biryear = birdate.split('/')[0].toUInt();
    QString age = QString::number(curyear-biryear);
    return age;
}

void NewData::on_stroketypechange()
{
    qDebug()<< "泳姿类型改变";
}
