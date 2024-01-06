#ifndef EVENT_H
#define EVENT_H

#pragma once

#include <vector>
#include <chrono>
#include <QObject>

class Event
{
private:
     static int TotalEvents;

     QString EventType;
     QString EventTime;
     QString EventNumber;
     QString Location;
     QString RP;
     QString Phone;
     std::vector<QString> Comment;
     std::vector<QString> CommentTime;
public:
     //Constructors
     Event(QString EventType = "none");
     //Copy
     Event(const Event &source);
     //Deconstructor
     ~Event();
     //Methods
     QString get_EventType();
     QString get_EventTime();
     QString get_EventNumber();
     QString get_Location();
     QString get_RP();
     QString get_Phone();
     QString get_Comment(size_t i);
     QString get_CommentTime(size_t i);
     size_t get_CommentSize();

     void update_EventType(QString NewEventType, QString NewCommentTime);
     void set_EventType(QString NewEventType, QString NewCommentTime);
     void set_EventNumber(QString NewEventNumber);
     void set_Comment(QString NewComment, QString NewCommentTime);
     void set_Location(QString NewLocation);
     void set_RP(QString NewRP);
     void set_Phone(QString NewPhone);

     bool write();

     static int get_Events();
};

#endif // EVENT_H
