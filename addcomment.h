#ifndef ADDCOMMENT_H
#define ADDCOMMENT_H

#include <QDialog>
#include <vector>
#include <QTimer>
#include <QFileSystemWatcher>
#include <QTime>
#include <QTreeWidgetItem>
#include "RFileManip.h"
#include "Entries.h"

namespace Ui {
class AddComment;
}

class AddComment : public QDialog
{
    Q_OBJECT

public:    
    Entries *thisEntries;
    RFile *thisOpenLog;
    QString thisEventNumber;
    size_t index;

    QFileSystemWatcher watcher;

    void set_Data(Entries *entries, RFile *OpenLog, QTreeWidgetItem *item);

    explicit AddComment(QWidget *parent = nullptr);
    ~AddComment();

signals:
    void locksig(QString &SOpen_Log);
    void writesig();

public slots:
    void reset_Data();

private slots:
    void on_Update_Button_clicked();

    void on_Close_Button_clicked();

    void on_AddComment_Button_clicked();

    void on_Comment_Input_returnPressed();

    void on_CallType_Input_returnPressed();

    void on_RP_Input_returnPressed();

    void on_Phone_Input_returnPressed();

    void on_Location_Input_returnPressed();



    void on_CompleteCall_Button_clicked();

private:
    Ui::AddComment *ui;
};

#endif // ADDCOMMENT_H
