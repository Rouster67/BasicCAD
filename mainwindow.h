#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QCloseEvent>
#include <QFile>
#include <QDir>
#include <QSettings>
#include <QFileSystemWatcher>
#include <QTreeWidget>
#include "addevent.h"
#include "addcomment.h"
#include "processing.h"
#include "Entries.h"
#include "RFileManip.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    //container for events
    Entries *entries;

    //can limit some proceses from running if another process sets this to true
    bool processing = false;

    //generates event number
    static int RawEventNumber;
    QString NewEventNumber{"ERROR"};

    //functions
    void shutdown();
    void tick();

    bool file_check();
    void gen_eventnumber();

    //path to all config files
    QString path{};

    //path to system.ini
    QString SystemINI; //makeup = path + System.ini

    //path to Open_Log file
    QString SOpen_Log;      //makeup = path + "Config/EventLogs/" + "Open_Log.csv";
    RFile *OpenLog;

    //path to current days log file
    QString logfile;        //makeup = path + "Config/EventLogs/" + fprefix + fsuffix;
    QString fprefix{"fprefixNotSet"};
    const QString fsuffix{"_Log.csv"};

    //declares file watcher
    QFileSystemWatcher watcher;

    //Admin Commands
    bool forceShutDown = false;

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_listView_indexesMoved(const QModelIndex &indexes);

    void on_Input_Edit_returnPressed();

    void on_Open_Display_viewportEntered();

    void on_actionEvent_triggered();

    void on_Calendar_Dispaly_selectionChanged();

    void on_Calendar_Dispaly_activated(const QDate &date);

    void on_CalendarSelection_linkActivated(const QString &link);

    void on_Calendar_Reset_clicked();

    void on_actionComment_triggered();

    void on_Open_Display_itemDoubleClicked(QTreeWidgetItem *item, int column);

    void on_Open_Display_itemSelectionChanged();

public slots:
    void FLock(QString &file);
    void FUnLock(QString &file);
    void read();
    void write();

protected:
    void closeEvent(QCloseEvent *event);
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H





//implement comments in mainwindow.ui and addcomment.ui
//implement transfer of info from Open_Log.csv to *date*_Log.csv
//implement closed events tab
    //selecting a day from calander should change what displays in closed_Display
//implement officers
    //in the officers tab active officers will appear as children under active parent
    //when an officer is assigned to a call
        //in officer tab they will be placed as a child with the event number as the parent. Primary officer should be on top and highlighted
        //in the open tab the primary officer should be displayed
//implement export functions
//implement accounts with 3 levels
    //officer- can only see and export info but may add themselves as an officer
    //dispatcher - can add events and comment. can edit specified data such ans and event location
    //admin - can edit all info and change information stored in System.ini and Accounts.ini
//creat admin panel
    //ability to move path with move function that moves all files
    //ability to add accounts
    //ability to view calls and comment in a way that displays the dispatcher who entered the info
//implement and/or finilize ini files using qsettings
    //1) system wide settings - stored in path/config
        //path
        //eventnumber
    //2) account based settings - stored in path/config/accounts
        //hold user name and passwords as well as account variables and settings
        //must be encrypted for account security

//Bugs:
//comma input bug
