#include<bits/stdc++.h> 
using namespace std;   

/*
Topic: calander application

*/
struct Date
{
    int year;
    int month;
    int day;
};
struct Time
{
    int hour;
    int minute;
};
class Event
{
protected:
    Date date;
    Time begin;
    Time end;
    string name;
    // some other things that you want to add
public:
    Event(Date date , Time begin , Time end , string name = "");
    void modify(Date date , Time begin , Time end , string name = "");
    void print () const;
    bool isConflictWith(const Event& e) const;
    // some other things that you want to add
};
Event::Event(Date date , Time begin , Time end , string name)
{
    this->date = date;
    this->begin = begin;
    this->end = end;
    this->name = name;
}
void Event::modify(Date date , Time begin , Time end , string name)
{
    this->date = date;
    this->begin = begin;
    this->end = end;
    this->name = name;
}
void Event::print() const
{
    cout << "Event: " << name << endl;
    cout << "Date: " << date.year << "/" << date.month << "/" << date.day << endl;
    cout << "Time: " << begin.hour << ":" << begin.minute << " - " << end.hour << ":" << end.minute << endl;
}
bool Event::isConflictWith(const Event& e) const
{
    if(date.year == e.date.year && date.month == e.date.month && date.day == e.date.day)
    {
        if(begin.hour < e.end.hour && end.hour > e.begin.hour)
        {
            return true;
        }
    }
    return false;
}

class Calendar
{
private:
    string ownerName;
    Event ** events;
    int eventCnt;
    static int eventCntMax;
    // some other things that you want to add
public:
    Calendar(string ownerName);
    Calendar(const Calendar& c);
    ~Calendar ();
    void setOwnerName(string newOwnerName);
    string getOwnerName () const;
    int getEventCnt () const;
    bool addEvent(Date date , Time begin , Time end , string name);
    bool removeEvent(Date date , Time begin , string name);
    bool modifyEvent(Date date , Time begin , string name , Date newDate ,
    Time newBegin , Time newEnd , string newName);
    void printEvent(Date date , Time begin , string name) const;
    void printCalendarOldToNew () const;
    static void setEventCntMax(int eventCntMax);
    // some other things that you want to add
};
int Calendar::eventCntMax = 100;
Calendar::Calendar(string ownerName)
{
    this->ownerName = ownerName;
    events = new Event*[eventCntMax];
    eventCnt = 0;
}
Calendar::Calendar(const Calendar& c)
{
    ownerName = c.ownerName;
    eventCnt = c.eventCnt;
    events = new Event*[eventCntMax];
    for(int i = 0; i < eventCnt; i++)
    {
        events[i] = c.events[i];
    }
}
Calendar::~Calendar()
{
    delete[] events;
}
void Calendar::setOwnerName(string newOwnerName)
{
    ownerName = newOwnerName;
}
string Calendar::getOwnerName() const
{
    return ownerName;
}
int Calendar::getEventCnt() const
{
    return eventCnt;
}
bool Calendar::addEvent(Date date , Time begin , Time end , string name)
{
    if(eventCnt == eventCntMax)
    {
        return false;
    }
    Event * newEvent = new Event(date , begin , end , name);
    for(int i = 0; i < eventCnt; i++)
    {
        if(events[i]->isConflictWith(*newEvent))
        {
            return false;
        }
    }
    events[eventCnt] = newEvent;
    eventCnt++;
    return true;
}
bool Calendar::removeEvent(Date date , Time begin , string name)
{
    for(int i = 0; i < eventCnt; i++)
    {
        if(events[i]->date.year == date.year && events[i]->date.month == date.month && events[i]->date.day == date.day)
        {
            if(events[i]->begin.hour == begin.hour && events[i]->begin.minute == begin.minute)
            {
                if(events[i]->name == name)
                {
                    delete events[i];
                    for(int j = i; j < eventCnt - 1; j++)
                    {
                        events[j] = events[j + 1];
                    }
                    eventCnt--;
                    return true;
                }
            }
        }
    }
    return false;
}
bool Calendar::modifyEvent(Date date , Time begin , string name , Date newDate , Time newBegin , Time newEnd , string newName)
{
    for(int i = 0; i < eventCnt; i++)
    {
        if(events[i]->date.year == date.year && events[i]->date.month == date.month && events[i]->date.day == date.day)
        {
            if(events[i]->begin.hour == begin.hour && events[i]->begin.minute == begin.minute)
            {
                if(events[i]->name == name)
                {
                    events[i]->modify(newDate , newBegin , newEnd , newName);
                    return true;
                }
            }
        }
    }
    return false;
}
void Calendar::printEvent(Date date , Time begin , string name) const
{
    for(int i = 0; i < eventCnt; i++)
    {
        if(events[i]->date.year == date.year && events[i]->date.month == date.month && events[i]->date.day == date.day)
        {
            if(events[i]->begin.hour == begin.hour && events[i]->begin.minute == begin.minute)
            {
                if(events[i]->name == name)
                {
                    events[i]->print();
                    return;
                }
            }
        }
    }
    cout << "Event not found." << endl;
}
void Calendar::printCalendarOldToNew() const
{
    for(int i = 0; i < eventCnt; i++)
    {
        events[i]->print();
    }
}
void Calendar::setEventCntMax(int eventCntMax)
{
    Calendar::eventCntMax = eventCntMax;
}

int main(){
    /*
    Input Format:
        AE "Bob" 2024/11/13 13:00 15:00 "PD Quiz"

    */
   int n; cin>>n;
   int calender_upper_limit = 0;
   for(int i=0;i<n;i++)
   {
       string operation; //operation = "Bob" 2024/11/13 13:00 15:00 "PD Quiz"
       cin>>operation;
       //split string
       stringstream ss(operation);
       string ownerName;
       
        


   }
    return 0;
}