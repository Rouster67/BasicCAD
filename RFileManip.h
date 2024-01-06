#ifndef RFILEMANIP_H
#define RFILEMANIP_H

#pragma once

#include <QFile>
#include <QDir>
#include <QString>
#include <QCoreApplication>
#include "Entries.h"

class RFile
{
private:  
    //used to lock system
    static bool locked;

    //file name to manip
    QString file;
    QString originalFile;

    //ram access
    Entries *entries;

    //path to all config files
    QString path{};

//lock
     //create two QStrings
          //file + -lock.csv
          //file + -locked.csv
     //set processing to true
     //create while loop to wait up to 30 seconds then attempt self correction
          //if file & lock.csv & !locked.csv
               //delete lock.csv
          //if !file & lock.csv & locked.csv
               //delete lock.csv
               //rename locked.csv to file
          //if
     //execute a read?
     //copy file into lock.csv
     //rename file to locked.csv
     //return

//unlock
     //create two QStrings
          //file + -lock.csv
          //file + -locked.csv
     //copy lock.csv into locked.csv
     //rename locked.csv back to just file
     //delete lock.csv
     //set processing to true
     //return

public:
     //Constructors
     RFile();
     //Copy
     RFile(const RFile &source);
     //Deconstructor
     ~RFile();
     //Methods
     bool setup(Entries *ptr_entries, QString filename);
     bool setfile(QString filename);
     bool setpath (QString pathname);
     bool lock();
     bool unlock();
     bool read();
     bool write();
     bool islocked();
     QString get();

protected:

};
#endif // RFILEMANIP_H
