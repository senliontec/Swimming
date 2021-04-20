#ifndef SHEETFRAME_H
#define SHEETFRAME_H

#include <QFrame>

namespace Ui {
class SheetFrame;
}

class SheetFrame : public QFrame
{
    Q_OBJECT

public:
    explicit SheetFrame(QWidget *parent = nullptr);
    ~SheetFrame();

private:
    Ui::SheetFrame *ui;
};

#endif // SHEETFRAME_H
