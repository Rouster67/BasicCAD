#include "Entries.h"
#include "qdatetime.h"

//Constructor
Entries::Entries()
{

}

//Copy
Entries::Entries(const Entries &source)
{

}

//Deconstructor
Entries::~Entries()
{

}

//Methods
bool Entries::add_Event(QString EventNumber, QString EventType, QString Location, QString RP, QString Phone, QString NewCommentTime)
{
    Event NewEvent;
    NewEvent.set_EventNumber(EventNumber);
    NewEvent.set_EventType(EventType, NewCommentTime);
    NewEvent.set_Location(Location);
    NewEvent.set_RP(RP);
    NewEvent.set_Phone(Phone);
    Open.push_back(NewEvent);

    bool temp = true;

    if((Open.at(Open.size()-1)).get_EventNumber() != EventNumber)
        temp = false;
    if((Open.at(Open.size()-1)).get_EventType() != EventType)
        temp = false;
    if((Open.at(Open.size()-1)).get_Location() != Location)
        temp = false;
    if((Open.at(Open.size()-1)).get_RP() != RP)
        temp = false;
    if((Open.at(Open.size()-1)).get_Phone() != Phone)
        temp = false;

    return temp;
}

bool Entries::set_Event(size_t Event, QString EventType, QString NewCommentTime)
{
    if(Open.size()>=0 && Event>=0 && Event<Open.size())
    {
        (Open.at(Event)).set_EventType(EventType, NewCommentTime);
        return true;
    }else
        return false;
}

bool Entries::set_EventNumber(size_t Event, int &RawEventNumber)
{
    if(Open.size()>=0 && Event>=0 && Event<Open.size())
    {
        QString NewEventNumber {"E"};

        QDateTime dateTime = dateTime.currentDateTime();
        QString dateTimeString = dateTime.toString("MMddyy");

        RawEventNumber += 1;

        QString ConvertedEventNumber = QString::number(RawEventNumber).rightJustified(3, '0');

        NewEventNumber = NewEventNumber + dateTimeString + ConvertedEventNumber;

        (Open.at(Event)).set_EventNumber(NewEventNumber);
        return true;
    }else
        return false;
}

bool Entries::set_Comment(size_t Event, QString Comment, QString NewCommentTime)
{
    if(Event>=0 && Event<Open.size())
    {
        (Open.at(Event)).set_Comment(Comment, NewCommentTime);
        return true;
    }else
        return false;
}

bool Entries::set_Location(size_t Event, QString NewLocation, QString NewCommentTime)
{
    if(Event>=0 && Event<Open.size())
    {
        (Open.at(Event)).set_Location(NewLocation);
        return true;
    }else
        return false;
}

bool Entries::set_RP(size_t Event, QString NewRP, QString NewCommentTime)
{
    if(Event>=0 && Event<Open.size())
    {
        (Open.at(Event)).set_RP(NewRP);
        return true;
    }else
        return false;
}

bool Entries::set_Phone(size_t Event, QString NewPhone, QString NewCommentTime)
{
    if(Event>=0 && Event<Open.size())
    {
        (Open.at(Event)).set_Phone(NewPhone);
        return true;
    }else
        return false;
}

QString Entries::get_EventType(size_t Event)
{
    return (Open.at(Event)).get_EventType();
}

QString Entries::get_EventNumberOpen(size_t Event)
{
    return (Open.at(Event)).get_EventNumber();
}

QString Entries::get_EventNumberClosed(size_t Event)
{
    return (Closed.at(Event)).get_EventNumber();
}

QString Entries::get_Closed(size_t Event)
{
    return (Closed.at(Event)).get_EventType();
}

QString Entries::get_EventTime(size_t Event)
{
    return (Open.at(Event)).get_EventTime();
}

QString Entries::get_Location(size_t Event)
{
    return (Open.at(Event)).get_Location();
}

QString Entries::get_RP(size_t Event)
{
    return (Open.at(Event)).get_RP();
}

QString Entries::get_Phone(size_t Event)
{
    return (Open.at(Event)).get_Phone();
}

QString Entries::get_Comment(size_t Event, size_t Comment)
{
    return (Open.at(Event)).get_Comment(Comment);
}

QString Entries::get_CommentTime(size_t Event, size_t CommentTime)
{
    return (Open.at(Event)).get_CommentTime(CommentTime);
}

size_t Entries::get_CommentSize(size_t Event)
{
    return (Open.at(Event)).get_CommentSize();
}

size_t Entries::get_Open()
{
    return Open.size();
}

size_t Entries::get_Closed()
{
    return Closed.size();
}

size_t Entries::get_Events()
{
    return Event::get_Events();
}

bool Entries::close_Event(size_t Selection, QString Disposition, QString NewCommentTime)
{
    if(Selection>=0 && Selection<Open.size())
    {
        QString temp = "All Officers clear ";
        Disposition = temp + Disposition;

        (Open.at(Selection)).set_Comment(Disposition, NewCommentTime);

        Closed.push_back(Open.at(Selection));
        Open.erase(Open.begin()+Selection);

        return true;
    }else
        return false;
}

bool Entries::reopen_Event(size_t Selection, QString Dispatcher, QString Reason, QString NewCommentTime)
{
    if(Selection>=0 && Selection<Closed.size())
    {
        Reason = "Event opened by " + Dispatcher + ". Reason: " + Reason;
        (Closed.at(Selection)).set_Comment(Reason, NewCommentTime);
        Open.push_back(Closed.at(Selection));
        Closed.erase(Closed.begin()+Selection);

        return true;
    }else
        return false;
}

bool Entries::clear_Open()
{
    Open.clear();
    if(Open.size()==0)
        return true;
    else
        return false;
}

bool Entries::read(QString file)//needs code
{

    return false;
}

Event *Entries::return_Event(size_t i)
{
    return &(Open.at(i));
}
