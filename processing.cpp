#include "processing.h"
#include "ui_processing.h"

Processing::Processing(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Processing)
{
    ui->setupUi(this);
    QApplication::beep();
}

Processing::~Processing()
{
    delete ui;
}

void Processing::on_OKButton_clicked()
{
    close();
}

