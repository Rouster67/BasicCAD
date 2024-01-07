#ifndef ENTRIES_H_
#define ENTRIES_H_

#pragma once

#include "Event.h"
#include <fstream>

class Entries
{
private:

std::vector<Event> Open{};
std::vector<Event> Closed{};

public:
     //Constructors
     Entries();
     //Copy
     Entries(const Entries &source);
     //Deconstructor
     ~Entries();
     //Methods
     bool add_Event(std::string Event, std::string Location, std::string RP, std::string Phone);

     bool set_Event(size_t Event, std::string EventType);
     bool set_Comment(size_t Event, std::string Comment);
     bool set_Location(size_t Event, std::string NewLocation);
     bool set_RP(size_t Event, std::string NewRP);
     bool set_Phone(size_t Event, std::string NewPhone);

     std::string get_EventType(size_t Event);
     std::string get_Closed(size_t Event);
     std::string get_EventTime(size_t Event);
     std::string get_Location(size_t Event);
     std::string get_RP(size_t Event);
     std::string get_Phone(size_t Event);

     std::string get_Comment(size_t Event, size_t Comment);
     std::string get_CommentTime(size_t Event, size_t CommentTime);
     size_t get_CommentSize(size_t Event);

     size_t get_Open();
     size_t get_Closed();
     size_t get_Events();

     bool close_Event(size_t Selection, std::string Disposition);
     bool reopen_Event(size_t Selection, std::string Dispatcher, std::string Reason);

     bool read(std::string file);
     bool write(std::string file, std::string Dispatcher);

protected:

};

#endif