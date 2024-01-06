#include "mainwindow.h"
#include "./ui_mainwindow.h"

int MainWindow::RawEventNumber{0};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    qDebug();
    qDebug() << "Startup function started";
    //sets windowtitle
    this->setWindowTitle("BasiCAD");

    //starts program maximized
    QWidget::showMaximized();

    //creates container
    entries = new Entries;

    //create file pointers
    OpenLog = new RFile;
    if(!OpenLog->setup(entries, "Open_Log.csv"))
        qWarning() << "Unable to setup OpenLog";

    //stylizations
    ui->Open_Display->setStyleSheet("QHeaderView::section { background-color:rgb(0, 0, 127) }" "QHeaderView::section { color:rgb(255, 255, 255) }");
    ui->Open_Display->setAllColumnsShowFocus(true);
    ui->Closed_Display->setStyleSheet("QHeaderView::section { background-color:rgb(0, 0, 127) }" "QHeaderView::section { color:rgb(255, 255, 255) }");
    ui->Closed_Display->setAllColumnsShowFocus(true);
    ui->Officers_Display->setStyleSheet("QHeaderView::section { background-color:rgb(0, 0, 127) }" "QHeaderView::section { color:rgb(255, 255, 255) }");
    ui->Officers_Display->setAllColumnsShowFocus(true);

    //set Closed Display Label to show current date
    ui->CalendarSelection->setText(ui->Calendar_Dispaly->selectedDate().toString("MM/dd/yy"));

    //set DateTime label to current time
    QDateTime dateTime = dateTime.currentDateTime();
    QString dateTimeString = dateTime.toString("MM/dd/yy hh:mm");
    ui->DateTime->setText(dateTimeString);

    //checks file paths
    if(!file_check())
        qWarning() << "file_check() failed";

    qDebug() << "Startup function ended";
    qDebug();

    //starts tick function
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&MainWindow::tick));
    timer->start(1000);

    //starts watching paths
    MainWindow::connect(&watcher, SIGNAL(fileChanged(QString)), this, SLOT(read()));

    read();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::shutdown()
{
    qDebug() << "Exit Called";
}

void MainWindow::tick()
{
    //gets current time every tick
    QDateTime dateTime = dateTime.currentDateTime();

    //debug lines
    QString dateTimeSecondsString = dateTime.toString("MM/dd/yyyy hh:mm:ss");
    qDebug() << "tick at" << dateTimeSecondsString;
    qDebug() << "Open File:" << OpenLog->get();
    qDebug() << "logfile:" << logfile;
    qDebug() << "RawEventNumber:" << MainWindow::RawEventNumber;

    //daily maintenance
    QString timeCheck = dateTime.toString("hhmmss");
    if(timeCheck == "000000")
    {
        qDebug() << "Daily Maintenance function started";

        qDebug() << "Daily Maintance function Ended";
    }

    //updates DateTime display
    QString dateTimeString = dateTime.toString("MM/dd/yy hh:mm");
    ui->DateTime->setText(dateTimeString);

    qDebug();
}

