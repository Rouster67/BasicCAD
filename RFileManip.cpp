#include "RFileManip.h"

//static initilization
bool RFile::locked {false};

//Constructor
RFile::RFile()
{

}

//Copy
RFile::RFile(const RFile &source)
    :file{source.file}, originalFile{source.originalFile}, entries{source.entries}, path{source.path}
{

}

//Deconstructor
RFile::~RFile()
{

}

//Methods
bool RFile::setup(Entries *ptr_entries, QString filename)
{
    entries = ptr_entries;
    file = filename;
    originalFile = filename;

    if(originalFile == filename && entries == ptr_entries && file == filename)
        return true;
    else
        return false;
}

bool RFile::setfile(QString filename)
{
    originalFile = filename;
    file = path + originalFile;
    if(originalFile == filename && file == path + originalFile)
        return true;
    else
        return false;
}

bool RFile::setpath(QString pathname)
{
    path = pathname;
    file = path + originalFile;
    if(file == path + originalFile && path == pathname)
        return true;
    else
        return false;
}

bool RFile::lock()
{
//    QStringList checkparse = file.split("--");
//    QStringList checkparse2 = (checkparse.at(1)).split(".");

    if(!locked)
    {

        //creates name for the temp file
        QStringList parse = file.split(".");
        QString temp;
        temp = parse.at(0) + "--lock." + parse.at(1);

        //Prevents user from adding any more write functions to the stack
        locked = true;

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


        if(QDir().exists(temp))
            return true;
        else
            return false;
    }
}

bool RFile::unlock()
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
            locked = false;

            if(QDir().exists(file))
            {
                if(QDir().exists(temp))
                    return false;
                else
                    return true;
            }
            else
                return false;
        }else
        {
            qWarning() << "Unable to unlock" << file << "it was never locked";
            return false;
        }
}

bool RFile::read()
{
    //reads data from storage into ram
        QFile read(file);
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
                    {
                            qWarning() << "WARNING: Failed to add event";
                            return false;
                    }
                    ++i;
                }
            }
            read.close();
            return true;
        }else
        {
            return false;
        }
        read.close();
}

bool RFile::write()
{
    //reads from RAM and writes to database
    QFile write(file);
    if(!write.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
        qWarning() << "Unable to open file for writing:" << file;
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
}

bool RFile::islocked()
{
    return locked;
}

QString RFile::get()
{
    return file;
}
