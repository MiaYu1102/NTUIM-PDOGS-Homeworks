#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

// 全域變數
const int MAX_TOKENS = 50;

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
    Event(const Event &e);
    Event& operator=(const Event &e);
    void modify(Date date , Time begin , Time end , string name = "");
    virtual void print () const;
    bool isConflictWith(const Event& e) const;
    bool isLaterThan(const Event& other) const;
    friend class Calendar;
    virtual ~Event() {};
    // some other things that you want to add
};
Event::Event(Date date , Time begin , Time end , string name)
{
    this->date = date;
    this->begin = begin;
    this->end = end;
    this->name = name;
}
Event::Event(const Event &e)
{
    this->date = e.date;
    this->begin = e.begin;
    this->end = e.end;
    this->name = e.name;
}
Event& Event::operator=(const Event &e)
{
    this->date = e.date;
    this->begin = e.begin;
    this->end = e.end;
    this->name = e.name;
    return *this;
}
void Event::modify(Date date , Time begin , Time end , string name)
{
    this->date = date;
    this->begin = begin;
    this->end = end;
    this->name = name;
}
void Event::print() const {
    cout << this->name;
    cout << ": ";

    string date = to_string(this->date.year);
    string month = to_string(this->date.month);
    string day = to_string(this->date.day);
    if(month.length() == 1) {
        month = "0" + month;
    }
    if(day.length() == 1) {
        day = "0" + day;
    }
    cout << date << "/" << month << "/" << day;
    cout << ", ";

    string hour = to_string(this->begin.hour);
    string minute = to_string(this->begin.minute);
    if(hour.length() == 1) {
        hour = "0" + hour;
    }
    if(minute.length() == 1) {
        minute = "0" + minute;
    }
    cout << hour << ":" << minute;
    cout << ", ";

    hour = to_string(this->end.hour);
    minute = to_string(this->end.minute);
    if(hour.length() == 1) {
        hour = "0" + hour;
    }
    if(minute.length() == 1) {
        minute = "0" + minute;
    }
    cout << hour << ":" << minute;
    cout << "." << endl;
}
bool Event::isConflictWith(const Event& event) const {
    if(event.date.year != this->date.year || 
        event.date.month != this->date.month || 
        event.date.day != this->date.day) {
        return false;
    }
    int timeBegin = this->begin.hour * 60 + this->begin.minute;
    int timeEnd = this->end.hour * 60 + this->end.minute;
    int timeBegin_event = event.begin.hour * 60 + event.begin.minute;
    int timeEnd_event = event.end.hour * 60 + event.end.minute;
    if (timeBegin_event >= timeEnd || timeEnd_event <= timeBegin) {
        return false; 
    }

    return true;
}
bool Event::isLaterThan(const Event& other) const {
    if(this->date.year > other.date.year) {
        return true;
    } else if(this->date.year == other.date.year) {
        if(this->date.month > other.date.month) {
            return true;
        } else if(this->date.month == other.date.month) {
            if(this->date.day > other.date.day) {
                return true;
            } else if(this->date.day == other.date.day) {
                if(this->begin.hour > other.begin.hour) {
                    return true;
                } else if(this->begin.hour == other.begin.hour) {
                    if(this->begin.minute > other.begin.minute) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

// hw10-3-----------------------------------------------------------------
class AlertEvent : public Event 
{
private:
    int aheadAlertMinutes;
    // some other things that you want to add
public:
    AlertEvent(Date date, Time begin, Time end, string name, 
               int aheadAlertMinutes);
    int getAheadAlertMinutes() const; 
    void modify(Date date, Time begin, Time end, string name, 
                int aheadAlertMinutes);
    void print() const override;  
    // some other things that you want to add
};

AlertEvent::AlertEvent(Date date, Time begin, Time end, string name, int aheadAlertMinutes)
    : Event(date, begin, end, name), aheadAlertMinutes(aheadAlertMinutes) {}
int AlertEvent::getAheadAlertMinutes() const {
    return aheadAlertMinutes;
}
void AlertEvent::modify(Date date, Time begin, Time end, string name, int aheadAlertMinutes) {
    Event::modify(date, begin, end, name);
    this->aheadAlertMinutes = aheadAlertMinutes;
}
void AlertEvent::print() const {
    cout << this->name;
    cout << ": ";

    string date = to_string(this->date.year);
    string month = to_string(this->date.month);
    string day = to_string(this->date.day);
    if(month.length() == 1) {
        month = "0" + month;
    }
    if(day.length() == 1) {
        day = "0" + day;
    }
    cout << date << "/" << month << "/" << day;
    cout << ", ";

    string hour = to_string(this->begin.hour);
    string minute = to_string(this->begin.minute);
    if(hour.length() == 1) {
        hour = "0" + hour;
    }
    if(minute.length() == 1) {
        minute = "0" + minute;
    }
    cout << hour << ":" << minute;
    cout << ", ";

    hour = to_string(this->end.hour);
    minute = to_string(this->end.minute);
    if(hour.length() == 1) {
        hour = "0" + hour;
    }
    if(minute.length() == 1) {
        minute = "0" + minute;
    }
    cout << hour << ":" << minute;
    cout << ", " << aheadAlertMinutes << "." << endl;
}

class WholeDayEvent : public Event 
{
public:
    WholeDayEvent(Date date, string name);
    void modify(Date date , string name);
    void print() const override; 
    // some other things that you want to add
};

WholeDayEvent::WholeDayEvent(Date date, string name) : Event(date, {0, 0}, {23, 59}, name) {}
void WholeDayEvent::modify(Date date, string name) {
    Event::modify(date, {0, 0}, {23, 59}, name);
}
void WholeDayEvent::print() const {
    cout << this->name;
    cout << ": ";

    string date = to_string(this->date.year);
    string month = to_string(this->date.month);
    string day = to_string(this->date.day);
    if(month.length() == 1) {
        month = "0" + month;
    }
    if(day.length() == 1) {
        day = "0" + day;
    }
    cout << date << "/" << month << "/" << day;
    cout << ", ";

    cout << "whole day." << endl;
}
//------------------------------------------------------------------------
class Calendar
{
private:
    string ownerName;
    Event ** events;
    int eventCnt;
    static int eventCntMax;
    // some other things that you want to add
public:
    Calendar();
    Calendar(string ownerName);
    Calendar(const Calendar& c);
    Calendar& operator=(const Calendar& c);
    ~Calendar();

    void setOwnerName(string newOwnerName);
    string getOwnerName () const;
    int getEventCnt () const;

    bool addEvent(Date date , Time begin , Time end , string name);
    bool removeEvent(Date date , Time begin , string name);
    bool modifyEvent(Date date , Time begin , string name , Date newDate ,
    Time newBegin, Time newEnd , string newName);
    
    bool addAlertEvent(Date date , Time begin , Time end , string name , int aheadAlertMinutes);
    bool removeAlertEvent(Date date , Time begin , string name);
    bool modifyAlertEvent(Date date , Time begin , string name , Date newDate , Time newBegin , Time newEnd , string newName , int newAheadAlertMinutes);

    bool addWholeDayEvent(Date date , string name);
    bool removeWholeDayEvent(Date date , string name);
    bool modifyWholeDayEvent(Date date , string name , Date newDate , string newName);

    void expandEventCnt(int newEventCnt);

    void printEvent(Date date , Time begin , string name) const;
    void printCalendarOldToNew () const;

    static void setEventCntMax(int eventCntMax);
    static void setDefaultEventCntMax(int eventCntMax);
    // some other things that you want to add
};

int Calendar::eventCntMax = 0;
Calendar::Calendar() // Default constructor
{
    ownerName = "";
    events = new Event*[eventCntMax];
    eventCnt = 0;
}
Calendar::Calendar(string ownerName)
{
    this->ownerName = ownerName;
    events = new Event*[eventCntMax];
    eventCnt = 0;
}
Calendar::Calendar(const Calendar& c) // deep copy constructor
{
    ownerName = c.ownerName;
    eventCnt = c.eventCnt;
    events = new Event*[eventCntMax];
    if (events != nullptr) {
        for(int i = 0; i < eventCnt; i++)
        { 
            events[i] = new Event(*c.events[i]);
        }
    }
}
Calendar& Calendar::operator=(const Calendar& c) // deep copy assignment
{
    if (this == &c) {
        return *this;
    }
    ownerName = c.ownerName;
    eventCnt = c.eventCnt;
    for (int i = 0; i < eventCnt; i++) {
        delete events[i];
    }
    delete[] events;
    events = new Event*[eventCntMax];
    for (int i = 0; i < eventCnt; i++) {
        events[i] = new Event(*c.events[i]);
    }
    return *this;
}
Calendar::~Calendar() {
    if (events != nullptr) {
        for (int i = 0; i < eventCnt; i++) {
            if(events[i]) delete events[i];
        }
        delete[] events;
    }
}

void Calendar::setOwnerName(string newOwnerName) {
    ownerName = newOwnerName;
}
string Calendar::getOwnerName() const {
    return ownerName;
}
int Calendar::getEventCnt() const {
    return eventCnt;
}

bool Calendar::addEvent(Date date , Time begin , Time end , string name)
{
    if(eventCnt == eventCntMax)
    {
        return false;
    }
    Event* newEvent = new Event(date , begin , end , name);
    for(int i = 0; i < eventCnt; i++)
    {
        if(events[i]->isConflictWith(*newEvent))
        {
            delete newEvent;
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
    // Event* newEvent = new Event(newDate , newBegin , newEnd , newName);
                
    
    for(int i = 0; i < eventCnt; i++)
    {
        if(events[i]->date.year == date.year && events[i]->date.month == date.month && events[i]->date.day == date.day)
        {
            if(events[i]->begin.hour == begin.hour && events[i]->begin.minute == begin.minute)
            {
                if(events[i]->name == name)
                {
                    //保留原數值
                    Date originDate = events[i]->date;
                    Time originBegin = events[i]->begin;
                    Time originEnd = events[i]->end;
                    string originName = events[i]->name;

                    //修改
                    events[i]->modify(newDate , newBegin , newEnd , newName);
                    for(int j = 0; j < eventCnt; j++)
                    {
                        if(j == i)
                        {
                            continue;
                        }
                        if(events[j]->isConflictWith(*events[i]))
                        {
                            events[i]->modify(originDate , originBegin , originEnd , originName);
                            return false;
                        }
                    }
                    return true;
                }
            }
        }
    }
    return false;
}

bool Calendar::addAlertEvent(Date date , Time begin , Time end , string name , int aheadAlertMinutes)
{
    if(eventCnt == eventCntMax)
    {
        return false;
    }
    Event* newEvent = new AlertEvent(date , begin , end , name , aheadAlertMinutes);
    for(int i = 0; i < eventCnt; i++)
    {
        if(events[i]->isConflictWith(*newEvent))
        {
            delete newEvent;
            return false;
        }
    }
    events[eventCnt] = newEvent;
    eventCnt++;
    return true;
}
bool Calendar::removeAlertEvent(Date date , Time begin , string name)
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
bool Calendar::modifyAlertEvent(Date date , Time begin , string name , Date newDate , Time newBegin , Time newEnd , string newName , int newAheadAlertMinutes)
{
    // Event* newEvent = new AlertEvent(newDate , newBegin , newEnd , newName , newAheadAlertMinutes);
                
    
    for(int i = 0; i < eventCnt; i++)
    {
        if(events[i]->date.year == date.year && events[i]->date.month == date.month && events[i]->date.day == date.day)
        {
            if(events[i]->begin.hour == begin.hour && events[i]->begin.minute == begin.minute)
            {
                if(events[i]->name == name)
                {
                    //保留原數值
                    Date originDate = events[i]->date;
                    Time originBegin = events[i]->begin;
                    Time originEnd = events[i]->end;
                    string originName = events[i]->name;
                    int originAheadAlertMinutes = dynamic_cast<AlertEvent*>(events[i])->getAheadAlertMinutes();

                    //修改
                    dynamic_cast<AlertEvent*>(events[i])->modify(newDate , newBegin , newEnd , newName, newAheadAlertMinutes); //待修改
                    for(int j = 0; j < eventCnt; j++)
                    {
                        if(j == i)
                        {
                            continue;
                        }
                        if(events[j]->isConflictWith(*events[i]))
                        {
                            dynamic_cast<AlertEvent*>(events[i])->modify(originDate , originBegin , originEnd , originName, originAheadAlertMinutes); //待修改
                            return false;
                        }
                    }
                    return true;
                }
            }
        }
    }
    return false;
}

bool Calendar::addWholeDayEvent(Date date , string name)
{
    if(eventCnt == eventCntMax)
    {
        return false;
    }
    Event* newEvent = new WholeDayEvent(date , name);
    for(int i = 0; i < eventCnt; i++)
    {
        if(events[i]->isConflictWith(*newEvent))
        {
            delete newEvent;
            return false;
        }
    }
    events[eventCnt] = newEvent;
    eventCnt++;
    return true;
}
bool Calendar::removeWholeDayEvent(Date date , string name)
{
    for(int i = 0; i < eventCnt; i++)
    {
        if(events[i]->date.year == date.year && events[i]->date.month == date.month && events[i]->date.day == date.day)
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
    return false;
}
bool Calendar::modifyWholeDayEvent(Date date , string name , Date newDate , string newName)
{
    // Event* newEvent = new WholeDayEvent(newDate , newName);
                
    
    for(int i = 0; i < eventCnt; i++)
    {
        if(events[i]->date.year == date.year && events[i]->date.month == date.month && events[i]->date.day == date.day)
        {
            if(events[i]->name == name)
            {
                //保留原數值
                Date originDate = events[i]->date;
                string originName = events[i]->name;

                //修改
                dynamic_cast<WholeDayEvent*>(events[i])->modify(newDate , newName); //待修改
                for(int j = 0; j < eventCnt; j++)
                {
                    if(j == i)
                    {
                        continue;
                    }
                    if(events[j]->isConflictWith(*events[i]))
                    {
                        dynamic_cast<WholeDayEvent*>(events[i])->modify(originDate , originName); //待修改
                        return false;
                    }
                }
                return true;
            }
        }
    }
    return false;
}

void Calendar::expandEventCnt(int newEventCnt) {
        Event** newEvents = new Event*[newEventCnt];
        for (int i = 0; i < eventCnt; i++) {
            newEvents[i] = events[i];
        }
        delete[] events;
        events = newEvents;
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
    cout << "";
}
void sortEvent(Event** events, int eventCnt) {
    for (int i = 1; i < eventCnt; i++) {
        Event* key = events[i];
        int j = i - 1;
        while (j >= 0 && !key->isLaterThan(*events[j])) {
            events[j + 1] = events[j];
            j--;
        }
        events[j + 1] = key;
    }
}
void Calendar::printCalendarOldToNew() const
{
    sortEvent(events, eventCnt);
    for(int i = 0; i < eventCnt; i++)
    {
        events[i]->print();
    }
}
void Calendar::setEventCntMax(int eventCntMax) {
    Calendar::eventCntMax = eventCntMax;
}
void Calendar::setDefaultEventCntMax(int eventCntMax) {
    Calendar::eventCntMax = eventCntMax;
}





// function---------------------------------------------------------------
bool isUserExist(Calendar* calendars, int user_cnt, string ownerName);
void splitString(const string& str, string* result);
void classifyByType(string* tokens, Calendar* calendars, int user_cnt);
void expandArray(Calendar*& calendars, int& capacity);


Date strToDate(string date_str);
Time strToTime(string time_str);

string queryModfiy(string query);
void queryPrint(string query_user, int user_cnt, Calendar* calendars);

bool isLeapYear(int year);
bool checkDateFormat(Date date);
bool checkTimeFormat(Time time);
bool checkBeginEndTime(Time begin, Time end);

int main(){
    int n; cin>>n;
    int event_cnt_limit; cin>>event_cnt_limit;
    Calendar::setEventCntMax(event_cnt_limit);

    // 創建calender動態陣列
    int capacity = 1000; // Initial capacity
    int user_cnt = 0;   // Current number of users
    Calendar* calendars = new Calendar[capacity];
    if (cin.peek() == '\n') {
        cin.ignore(); // 確保忽略換行符
    }
    
    // 處理n筆操作
    for(int i=0;i<n;i++)
    {
        //讀取操作指令
        string operation;
        
        getline(cin, operation);
        
        //分割字串
        string tokens[MAX_TOKENS];
        splitString(operation, tokens);


       //分類操作類型
        if(tokens[0]=="CC" && !isUserExist(calendars, user_cnt, tokens[1])) // create calender
        {    
            string ownerName = tokens[1];
            // 擴充動態陣列
            if (user_cnt >= capacity) {
                expandArray(calendars, capacity);
            }
            // 塞入陣列
            calendars[user_cnt] = Calendar(ownerName);
            user_cnt++;
        }
        else if(tokens[0]=="EX") // expand event count limit
        {
            //格式: EX 5
            int add_event_cnt = stoi(tokens[1]);
            if(add_event_cnt <= 0){
                cerr << "Invalid number." << endl;
            }
            else{
                event_cnt_limit += add_event_cnt;
                Calendar::setEventCntMax(event_cnt_limit);
                for (int j = 0; j < user_cnt; j++) {
                    calendars[j].expandEventCnt(event_cnt_limit);
                }
            }
            
        }
        else classifyByType(tokens, calendars, user_cnt);
    }

    // 處理詢問
    string query;
    getline(cin, query);
    string query_user = queryModfiy(query);
    
    queryPrint(query_user, user_cnt, calendars);
    
    delete[] calendars;
    return 0;
}


// function
bool isUserExist(Calendar* calendars, int user_cnt, string ownerName) {
    for(int i=0;i<user_cnt;i++){
        if(calendars[i].getOwnerName() == ownerName){
            return true;
        }
    }
    return false;
}

void splitString(const string& str, string* result) {
    istringstream ss(str);
    string token;
    bool inQuotes = false; // 判斷是否處於雙引號內
    string quotedContent;
    int resultSize = 0;
    
    while (ss >> token) { // 不忽略空白
        if (token.front() == '"' && token.back() == '"' && token.size()!=1 && !inQuotes) {
            result[resultSize++] = token.substr(1, token.size() - 2);
        }
        else if (token.front() == '"' && !inQuotes) { // 遇到開頭的雙引號
            inQuotes = true;
            quotedContent = token.substr(1); // 移除開頭雙引號
        }
        else if (token.back() == '"' && inQuotes) { // 遇到結尾的雙引號
            inQuotes = false;
            quotedContent += " " + token.substr(0, token.size() - 1); // 加入結尾
            if (resultSize < MAX_TOKENS) { // 使用全域變數作為限制
                result[resultSize++] = quotedContent; // 將完整內容加入結果
                quotedContent = "";
            }
        }
        else if (inQuotes) { // 處於雙引號內
            quotedContent += " " + token;
        } 
        else { // 普通空格分隔部分
            if (resultSize < MAX_TOKENS) { // 使用全域變數作為限制
                result[resultSize++] = token;
            }
        }
    }
}

void classifyByType(string* tokens, Calendar* calendars, int user_cnt) {
    //判斷操作類型
    if(tokens[0]=="AE") // add event
    {  
        //格式: AE "Bob" 2024/11/13 13:00 15:00 "PD Quiz"
        
        // set token
        string owner_name = tokens[1];
        string date_str = tokens[2];
        string begin_str = tokens[3];
        string end_str = tokens[4];
        string event_name = tokens[5];

        // transform format
        Date date = strToDate(date_str);
        Time begin = strToTime(begin_str);
        Time end = strToTime(end_str); 

        // check reasonability
        if(!checkDateFormat(date) || !checkTimeFormat(begin) || !checkTimeFormat(end)){
            cerr << "Invalid date or time." << endl;
            return;
        }
        if(!isUserExist(calendars, user_cnt, owner_name)){
            cerr << "User not found." << endl;
            return;
        }
        if(!checkBeginEndTime(begin, end)){
            cerr << "Invalid time." << endl;
            return;
        }
        // add event
        for(int i=0;i<user_cnt;i++){
            if(calendars[i].getOwnerName() == owner_name){
                bool isAdd = calendars[i].addEvent(date, begin, end, event_name);
                if(isAdd){
                    return;
                }
                else{
                    cerr << "Time conflict." << endl;
                    return;
                }
            }
        }

    }
    else if(tokens[0]=="ME") // modify event
    {
        //格式: ME "Bob" "PD Quiz" 2024/11/13 13:00 2024/11/13 16:00 18:00 "PD Quiz"
        
        // set token
        string owner_name = tokens[1];
        string origin_event_name = tokens[2];
        string origin_date_str = tokens[3];
        string origin_begin_str = tokens[4];
        string new_date_str = tokens[5];
        string new_begin_str = tokens[6];
        string new_end_str = tokens[7];
        string new_event_name = tokens[8];

        // transform format
        Date origin_date = strToDate(origin_date_str);
        Time origin_begin = strToTime(origin_begin_str);
        Time new_begin = strToTime(new_begin_str);
        Time new_end = strToTime(new_end_str);
        Date new_date = strToDate(new_date_str);

        // check reasonability
        if(!checkDateFormat(origin_date) || !checkTimeFormat(origin_begin) || !checkTimeFormat(new_begin) || !checkTimeFormat(new_end) || !checkDateFormat(new_date)){
            cerr << "Invalid date or time." << endl;
            return;
        }
        if(!isUserExist(calendars, user_cnt, owner_name)){
            cerr << "User not found." << endl;
            return;
        }
        if(!checkBeginEndTime(new_begin, new_end)){
            cerr << "Invalid time." << endl;
            return;
        }

        // modify event
        for(int i=0;i<user_cnt;i++){
            if(calendars[i].getOwnerName() == owner_name){
                bool isModify = calendars[i].modifyEvent(origin_date, origin_begin, origin_event_name, new_date, new_begin, new_end, new_event_name);
                if(isModify){
                    return;
                }
            }
        }

    }
    else if(tokens[0]=="RE") // remove event
    {
        //格式: RE "Mary" "Calculus" 2024/11/14 15:00
        
        // set token
        string owner_name = tokens[1];
        string event_name = tokens[2];
        string date_str = tokens[3];
        string begin_str = tokens[4];

        // transform format
        Date date = strToDate(date_str);
        Time begin = strToTime(begin_str);

        // check reasonability
        if(!checkDateFormat(date) || !checkTimeFormat(begin)){
            cerr << "Invalid date or time." << endl;
            return;
        }
        if(!isUserExist(calendars, user_cnt, owner_name)){
            cerr << "User not found." << endl;
            return;
        }

        // remove event
        for(int i=0;i<user_cnt;i++){
            if(calendars[i].getOwnerName() == owner_name){
                bool isRemove = calendars[i].removeEvent(date, begin, event_name);
                if(isRemove){
                    return;
                }
            }
        }
        
    }
    else if(tokens[0]=="AAE") // add alert event
    {
        //格式: AAE "Jane" 2024/06/23 09:00 11:00 "Meeting" 30

        // set token
        string owner_name = tokens[1];
        string date_str = tokens[2];
        string begin_str = tokens[3];
        string end_str = tokens[4];
        string event_name = tokens[5];
        string ahead_alert_minutes_str = tokens[6];

        // transform format
        Date date = strToDate(date_str);
        Time begin = strToTime(begin_str);
        Time end = strToTime(end_str);
        int alert_minutes = stoi(ahead_alert_minutes_str);

        // check reasonability
        if(!checkDateFormat(date) || !checkTimeFormat(begin) || !checkTimeFormat(end)){
            cerr << "Invalid date or time." << endl;
            return;
        }
        if(!isUserExist(calendars, user_cnt, owner_name)){
            cerr << "User not found." << endl;
            return;
        }
        if(!checkBeginEndTime(begin, end)){
            cerr << "Invalid time." << endl;
            return;
        }

        // add alert event
        for(int i=0;i<user_cnt;i++){
            if(calendars[i].getOwnerName() == owner_name){
                bool isAdd = calendars[i].addAlertEvent(date, begin, end, event_name, alert_minutes);
                if(isAdd){
                    return;
                }
                else{
                    cerr << "Time conflict." << endl;
                    return;
                }
            }
        }

    }
    else if(tokens[0]=="RAE") // remove alert event
    {
        //格式: RAE "Jane" "Yoga Class" 2024/06/20 08:00

        // set token
        string owner_name = tokens[1];
        string event_name = tokens[2];
        string date_str = tokens[3];
        string begin_str = tokens[4];

        // transform format
        Date date = strToDate(date_str);
        Time begin = strToTime(begin_str);

        // check reasonability
        if(!checkDateFormat(date) || !checkTimeFormat(begin)){
            cerr << "Invalid date or time." << endl;
            return;
        }
        if(!isUserExist(calendars, user_cnt, owner_name)){
            cerr << "User not found." << endl;
            return;
        }

        // remove alert event
        for(int i=0;i<user_cnt;i++){
            if(calendars[i].getOwnerName() == owner_name){
                bool isRemove = calendars[i].removeAlertEvent(date, begin, event_name);
                if(isRemove){
                    return;
                }
            }
        }


    }
    else if(tokens[0]=="MAE") // modify alert event
    {
        //格式: MAE "Jane" "Meeting" 2024/06/23 09:00 2024/06/23 09:00 11:00 "Meeting" 20

        // set token
        string owner_name = tokens[1];
        string origin_event_name = tokens[2];
        string origin_date_str = tokens[3];
        string origin_begin_str = tokens[4];
        string new_date_str = tokens[5];
        string new_begin_str = tokens[6];
        string new_end_str = tokens[7];
        string new_event_name = tokens[8];
        string new_ahead_alert_minutes_str = tokens[9];

        // transform format
        Date origin_date = strToDate(origin_date_str);
        Time origin_begin = strToTime(origin_begin_str);
        Time new_begin = strToTime(new_begin_str);
        Time new_end = strToTime(new_end_str);
        Date new_date = strToDate(new_date_str);
        int new_ahead_alert_minutes = stoi(new_ahead_alert_minutes_str);

        // check reasonability
        if(!checkDateFormat(origin_date) || !checkTimeFormat(origin_begin) || !checkTimeFormat(new_begin) || !checkTimeFormat(new_end) || !checkDateFormat(new_date)){
            cerr << "Invalid date or time." << endl;
            return;
        }
        if(!isUserExist(calendars, user_cnt, owner_name)){
            cerr << "User not found." << endl;
            return;
        }
        if(!checkBeginEndTime(new_begin, new_end)){
            cerr << "Invalid time." << endl;
            return;
        }

        // modify alert event
        for(int i=0;i<user_cnt;i++){
            if(calendars[i].getOwnerName() == owner_name){
                bool isModify = calendars[i].modifyAlertEvent(origin_date, origin_begin, origin_event_name, new_date, new_begin, new_end, new_event_name, new_ahead_alert_minutes);
                if(isModify){
                    return;
                }
            }
        }


    }
    else if(tokens[0]=="AWE") // add whole day event
    {
        //格式: AWE "Jane" 2024/06/21 "Summer Solstice Festival"

        // set token
        string owner_name = tokens[1];
        string date_str = tokens[2];
        string event_name = tokens[3];

        // transform format
        Date date = strToDate(date_str);

        // check reasonability
        if(!checkDateFormat(date)){
            cerr << "Invalid date." << endl;
            return;
        }
        if(!isUserExist(calendars, user_cnt, owner_name)){
            cerr << "User not found." << endl;
            return;
        }

        // add whole day event
        for(int i=0;i<user_cnt;i++){
            if(calendars[i].getOwnerName() == owner_name){
                bool isAdd = calendars[i].addWholeDayEvent(date, event_name);
                if(isAdd){
                    return;
                }
                else{
                    cerr << "Time conflict." << endl;
                    return;
                }
            }
        }

    }
    else if(tokens[0]=="RWE") // remove whole day event
    {
        //格式: RWE "Jane" "Summer Solstice Festival" 2024/06/21

        // set token
        string owner_name = tokens[1];
        string event_name = tokens[2];
        string date_str = tokens[3];

        // transform format
        Date date = strToDate(date_str);

        // check reasonability
        if(!checkDateFormat(date)){
            cerr << "Invalid date." << endl;
            return;
        }
        if(!isUserExist(calendars, user_cnt, owner_name)){
            cerr << "User not found." << endl;
            return;
        }

        // remove whole day event
        for(int i=0;i<user_cnt;i++){
            if(calendars[i].getOwnerName() == owner_name){
                bool isRemove = calendars[i].removeWholeDayEvent(date, event_name);
                if(isRemove){
                    return;
                }
            }
        }
    }
    else if(tokens[0]=="MWE") // modify whole day event
    {
        //格式: MWE "Jane" "Christmas Eve" 2024/12/24 2024/12/34 "Christmas Eve"

        // set token
        string owner_name = tokens[1];
        string origin_event_name = tokens[2];
        string origin_date_str = tokens[3];
        string new_date_str = tokens[4];
        string new_event_name = tokens[5];
        
        // transform format
        Date origin_date = strToDate(origin_date_str);
        Date new_date = strToDate(new_date_str);

        // check reasonability
        if(!checkDateFormat(origin_date) || !checkDateFormat(new_date)){
            cerr << "Invalid date." << endl;
            return;
        }
        if(!isUserExist(calendars, user_cnt, owner_name)){
            cerr << "User not found." << endl;
            return;
        }

        // modify whole day event
        for(int i=0;i<user_cnt;i++){
            if(calendars[i].getOwnerName() == owner_name){
                bool isModify = calendars[i].modifyWholeDayEvent(origin_date, origin_event_name, new_date, new_event_name);
                if(isModify){
                    return;
                }
            }
        }

    }
    
}  
void expandArray(Calendar*& calendars, int& capacity) {
    int new_capacity = capacity * 2;
    Calendar* new_array = new Calendar[new_capacity];

    for (int i = 0; i < capacity; i++) {
        new_array[i] = calendars[i];
    }

    delete[] calendars;
    calendars = new_array;
    capacity = new_capacity;
}

Date strToDate(string date_str) {
    //格式: 2024/11/13
    Date date;
    date.year = stoi(date_str.substr(0, 4));
    date.month = stoi(date_str.substr(5, 2));
    date.day = stoi(date_str.substr(8, 2));
    return date;
}
Time strToTime(string time_str) {
    //格式: 13:00
    Time time;
    time.hour = stoi(time_str.substr(0, 2));
    time.minute = stoi(time_str.substr(3, 2));
    return time;
}

string queryModfiy(string query) {
    //格式: Q "Bob"
    cerr << "\033[32m" << "有執行"  <<"\033[0m" << endl;
    string query_user = query.substr(3);
    query_user.pop_back();

    cerr << "\033[32m" << query_user <<"\033[0m" << endl;
    return query_user;
}
void queryPrint(string query_user, int user_cnt, Calendar* calendars) {
    //格式: 
    // Bob
    // PD Quiz: 2024/11/13, 16:00, 18:00.
    // Concert: 2024/11/20, 19:00, 20:00.
    cout << query_user << endl;
    for(int i=0;i<user_cnt;i++){
        if(calendars[i].getOwnerName() == query_user){
            calendars[i].printCalendarOldToNew();
        }
    }
}

bool isLeapYear(int year) {
    if (year % 4 != 0) return false;
    if (year % 100 != 0) return true;
    if (year % 400 != 0) return false;
    return true;
}
bool checkDateFormat(Date date) {
    // year
    if(date.year < 1900){
        return false;
    }

    // month
    if(date.month < 1 || date.month > 12){
        return false;
    }

    //day
    if(date.day < 1 || date.day > 31){
        return false;
    }
    else if(date.month == 2){
        if (isLeapYear(date.year)) {
            return date.day <= 29; // 閏年 2 月最多 29 天
        } else {
            return date.day <= 28; // 平年 2 月最多 28 天
        }
    }
    else if(date.month == 4 || date.month == 6 || date.month == 9 || date.month == 11){
        if(date.day > 30){
            return false;
        }
    }

    return true;
}
bool checkTimeFormat(Time time) {
    if(time.hour == 24 && time.minute == 0) {
        return true;
    }
    if(time.hour < 0 || time.hour > 23) {
        return false;
    }
    if(time.minute < 0 || time.minute > 59) {
        return false;
    }
    return true;
}

bool checkBeginEndTime(Time begin, Time end) {
    if (begin.hour > end.hour) {
        return false;
    } else if (begin.hour == end.hour) {
        if (begin.minute >= end.minute) {
            return false;
        }
    }
    return true;
}
