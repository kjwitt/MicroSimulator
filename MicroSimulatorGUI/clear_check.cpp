#include "clear_check.h"
#include "ui_clear_check.h"

Clear_Check::Clear_Check(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Clear_Check)
{
    ui->setupUi(this);
}

Clear_Check::~Clear_Check()
{
    delete ui;
}
