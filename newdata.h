#ifndef NEWDATA_H
#define NEWDATA_H

#include <QStandardItem>
#include <QDialog>
#include <QList>
#include <QDateTime>
namespace Ui {
class NewData;
}

class NewData : public QDialog
{
    Q_OBJECT

public:
    explicit NewData(QWidget *parent = nullptr);
    ~NewData();

private:
    QString dataFormat();
    QString getAge(QString birdate);

public:
    QStringList insertData();

private slots:
    void on_stroketypechange();

private:
    Ui::NewData *ui;
};

#endif // NEWDATA_H
