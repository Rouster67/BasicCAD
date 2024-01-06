#ifndef ADDEVENT_H
#define ADDEVENT_H

#include <QDialog>
#include <QTime>

namespace Ui {
class AddEvent;
}

class AddEvent : public QDialog
{
    Q_OBJECT

public:
    QString Time;
    QString Location;
    QString Phone;
    QString RP;
    QString Event;
    QString Comment;
    explicit AddEvent(QWidget *parent = nullptr);
    ~AddEvent();

private slots:
    void on_CancelButton_clicked();

    void on_SubmitButton_clicked();

private:
    Ui::AddEvent *ui;

};

#endif // ADDEVENT_H