void MainWindow::read()
{
     //reads data from storage into ram
     QFile read(OpenLog->get());
     if(read.open(QIODevice::ReadOnly | QIODevice::Text))
     {
         QStringList column;
         QTextStream in(&read);
         entries->clear_Open();
         int i{-1};

         while(!in.atEnd())
         {
             QString line = in.readLine();
             column.clear();
             column.append(line.split(","));
             if(column.at(0) == "--")
             {
                 QString CommentTime = column.at(1);
                 QString Comment = column.at(5);

                 entries->set_Comment(i, Comment, CommentTime);
             }else
             {
                 QString EventNumber = column.at(0);
                 QString EventTime = column.at(1);
                 QString Location = column.at(2);
                 QString RP = column.at(3);
                 QString Phone = column.at(4);
                 QString EventType = column.at(5);

                 if(!entries->add_Event(EventNumber, EventType, Location, RP, Phone, EventTime))
                         qWarning() << "WARNING: Failed to add event";
                 ++i;
             }
         }
     }
     read.close();

    //reads data from RAM into the display (Open_Display)
    if(entries->get_Open()>0)
    {
        ui->Open_Display->clear();

        for(size_t i{0};i<entries->get_Open();++i)
        {
            QBrush Event_Foreground (Qt::white);
            QBrush Event_Background (Qt::darkGray);
            QBrush Comment_Foreground (Qt::white);
            QTreeWidgetItem *treeItem1 = new QTreeWidgetItem(ui->Open_Display);
            treeItem1->setText(0, entries->get_EventNumberOpen(i));
            treeItem1->setBackground(0, Event_Background);
            treeItem1->setForeground(0, Event_Foreground);
            treeItem1->setText(1, entries->get_EventTime(i));
            treeItem1->setBackground(1, Event_Background);
            treeItem1->setForeground(1, Event_Foreground);
            treeItem1->setText(2, entries->get_Location(i));
            treeItem1->setBackground(2, Event_Background);
            treeItem1->setForeground(2, Event_Foreground);
            treeItem1->setText(3, entries->get_RP(i));
            treeItem1->setBackground(3, Event_Background);
            treeItem1->setForeground(3, Event_Foreground);
            treeItem1->setText(4, entries->get_Phone(i));
            treeItem1->setBackground(4, Event_Background);
            treeItem1->setForeground(4, Event_Foreground);
            treeItem1->setText(5, entries->get_EventType(i));
            treeItem1->setBackground(5, Event_Background);
            treeItem1->setForeground(5, Event_Foreground);
            QString s = QString::number(i);
            treeItem1->setText(6, s);
            for(size_t j{0};j<entries->get_CommentSize(i); ++j)
            {
                QTreeWidgetItem *treeItem2 = new QTreeWidgetItem();
                treeItem2->setFlags(Qt::ItemIsSelectable);
                treeItem2->setForeground(1, Comment_Foreground);
                treeItem2->setForeground(5, Comment_Foreground);
                treeItem2->setText(1, entries->get_CommentTime(i, j));
                treeItem2->setText(5, entries->get_Comment(i, j));
                treeItem1->addChild(treeItem2);
                treeItem1->setExpanded(true);
            }
        }

    }
    //formats tables
    ui->Open_Display->resizeColumnToContents(0);
    ui->Open_Display->resizeColumnToContents(1);
    ui->Open_Display->resizeColumnToContents(2);
    ui->Open_Display->resizeColumnToContents(3);
    ui->Open_Display->resizeColumnToContents(4);

    //reads systemini
    QSettings systemini(SystemINI, QSettings::IniFormat);

    forceShutDown = systemini.value("AdminCommands/forceShutDown").toBool();
    if(forceShutDown)
        close();
}

void MainWindow::write()
{    
    if(processing)
    {
        Processing *p = new Processing;
        p->exec();
    }else
    {
        processing = true;
        QFile write(OpenLog->get());
        if(!write.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
            qWarning() << "Unable to open file for writing:" << OpenLog->get();

        //writes all info in RAM to file
        QTextStream out(&write);
        for(size_t i{0};i<entries->get_Open();++i)
        {
            out << entries->get_EventNumberOpen(i) << ","
                << entries->get_EventTime(i) << ","
                << entries->get_Location(i) << ","
                << entries->get_RP(i) << ","
                << entries->get_Phone(i) << ","
                << entries->get_EventType(i);
            out << "\n";
                for(size_t j{0};j<entries->get_CommentSize(i);++j)
                {
                    out << "--,"
                        << entries->get_CommentTime(i, j)
                        << "," << "," << "," << ","
                        << entries->get_Comment(i, j);
                    out << "\n";
                }
        }
        write.close();

        //releases file for the rest of the program to use
        OpenLog->unlock();
        processing = false;

        read();
    }
}

bool MainWindow::file_check()
{
    bool Return{true};

//Config Dir
    //creates Config folder if needed
    if(!QDir("Config").exists())
    {
        QDir().mkdir("Config");
        if(QDir("Config").exists())
        {
            qDebug() << "Config directory created";
        }else
        {
            qWarning() << "\nWARNING: Unable to create Config directory\n";
            Return = false;
        }
    }

//Config Files
    //creates System.ini if it dosnt exist
    SystemINI = path + "Config/" + "System.ini";
    QFile System(SystemINI);
    if(!System.exists())
    {
        QSettings systemini(SystemINI, QSettings::IniFormat);

        systemini.beginGroup("AdminCommands");
        systemini.setValue("forceShutDown", false);
        systemini.endGroup();

        systemini.beginGroup("EventNumbers");
        systemini.setValue("EventDate", 0000);
        systemini.setValue("RawEventNumber", 0);
        systemini.endGroup();

        if(System.exists())
            qDebug() << "System.ini created";
        else
        {
            qWarning() << "\nWARNING: Unable to create System.ini\n";
            Return = false;
        }
    }
    //starts wathcing this path
    watcher.addPath(SystemINI);

//EventLogs Dir
    //creates eventlog folder if needed
    if(!QDir("Config/EventLogs").exists())
    {
        QDir().mkdir("Config/EventLogs");

        if(QDir("Config/EventLogs").exists())
        {
            qDebug() << "EventLogs directory created";
        }else
        {
            qWarning() << "\nWARNING: Unable to create EventLogs directory\n";
            Return = false;
        }
    }


//EventLogs Files
    //creates Open_Log.csv if it dosnt exist
    QString localPath = path + "Config/EventLogs/";
    OpenLog->setpath(localPath);
    OpenLog->setfile("Open_Log.csv");
    QFile Open_Log(OpenLog->get());
    if(!Open_Log.exists())
    {
        Open_Log.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append);
        Open_Log.close();

        if(Open_Log.exists())
            qDebug() << "Open_Log.csv created";
        else
        {
            qWarning() << "\nWARNING: Unable to create Open_Log.csv\n";
            Return = false;
        }
    }
    watcher.addPath(OpenLog->get());

    //creates daily log if it dosnt exist
    QDateTime dateTime = dateTime.currentDateTime();
    fprefix = dateTime.toString("yyyy-MM-dd");
    logfile = path + "Config/EventLogs/" + fprefix + fsuffix;
    QFile log(logfile);
    if(!log.exists())
    {
        log.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append);
        log.close();

        if(log.exists())
            qDebug() << logfile << "created";
        else
        {
            qWarning() << "\nWARNING: Unable to create" << logfile << "\n";
            Return = false;
        }
    }

    return Return;
}

