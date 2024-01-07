#include "Event.h"

//Static Initilization
int Event::TotalEvents {0};

//Constructor
Event::Event(std::string EventType)
:EventType {"none"}, EventTime {"none"}
{
    ++TotalEvents;
}

//Copy
Event::Event(const Event &source)
:EventType{source.EventType}, EventTime{source.EventTime}, Location{source.Location}, RP{source.RP}, Phone{source.Phone}, Comment{source.Comment}, CommentTime{source.CommentTime}
{
    ++TotalEvents;
}

//Deconstructor
Event::~Event()
{
    --TotalEvents;
}

//Methods
std::string Event::get_EventType()
{
    return EventType;
}

std::string Event::get_EventTime()
{
    return EventTime;
}

std::string Event::get_Location()
{
    return Location;
}

std::string Event::get_RP()
{
    return RP;
}

std::string Event::get_Phone()
{
    return Phone;
}

std::string Event::get_Comment(size_t i)
{
    if(i>=0 && i<Comment.size())
        return Comment.at(i);
    else
        return "No Value";
}

std::string Event::get_CommentTime(size_t i)
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

void Event::set_EventType(std::string NewEventType)
{
    std::string isnew = "none";
    std::string temp{};
    if(isnew == EventType)
    {
        temp = "Event Opend: " + NewEventType;
    }else
    {
        temp = EventType + " updated to " + NewEventType;
    }
    EventType = NewEventType;
    set_Comment(temp);
}

void Event::set_Comment(std::string NewComment)
{
    //gets date time group and stores it in date
    time_t t = time(0); 
    struct tm *now = localtime(&t);
    char date [80];
    strftime (date,80,"%m/%d/%y %H:%M:%Ss",now);

    //if this is the first comment set EventTime to date
    if(CommentTime.size() == 0)
        EventTime = date;

    //add the NewComment and date to vectors
    Comment.push_back(NewComment);
    CommentTime.push_back(date);
}

void Event::set_Location(std::string NewLocation)
{
    Location = NewLocation;
}

void Event::set_RP(std::string NewRP)
{
    RP = NewRP;
}

void Event::set_Phone(std::string NewPhone)
{
    Phone = NewPhone;
}

int Event::get_Events()
{
    return TotalEvents;
}