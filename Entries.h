#ifndef ENTRIES_H
#define ENTRIES_H

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
     bool add_Event(QString EventNumber, QString Event, QString Location, QString RP, QString Phone, QString NewCommentTime);

     bool set_Event(size_t Event, QString EventType, QString NewCommentTime);
     bool set_EventNumber(size_t Event, int &RawEventNumber);
     bool set_Comment(size_t Event, QString Comment, QString NewCommentTime);
     bool set_Location(size_t Event, QString NewLocation, QString NewCommentTime);
     bool set_RP(size_t Event, QString NewRP, QString NewCommentTime);
     bool set_Phone(size_t Event, QString NewPhone, QString NewCommentTime);

     QString get_EventType(size_t Event);
     QString get_EventNumberOpen(size_t Event);
     QString get_EventNumberClosed(size_t Event);
     QString get_Closed(size_t Event);
     QString get_EventTime(size_t Event);
     QString get_Location(size_t Event);
     QString get_RP(size_t Event);
     QString get_Phone(size_t Event);

     QString get_Comment(size_t Event, size_t Comment);
     QString get_CommentTime(size_t Event, size_t CommentTime);
     size_t get_CommentSize(size_t Event);

     size_t get_Open();
     size_t get_Closed();
     size_t get_Events();

     bool close_Event(size_t Selection, QString Disposition, QString NewCommentTime);
     bool reopen_Event(size_t Selection, QString Dispatcher, QString Reason, QString NewCommentTime);

     bool clear_Open();
     bool read(QString file);
     bool write(QString file, QString Dispatcher);

     Event *return_Event(size_t i);
};

#endif // ENTRIES_H
