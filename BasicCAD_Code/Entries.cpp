#include "Entries.h"

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
bool Entries::add_Event(std::string EventType, std::string Location, std::string RP, std::string Phone)
{
    Event NewEvent;
    NewEvent.set_EventType(EventType);
    NewEvent.set_Location(Location);
    NewEvent.set_RP(RP);
    NewEvent.set_Phone(Phone);
    Open.push_back(NewEvent);
    bool temp = true;

    if((Open.at(Open.size()-1)).get_EventType() != EventType)
        temp = false;
    if((Open.at(Open.size()-1)).get_Location() != Location)
        temp = false;

    return temp;
}

bool Entries::set_Event(size_t Event, std::string EventType)
{
    if(Open.size()>=0 && Event>=0 && Event<Open.size())
    {
        (Open.at(Event)).set_EventType(EventType);
        return true;
    }else
        return false;
}

bool Entries::set_Comment(size_t Event, std::string Comment)
{
    if(Event>=0 && Event<Open.size())
    {
        (Open.at(Event)).set_Comment(Comment);
        return true;
    }else
        return false;
}

bool Entries::set_Location(size_t Event, std::string NewLocation)
{
    if(Event>=0 && Event<Open.size())
    {
        (Open.at(Event)).set_Comment(NewLocation);
        return true;
    }else
        return false;
}

bool Entries::set_RP(size_t Event, std::string NewRP)
{
    if(Event>=0 && Event<Open.size())
    {
        (Open.at(Event)).set_Comment(NewRP);
        return true;
    }else
        return false;
}

bool Entries::set_Phone(size_t Event, std::string NewPhone)
{
    if(Event>=0 && Event<Open.size())
    {
        (Open.at(Event)).set_Comment(NewPhone);
        return true;
    }else
        return false;
}

std::string Entries::get_EventType(size_t Event)
{
    return (Open.at(Event)).get_EventType();
}

std::string Entries::get_Closed(size_t Event)
{
    return (Closed.at(Event)).get_EventType();
}

std::string Entries::get_EventTime(size_t Event)
{
    return (Open.at(Event)).get_EventTime();
}

std::string Entries::get_Location(size_t Event)
{
    return (Open.at(Event)).get_Location();
}

std::string Entries::get_RP(size_t Event)
{
    return (Open.at(Event)).get_RP();
}

std::string Entries::get_Phone(size_t Event)
{
    return (Open.at(Event)).get_Phone();
}

std::string Entries::get_Comment(size_t Event, size_t Comment)
{
    return (Open.at(Event)).get_Comment(Comment);
}

std::string Entries::get_CommentTime(size_t Event, size_t CommentTime)
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

bool Entries::close_Event(size_t Selection, std::string Disposition)
{
    if(Selection>=0 && Selection<Open.size())
    {
        std::string temp = "All Officers clear ";
        Disposition = temp + Disposition;

        (Open.at(Selection)).set_Comment(Disposition);

        Closed.push_back(Open.at(Selection));
        Open.erase(Open.begin()+Selection);

        return true;
    }else
        return false;
}

bool Entries::reopen_Event(size_t Selection, std::string Dispatcher, std::string Reason)
{
    if(Selection>=0 && Selection<Closed.size())
    {
        Reason = "Event opened by " + Dispatcher + ". Reason: " + Reason;
        (Closed.at(Selection)).set_Comment(Reason);
        Open.push_back(Closed.at(Selection));
        Closed.erase(Closed.begin()+Selection);

        return true;
    }else
        return false;
}

bool Entries::read(std::string file)//needs code
{

    return false;
}

bool Entries::write(std::string file, std::string Dispatcher)
{
    if(Closed.size()>0 || Open.size()>0)
    {
        std::ofstream InFile;
        InFile.open (file);
        InFile << "Events: , " << get_Events() << " , Closed: " << get_Closed() << " , Open: " << get_Open() << "\n";
        InFile << "Timestamp , Call Type , Comment , Location , RP , Phone , Dispatcher\n";
        if(Closed.size()>0)
        {
            for(size_t i{0};i<Closed.size();++i)
            {
                InFile << (Closed.at(i)).get_EventTime()
                       << " , " << (Closed.at(i)).get_EventType()
                       << " , "
                       << " , " << get_Location(i)
                       << " , " << (Closed.at(i)).get_RP()
                       << " , " << (Closed.at(i)).get_Phone() << "\n";

                for (size_t j{0};j<(Closed.at(i)).get_CommentSize();++j)
                {
                    InFile << (Closed.at(i)).get_CommentTime(j)
                           << " , , " << (Closed.at(i)).get_Comment(j) 
                           << " , , ,  , " << Dispatcher << std::endl;
                }
                InFile << "\n";
            }
        }
        if(Open.size()>0)
        {
            InFile << "\nEvents left open:\n";
            for(size_t i{0};i<Open.size();++i)
            {
                InFile << (Open.at(i)).get_EventTime()
                       << " , " << (Open.at(i)).get_EventType()
                       << " , "
                       << " , " << (Open.at(i)).get_Location()
                       << " , " << (Open.at(i)).get_RP()
                       << " , " << (Open.at(i)).get_Phone() << "\n";
                for (size_t j{0};j<(Open.at(i)).get_CommentSize();++j)
                {
                    InFile << (Open.at(i)).get_CommentTime(j)
                           << ", ," << (Open.at(i)).get_Comment(j)
                           << " , , ,  , " << Dispatcher << std::endl;
                }
                InFile << " , , This Event was left open\n"; 
            }
        }
        InFile.close();
        return true;
    }else
        return false;
}