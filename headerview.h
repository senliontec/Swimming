#ifndef HEADERVIEW_H
#define HEADERVIEW_H

#include <QHeaderView>
#include <QCheckBox>
#include <QtDebug>
#include <stdbool.h>
#include <QMap>
class TableQHeaderView : public QHeaderView
{
    Q_OBJECT
public:
    explicit TableQHeaderView(Qt::Orientation orientation, QWidget * parent =0)
    : QHeaderView(orientation, parent){
        headercbx0  = new QCheckBox(this);
        headercbx0->setVisible(true);
        setSectionsClickable(true);
        connect(this, SIGNAL(sectionClicked(int)),this,SLOT(onHeaderCbxClicked(int)));
    }


protected:
    void updateGeometries(){
        headercbx0->move(sectionPosition(0) + 3, 6);
    }


public:
    QCheckBox *headercbx0;
};

#endif // HEADERVIEW_H