void MainWindow::on_listView_indexesMoved(const QModelIndex &indexes)
{

}

//comment input
void MainWindow::on_Input_Edit_returnPressed()
{
    //only executes if column 0 has an event number and ui has input
    if(ui->Input_Edit->text() != "" && (ui->Open_Display->selectedItems().at(0)->text(0)).size()>=10)
    {
        //gets event number
        QString eventNumber = ui->Open_Display->selectedItems().at(0)->text(0);

        //gets event index
        size_t index = 0;
        for(size_t i{0};i<entries->get_Open();++i)
        {
            if(entries->get_EventNumberOpen(i) ==  eventNumber)
            {
                index = i;
            }
        }

        //gets current date and time
        QDateTime dateTime = dateTime.currentDateTime();
        QString timestamp = dateTime.toString("MM/dd/yyyy hh:mm:ss");

        //locks file
        OpenLog->lock();

        //adds comment to RAM
        entries->set_Comment(index, ui->Input_Edit->text(), timestamp);

        write();

        ui->Input_Edit->clear();
    }
}


void MainWindow::on_Open_Display_viewportEntered()
{

}

//file -> New -> Event
void MainWindow::on_actionEvent_triggered()
{
    if(processing)
    {
        Processing *p = new Processing;
        p->exec();
    }else
    {
        AddEvent *ae = new AddEvent;
        ae->exec();

        if(ae->result() == 1)
        {
            //locks other processes from accesing file
            OpenLog->lock();

            //generates a new event number
            gen_eventnumber();

            //writes to RAM
            size_t i {entries->get_Open()};
            entries->add_Event(NewEventNumber, ae->Event,ae->Location, ae->RP, ae->Phone, ae->Time);
            entries->set_Comment(i, ae->Comment, ae->Time);

            //reads from RAM and writes to database
            QFile write(OpenLog->get());
            if(!write.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
                qWarning() << "Unable to open file for writing:" << OpenLog->get();
            QTextStream out(&write);
            out << entries->get_EventNumberOpen(i) << ","
                << entries->get_EventTime(i) << ","
                << entries->get_Location(i) << ","
                << entries->get_RP(i) << ","
                << entries->get_Phone(i) << ","
                << entries->get_EventType(i);
            out << "\n";
            out << "--,"
                << entries->get_CommentTime(i, 0)
                << "," << "," << "," << ","
                << entries->get_Comment(i, 0);
            out << "\n";
            write.close();

            //releases file for other processes to access
            OpenLog->unlock();
        }

        ae->close();
        read();
    }
}

//file -> New -> Comment
void MainWindow::on_actionComment_triggered()
{
    if(!ui->Open_Display->selectedItems().isEmpty())
        on_Open_Display_itemDoubleClicked(ui->Open_Display->currentItem(), 0);
}

//Open_Display -> double click item
void MainWindow::on_Open_Display_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    //only executes if column 0 has an event number
    if((item->text(0)).size()>=10)
    {
        //executes window
        AddComment *ac = new AddComment;

        //creates write signal
        connect(ac,&AddComment::writesig,this,&MainWindow::write);
        connect(ac, &AddComment::locksig, this, &MainWindow::FLock);


        //initilizes needed data
        ac->set_Data(entries, OpenLog, item);

        if(ac->result() == 1)
        {
            //code here
        }
    }
}

