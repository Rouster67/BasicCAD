#include "addcomment.h"
#include "ui_addcomment.h"

AddComment::AddComment(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddComment)
{
    ui->setupUi(this);
    this->setWindowTitle("Event Edit Window");
    ui->AddComment_Button->setDefault(true);

    //stylizations
    ui->Comment_Display->setStyleSheet("QHeaderView::section { background-color:rgb(0, 0, 127) }" "QHeaderView::section { color:rgb(255, 255, 255) }");

    //starts watching paths
    AddComment::connect(&watcher, SIGNAL(fileChanged(QString)), this, SLOT(reset_Data()));

    //starts tick function
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&AddComment::reset_Data));
    timer->start(5000);
}

AddComment::~AddComment()
{
    delete ui;
}

void AddComment::set_Data(Entries *entries, RFile *OpenLog, QTreeWidgetItem *item)
{   
    //pulls event number from mainwindow
    thisEventNumber = item->text(0);

    //prevents window from openeing if it cant get ahold of an event number
    if(thisEventNumber.size()>=10)
    {
        //initilizes pointers
        thisEntries = entries;
        thisOpenLog = OpenLog;

        //shows the display
        show();

        //starts watching path
        watcher.addPath(OpenLog->get());

        //gets event index
        for(size_t j{0};j<entries->get_Open();++j)
        {
            if(thisEntries->get_EventNumberOpen(j) ==  thisEventNumber)
            {
                index = j;
            }
        }

        //sets title bar to have the event number
        this->setWindowTitle("Event Edit Window - " + thisEventNumber);

        //sets static data
        ui->Event_Display->setText(thisEventNumber);
        ui->Timestamp_Display->setText(thisEntries->get_EventTime(index));
        //sets input data
        ui->CallType_Input->setText(thisEntries->get_EventType(index));
        ui->RP_Input->setText(thisEntries->get_RP(index));
        ui->Phone_Input->setText(thisEntries->get_Phone(index));
        ui->Location_Input->setText(thisEntries->get_Location(index));

        //sets comment data
        if(thisEntries->get_CommentSize(index)>0)
        {
            ui->Comment_Display->clear();
            QBrush Comment_Foreground (Qt::white);
            for(size_t j{0};j<thisEntries->get_CommentSize(index);++j)
            {
                QTreeWidgetItem *treeItem = new QTreeWidgetItem(ui->Comment_Display);
                treeItem->setForeground(0, Comment_Foreground);
                treeItem->setForeground(1, Comment_Foreground);
                treeItem->setText(0, thisEntries->get_CommentTime(index, j));
                treeItem->setText(1, thisEntries->get_Comment(index, j));
                ui->Comment_Display->resizeColumnToContents(0);
                ui->Comment_Display->resizeColumnToContents(1);
            }
        }
    }
}

void AddComment::reset_Data()
{
    //gets event index
    for(size_t j{0};j<thisEntries->get_Open();++j)
    {
        if(thisEntries->get_EventNumberOpen(j) ==  thisEventNumber)
        {
            index = j;
        }
    }

    //refreshes comment data
    if(thisEntries->get_CommentSize(index)>0)
    {
        ui->Comment_Display->clear();
        QBrush Comment_Foreground (Qt::white);
        for(size_t j{0};j<thisEntries->get_CommentSize(index);++j)
        {
            QTreeWidgetItem *treeItem = new QTreeWidgetItem(ui->Comment_Display);
            treeItem->setForeground(0, Comment_Foreground);
            treeItem->setForeground(1, Comment_Foreground);
            treeItem->setText(0, thisEntries->get_CommentTime(index, j));
            treeItem->setText(1, thisEntries->get_Comment(index, j));
            ui->Comment_Display->resizeColumnToContents(0);
            ui->Comment_Display->resizeColumnToContents(1);
        }
    }
}

void AddComment::on_Update_Button_clicked()
{
    //gets current date and time
    QDateTime dateTime = dateTime.currentDateTime();
    QString timestamp = dateTime.toString("MM/dd/yyyy hh:mm:ss");

    //bools
    bool bevent = false;
    bool brp = false;
    bool bphone = false;
    bool blocation = false;

    //gets event index
    for(size_t j{0};j<thisEntries->get_Open();++j)
    {
        if(thisEntries->get_EventNumberOpen(j) ==  thisEventNumber)
        {
            index = j;
        }
    }

    //call the lock
    thisOpenLog->lock();

    //adds info to RAM
    if(thisEntries->get_EventType(index)!=ui->CallType_Input->text())
    {
        thisEntries->set_Event(index, ui->CallType_Input->text(), timestamp);
        bevent = true;
    }

    if(thisEntries->get_RP(index)!=ui->RP_Input->text())
    {
        thisEntries->set_RP(index, ui->RP_Input->text(), timestamp);
        brp = true;
    }

    if(thisEntries->get_Phone(index)!=ui->Phone_Input->text())
    {
        thisEntries->set_Phone(index, ui->Phone_Input->text(), timestamp);
        bphone = true;
    }

    if(thisEntries->get_Location(index)!=ui->Location_Input->text())
    {
        thisEntries->set_Location(index, ui->Location_Input->text(), timestamp);
        blocation = true;
    }

    //adds comment to RAM
    if(bevent || brp || bphone|| blocation)
    {
        QStringList updateCommentList;
        updateCommentList.push_back("Updated");
        if(bevent)
            updateCommentList.push_back("Call Type");
        if(brp)
            updateCommentList.push_back("RP");
        if(bphone)
            updateCommentList.push_back("Phone");
        if(blocation)
            updateCommentList.push_back("Location");
        QString updateComment;
        if(updateCommentList.size()>2)
        {
            for(size_t i{0};i<updateCommentList.size();++i)
            {
                if(i==updateCommentList.size()-1)
                    updateComment = updateComment + " and " + updateCommentList.at(i);
                else if(i==0)
                    updateComment = updateComment + updateCommentList.at(i);
                else
                    updateComment = updateComment + " " + updateCommentList.at(i);

            }
        }else
        {
            updateComment = updateCommentList.at(0) + " " + updateCommentList.at(1);
        }
        thisEntries->set_Comment(index, updateComment, timestamp);

        //Calls write function
        emit writesig();
    }

}


void AddComment::on_Close_Button_clicked()
{
    close();
}

//add comment
void AddComment::on_AddComment_Button_clicked()
{
    if(ui->Comment_Input->text() != "")
    {
        //gets current date and time
        QDateTime dateTime = dateTime.currentDateTime();
        QString timestamp = dateTime.toString("MM/dd/yyyy hh:mm:ss");

        //locks file
        thisOpenLog->lock();

        //adds comment to RAM
        thisEntries->set_Comment(index, ui->Comment_Input->text(), timestamp);

        //calls write function
        emit writesig();

        //clears ui
        ui->Comment_Input->clear();
    }
}


void AddComment::on_Comment_Input_returnPressed()
{
    //on_AddComment_Button_clicked();
}


void AddComment::on_CallType_Input_returnPressed()
{
    on_Update_Button_clicked();
}


void AddComment::on_RP_Input_returnPressed()
{
    on_Update_Button_clicked();
}


void AddComment::on_Phone_Input_returnPressed()
{
    on_Update_Button_clicked();
}


void AddComment::on_Location_Input_returnPressed()
{
    on_Update_Button_clicked();
}


//complete call
void AddComment::on_CompleteCall_Button_clicked()
{
    if(ui->Comment_Input->text() != "")
    {
        on_AddComment_Button_clicked();
        accept();
    }

}

