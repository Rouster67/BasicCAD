#include "Event.h"

//Static Initilization
int Event::TotalEvents {0};

//Constructor
Event::Event(QString EventType)
:EventType {"none"}, EventTime {"none"}
{
    ++TotalEvents;
}

//Copy
Event::Event(const Event &source)
    :EventType{source.EventType}, EventTime{source.EventTime}, EventNumber{source.EventNumber}, Location{source.Location}, RP{source.RP}, Phone{source.Phone}, Comment{source.Comment}, CommentTime{source.CommentTime}
{
    ++TotalEvents;
}

//Deconstructor
Event::~Event()
{
    --TotalEvents;
}

//Methods
QString Event::get_EventType()
{
    return EventType;
}

QString Event::get_EventTime()
{
    return EventTime;
}

QString Event::get_EventNumber()
{
    return EventNumber;
}

QString Event::get_Location()
{
    return Location;
}

QString Event::get_RP()
{
    return RP;
}

QString Event::get_Phone()
{
    return Phone;
}

QString Event::get_Comment(size_t i)
{
    if(i>=0 && i<Comment.size())
        return Comment.at(i);
    else
        return "No Value";
}

QString Event::get_CommentTime(size_t i)
{
    if(i>=0 && i<CommentTime.size())
        return CommentTime.at(i);
    else
        return "No Value";
}

size_t Event::get_CommentSize()
{
    return Comment.size();
}

void Event::update_EventType(QString NewEventType, QString NewCommentTime)
{

    QString temp = EventType + " updated to " + NewEventType;

    EventType = NewEventType;
    set_Comment(temp, NewCommentTime);
}

void Event::set_EventType(QString NewEventType, QString NewCommentTime)
{
    EventType = NewEventType;
}

void Event::set_EventNumber(QString NewEventNumber)
{
    EventNumber = NewEventNumber;
}

void Event::set_Comment(QString NewComment, QString NewCommentTime)
{
    //if this is the first comment set EventTime to date
    if(CommentTime.size() == 0)
        EventTime = NewCommentTime;

    //add the NewComment and date to vectors
    Comment.push_back(NewComment);
    CommentTime.push_back(NewCommentTime);
}

void Event::set_Location(QString NewLocation)
{
    Location = NewLocation;
}

void Event::set_RP(QString NewRP)
{
    RP = NewRP;
}

void Event::set_Phone(QString NewPhone)
{
    Phone = NewPhone;
}

int Event::get_Events()
{
    return TotalEvents;
}
