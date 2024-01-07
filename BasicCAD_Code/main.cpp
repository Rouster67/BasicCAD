#include "main.h"

int main ()
{   
    //gets date group
    time_t t = time(0); 
    struct tm *now = localtime(&t);
    char date [80];
    strftime (date,80,"%m-%d-%Y",now);
    
    //gets the shift and Dispatcher
    string shift = "days";
    const string _ = "_";
    string Dispatcher = "Bob";
    const string filetype = ".csv";

    //creates file name
    string fname = date + _ + shift + _ + Dispatcher + filetype;

    //creates path to the file
    string path ="EventLogs/";

    //combines file name and path
    string file = path + fname;
    
    Entries Events;

    //loop contaning the entire program
    for(;;)
    {
        clear();
        EntryList(Events);
        Menu();

        cout << "Enter selection: ";
        char MenuSelection{0};
        cin >> MenuSelection;

        switch(MenuSelection)
        {
            case '1':
            {
                cout << "Enter Event Type: ";
                string EventType;
                cin.ignore();
                getline(cin, EventType);

                cout << "Enter Location: ";
                string Location;
                getline(cin, Location);

                cout << "Enter RP: ";
                string RP;
                getline(cin, RP);

                cout << "Enter RP Phone: ";
                string Phone;
                getline(cin, Phone);

                if(!Events.add_Event(EventType, Location, RP, Phone))
                {
                    cout << "Failed\n"; system("pause");
                }

                cout << Events.get_EventType(Events.get_Open()-1) << " Initial Comment: ";
                string NewComment;
                getline(cin, NewComment);

                if(!Events.set_Comment(Events.get_Open()-1, NewComment))
                {
                    cout << "Failed\n"; system("pause");
                }

                break;
            }

            case '2':
            {
                if(Events.get_Open()<1)
                {
                    cout << "No Events to Edit" << endl;
                }else
                {
                    cout << "Enter Event to Edit: ";
                    size_t Selection{0};
                    cin >> Selection;
                    Selection-=1;
                    if(Selection>=0 && Selection<Events.get_Open())
                    {
                        cout << "Change " << Events.get_EventType(Selection) << " to: ";
                        string NewEventType;
                        cin.ignore();
                        getline(cin, NewEventType);

                        if(Events.set_Event(Selection, NewEventType))
                            cout << "Event Updated" << endl;
                        else
                            cout << "Unable to Update Event" << endl;
                    }
                }
                break;
            }

            case '3':
            {
                if(Events.get_Open()<1)
                {
                    cout << "No Events to Add Comments to" << endl;
                }else
                {
                    cout << "Enter Event to Add Comment: ";
                    size_t Selection{0};
                    cin >> Selection;
                    Selection-=1;
                    
                    cout << "Comment to add to " << Events.get_EventType(Selection) << ": ";
                    string NewComment;
                    cin.ignore();
                    getline(cin, NewComment);

                    Events.set_Comment(Selection, NewComment);
                }
                break;
            }

            case '4':
            {
                cout << "Which Event is completed: ";
                size_t Selection;
                cin >> Selection;
                Selection-=1;
                
                cout << "Disposition: ";

                string Disposition;
                cin.ignore();
                getline(cin, Disposition);
                
                Events.close_Event(Selection, Disposition);

                break;
            }

            case '5':
            {
                if(Events.write(file, Dispatcher))
                {
                    cout << "Save Successful" << endl;
                    system("pause");
                }else
                {
                    cout << "Unable to save" << endl;
                    system("pause");
                }

                break;
            }

            case '6':
            {
                cout << "Which do you want to reopen: ";
                size_t Selection;
                cin >> Selection;
                Selection-=1;
                
                cout << "Reason to reopen " << Events.get_Closed(Selection) << ": ";

                string Reason;
                cin.ignore();
                getline(cin, Reason);
                
                Events.reopen_Event(Selection, Dispatcher, Reason);

                break;
            }

            default:
            {
                cout << "Invalid selection" << endl;
                break;
            }
        }
    }
}

void EntryList(Entries &Events)
{
    if(Events.get_Open() > 0)
        {
            for(size_t i{0};i<Events.get_Open();++i)
            {
                cout << i+1 << ") " << Events.get_EventType(i) << " - " << Events.get_Location(i) << " - " << Events.get_RP(i) << " - " << Events.get_Phone(i) << " - " << Events.get_EventTime(i) << endl;
                cout << endl;
                for (size_t j{0};j<Events.get_CommentSize(i);++j)
                {
                    cout << "\t" << Events.get_CommentTime(i, j) << "\t" << Events.get_Comment(i, j) << endl;
                    cout << endl;
                }    
            }
        }else
        {
            cout << "No Enteries Avalible" << endl;
        }
}

void Menu()
{
    cout << setfill(' ');
    cout << setw(24) << " "; cout << "\tMenu" << endl;
    cout << setw(24) << " "; cout << "1) Add Event" << endl;
    cout << setw(24) << " "; cout << "2) Change Event Type" << endl;
    cout << setw(24) << " "; cout << "3) Add Comment" << endl;
    cout << setw(24) << " "; cout << "4) Disposition" << endl;
    cout << setw(24) << " "; cout << "5) Save" << endl;
    cout << setw(24) << " "; cout << "6) ReOpen" << endl;
}

void clear()
{
    system("cls");
}