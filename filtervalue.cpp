#include "filtervalue.h"
#include "ui_filtervalue.h"

FilterValue::FilterValue(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FilterValue)
{
    ui->setupUi(this);
}

FilterValue::~FilterValue()
{
    delete ui;
}

void FilterValue::getFilterValue()
{
    QString gender;
    bool allperson = ui->allradbtn->isChecked();
    bool man = ui->manradbtn->isChecked();
    bool woman = ui->womanradbtn->isChecked();
    QString start_age = ui->agestartlab->text();
    QString end_age = ui->endstartlab->text();
    QString test_start_date = ui->datestartedit->text();
    QString test_end_date = ui->dateendedit->text();
    QString test_env = ui->testenvcombox->currentText();
    QString sport_level = ui->sportlevelcombox->currentText();
    QString stroke = ui->strokecombox->currentText();
    QString stroke_type = ui->typecombox->currentText();

    if (allperson)
        gender = "all";
    if (man)
        gender = "男";
    if (woman)
        gender = "女";

    if (test_env == "全部")
        test_env = "all";
    if (sport_level == "全部")
        sport_level = "all";
    if (stroke == "全部")
        stroke = "all";
    if (stroke_type == "全部")
        stroke_type = "all";

    int start_date = test_start_date.split('/')[0].toUInt();
    int end_date = test_end_date.split('/')[0].toUInt();
    QString age = QString::number(end_date - start_date);

    filtervalueMap.insert("性别",gender);
    filtervalueMap.insert("测试环境",test_env);
    filtervalueMap.insert("运动等级",sport_level);
    filtervalueMap.insert("泳姿",stroke);
    filtervalueMap.insert("类别",stroke_type);
}
