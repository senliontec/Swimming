#ifndef DATAFILTER_H
#define DATAFILTER_H

#include <QDialog>
#include <QMap>

namespace Ui {
class FilterValue;
}

class FilterValue : public QDialog
{
    Q_OBJECT

public:
    explicit FilterValue(QWidget *parent = nullptr);
    ~FilterValue();
    void getFilterValue();

public:
    QMap<QString,QString> filtervalueMap;

private:
    Ui::FilterValue *ui;
};

#endif // DATAFILTER_H
