#include <iostream>
#include <iomanip>
#include <fstream>
#include "Entries.h"
using namespace std;

void EntryList(Entries &Events);
void Menu();
void clear();

/*
add event numbers to calls

create startup and close function in main

create an autosave feature

create a load function to load csv files

create a move function to move the path

create function to create a folder when folder inst found

implement a location vector in the event class

have files auto generate at midnight each day and carry over all events still open

create officers class

officers will have a name and callsign assigned and stored into a vector class

create an accounts class.

define a hardcoded admin object from the account class

give admin ability to create new accounts

give admin ability to give account admin privlages

give admin ability to change usernames and passwords at will

give regular account ability to change their own username and password at will

encrypt passwords

give admin ability to change program. Example: ability to change path.

implement git repository

implement Officers and callsigns

make callsigns editable by admins

make officers editable by dispatchers

Create a file that is used to store cross system variable data

in cross system variable folder think of ways to allow them to talk to eachother
    -have a bool that is always false. when a program is writing to a shared folder it will first change this to true. then back to false when done writing.

allow admin to change all shortcut codes

begin constructing UI

create sub menus for various tasks. Examples: New event, open closed event

implement text prediction
*/