void MainWindow::FLock(QString &file)
{
    //Example:
        //FLock(MyFile);
        //QFile write(MyFile);
        //write.open;
        //write.close;
        //FUnLock(MyFile);

    //creates name for the temp file
    QStringList parse = file.split(".");
    QString temp;
    temp = parse.at(0) + "--lock." + parse.at(1);

    //Prevents user from adding any more write functions to the stack
    processing = true;

    //checks to see if temp exists. If it does program will wait up to 30 seconds.
    int looper{0};
    while(QDir().exists(temp))
    {
        QTime dieTime= QTime::currentTime().addSecs(1);
        while(QTime::currentTime()<dieTime)
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        qDebug()<<"loop:" << looper;
        if(looper > 30)
        {
            QDir().remove(temp);
        }
        ++looper;
    }

    read();

    //copys file into a temp file. Locking file in the process.
    QFile copy(file);
    copy.copy(temp);

    //changes the file name to reflect its lock state
    file = temp;


//    if(QDir().exists(temp))
//        return true;
//    else
//        return false;
}

void MainWindow::FUnLock(QString &file)
{
    QStringList checker1 = file.split("--");
    QStringList checker2 = checker1.at(1).split(".");

    if(checker2.at(0) == "lock")
    {

        //declares -lock.csv as temp
        QString temp = file;
        QStringList parse = temp.split("--");
        QStringList parse2 = parse.at(1).split(".");
        file = parse.at(0) + "." + parse2.at(1);

        //reads -lock.csv into linein
        QFile read(temp);
        read.open(QIODevice::ReadOnly | QIODevice::Text);
        QTextStream in(&read);
        QString linein = in.readAll();
        read.close();

        //writes linin into file
        QFile write(file);
        write.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate);
        QTextStream out(&write);
        out << linein;
        write.close();

        //delete temp file.
        QDir().remove(temp);

        //allows users to again add write functions
        processing = false;

//        if(QDir().exists(file))
//        {
//            if(QDir().exists(temp))
//                return false;
//            else
//                return true;
//        }
//        else
//            return false;
    }else
    {
        qWarning() << "Unable to unlock" << file << "it was never locked";
//        return false;
    }
}

void MainWindow::gen_eventnumber()
{
    //gets current date and time
    QDateTime dateTime = dateTime.currentDateTime();

    //generates a new event number
    QString dateTimeString =dateTime.toString("MMddyy");

    //decalres access to file without locking
    QSettings systemini(SystemINI, QSettings::IniFormat);

    //resets event numbers if the date is new
    if(systemini.value("EventNumbers/EventDate").toString() != dateTimeString)
    {
        systemini.setValue("EventNumbers/RawEventNumber", 0);
        systemini.setValue("EventNumbers/EventDate", dateTimeString);
    }

    //stores event number from the ini
    RawEventNumber = systemini.value("EventNumbers/RawEventNumber").toInt();

    //iterates event number by 1
    RawEventNumber += 1;
    systemini.setValue("EventNumbers/RawEventNumber", RawEventNumber);

    //formats event number
    QString ConvertedEventNumber = QString::number(RawEventNumber).rightJustified(3, '0');
    NewEventNumber = "E" + dateTimeString + ConvertedEventNumber;
}

void MainWindow::on_Calendar_Dispaly_selectionChanged()
{
    ui->CalendarSelection->setText(ui->Calendar_Dispaly->selectedDate().toString("MM/dd/yy"));
}

void MainWindow::on_Calendar_Dispaly_activated(const QDate &date)
{

}

void MainWindow::on_CalendarSelection_linkActivated(const QString &link)
{

}

void MainWindow::on_Calendar_Reset_clicked()
{
    ui->Calendar_Dispaly->setSelectedDate(QDate::currentDate());
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    shutdown();
    QWidget::closeEvent(event);
}


void MainWindow::on_Open_Display_itemSelectionChanged()
{
    QTreeWidgetItem *item = ui->Open_Display->currentItem();

    QString label{};

    label = "Add Comment\n" + item->text(0) + "\n" + item->text(5);

    if(label == "")
        ui->Input_Label->setText("No Event Selected");
    else
        ui->Input_Label->setText(label);
}

