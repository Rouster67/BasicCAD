#include "addevent.h"
#include "ui_addevent.h"

AddEvent::AddEvent(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddEvent)
{
    ui->setupUi(this);
    this->setWindowTitle("New Event");
    ui->SubmitButton->setDefault(true);
}

AddEvent::~AddEvent()
{
    delete ui;
}

void AddEvent::on_SubmitButton_clicked()
{
    //gets current date and time
    QDateTime dateTime = dateTime.currentDateTime();

    //generates a new event number
    QString dateTimeString =dateTime.toString("MMddyy");

    //variables to be grabbed from mainwindow.cpp
    Location = ui->LocationInput->text();
    Phone = ui->PhoneInput->text();
    RP = ui->RPInput->text();
    Event = ui->EventTypeInput->text();
    Comment = ui->CommentInput->text();
    Time = dateTime.toString("MM/dd/yyyy hh:mm:ss");

    accept();
}

void AddEvent::on_CancelButton_clicked()
{
    close();
}
