#ifndef EVENT_H_
#define EVENT_H_

#pragma once

#include <vector>
#include <string>
#include <chrono>

class Event
{
private:
     static int TotalEvents;

     std::string EventType;
     std::string EventTime;
     std::string Location;
     std::string RP;
     std::string Phone;
     std::vector<std::string> Comment;
     std::vector<std::string> CommentTime;
public:
     //Constructors
     Event(std::string EventType = "none");
     //Copy
     Event(const Event &source);
     //Deconstructor
     ~Event();
     //Methods
     std::string get_EventType();
     std::string get_EventTime();
     std::string get_Location();
     std::string get_RP();
     std::string get_Phone();
     std::string get_Comment(size_t i);
     std::string get_CommentTime(size_t i);
     size_t get_CommentSize();

     void set_EventType(std::string NewEventType);
     void set_Comment(std::string NewComment);
     void set_Location(std::string NewLocation);
     void set_RP(std::string NewRP);
     void set_Phone(std::string NewPhone);

     bool write();

     static int get_Events();
protected:

};

#endif