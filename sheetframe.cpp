#include "sheetframe.h"
#include "ui_sheetframe.h"

SheetFrame::SheetFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::SheetFrame)
{
    ui->setupUi(this);
}

SheetFrame::~SheetFrame()
{
    delete ui;
}
