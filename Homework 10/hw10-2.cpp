#include<bits/stdc++.h> 
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
    if(timeBegin_event >= timeEnd || timeEnd_event <= timeBegin) {
        return false;
    }

    return true;
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
    Calendar();
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

int Calendar::eventCntMax = 100;  //待修改

// Default constructor
Calendar::Calendar()
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
Calendar::Calendar(const Calendar& c) //待修改
{
    ownerName = c.ownerName;
    eventCnt = c.eventCnt;
    events = new Event*[eventCntMax];
    for(int i = 0; i < eventCnt; i++)
    {
        events[i] = c.events[i];
    }
}
Calendar::~Calendar() {
    if (events != nullptr) {
        for (int i = 0; i < eventCnt; i++) {
            delete events[i];
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
void Calendar::setEventCntMax(int eventCntMax) {
    Calendar::eventCntMax = eventCntMax;
}

//------------------以下是手打的內容--------------------------

// function
bool isUserExist(Calendar* calenders, int user_cnt, string ownerName);
void splitString(const string& str, string* result);
void classifyByType(string* tokens, Calendar* calenders, int user_cnt);
void expandArray(Calendar*& calenders, int& capacity);

Date strToDate(string date_str);
Time strToTime(string time_str);

string queryModfiy(string query);
void queryPrint(string query_user, int user_cnt, Calendar* calenders);

bool isLeapYear(int year);
bool checkDateFormat(Date date);
bool checkTimeFormat(Time time);

int main(){
    int n; cin>>n;
    int event_cnt_limit; cin>>event_cnt_limit;

    // 創建calender動態陣列
    int capacity = 100; // Initial capacity
    int user_cnt = 0;   // Current number of users
    Calendar* calenders = new Calendar[capacity];

    // 處理n筆操作
    for(int i=0;i<n;i++)
    {
       //讀取操作指令
       string operation;
       cin>>operation;
       
       //分割字串
       string tokens[MAX_TOKENS];
       splitString(operation, tokens);

       //分類操作類型
       if(tokens[0]=="CC" && !isUserExist(calenders, user_cnt, tokens[1])) // create calender
       {    
            string ownerName = tokens[1];
            // 擴充動態陣列
            if (user_cnt >= capacity) {
                    expandArray(calenders, capacity);
            }
            // 塞入陣列
            calenders[user_cnt] = Calendar(ownerName);
            user_cnt++;
       }
       else if(tokens[0]=="EX") // expand event count limit
       {
            //格式: EX 5
            int add_event_cnt = stoi(tokens[1]);
            if(add_event_cnt < 0){
                cerr << "Invalid number." << endl;
            }
            else{
                event_cnt_limit += add_event_cnt;
                Calendar::setEventCntMax(event_cnt_limit);
            }
            
       }
       else classifyByType(tokens, calenders, user_cnt);
    }

    // 處理詢問
    string query; cin>>query;
    string query_user = queryModfiy(query);
    queryPrint(query_user, user_cnt, calenders);

    return 0;
}


// function
bool isUserExist(Calendar* calenders, int user_cnt, string ownerName) {
    for(int i=0;i<user_cnt;i++){
        if(calenders[i].getOwnerName() == ownerName){
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

    while (ss >> noskipws >> token) { // 不忽略空白
        if (token.front() == '"' && !inQuotes) { // 遇到開頭的雙引號
            inQuotes = true;
            quotedContent = token.substr(1); // 移除開頭雙引號
        } else if (token.back() == '"' && inQuotes) { // 遇到結尾的雙引號
            inQuotes = false;
            quotedContent += " " + token.substr(0, token.size() - 1); // 加入結尾
            if (resultSize < MAX_TOKENS) { // 使用全域變數作為限制
                result[resultSize++] = quotedContent; // 將完整內容加入結果
            }
        } else if (inQuotes) { // 處於雙引號內
            quotedContent += " " + token;
        } else { // 普通空格分隔部分
            if (resultSize < MAX_TOKENS) { // 使用全域變數作為限制
                result[resultSize++] = token;
            }
        }
    }
}
void classifyByType(string* tokens, Calendar* calenders, int user_cnt) {
    //判斷操作類型
    if(tokens[0]=="AE") // add event
    {  
        //格式: AE "Bob" 2024/11/13 13:00 15:00 "PD Quiz"
        
        //set token
        string owner_name = tokens[1];
        string date_str = tokens[2];
        string begin_str = tokens[3];
        string end_str = tokens[4];
        string event_name_str = tokens[5];

        // transform format
        Date date = strToDate(date_str);
        Time begin = strToTime(begin_str);
        Time end = strToTime(end_str); 

        // check reasonability
        if(!checkDateFormat(date) || !checkTimeFormat(begin) || !checkTimeFormat(end)){
            cerr << "Invalid date or time." << endl;
            return;
        }
        if(!isUserExist(calenders, user_cnt, owner_name)){
            cerr << "User not found." << endl;
            return;
        }
        // add event
        bool isAdd = 

    }
    else if(tokens[0]=="ME") // modify event
    {
        //格式: ME "Bob" "PD Quiz" 2024/11/13 13:00 2024/11/13 16:00 18:00 "PD Quiz"
        
        //set token
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
        if(!isUserExist(calenders, user_cnt, owner_name)){
            cerr << "User not found." << endl;
            return;
        }

        // modify event

    }
    else if(tokens[0]=="RE") // remove event
    {
        //格式: RE "Mary" "Calculus" 2024/11/14 15:00
        
        //set token
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
        if(!isUserExist(calenders, user_cnt, owner_name)){
            cerr << "User not found." << endl;
            return;
        }

        // remove event
        
    }
}  
void expandArray(Calendar*& calenders, int& capacity) {
    int new_capacity = capacity * 2;
    Calendar* new_array = new Calendar[new_capacity];

    for (int i = 0; i < capacity; i++) {
        new_array[i] = calenders[i];
    }

    delete[] calenders;
    calenders = new_array;
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
    string query_user = query.substr(3);
    query.erase(query.size() - 1);
    return query_user;
}
void queryPrint(string query_user, int user_cnt, Calendar* calenders) {
    //格式: 
    // Bob
    // PD Quiz: 2024/11/13, 16:00, 18:00.
    // Concert: 2024/11/20, 19:00, 20:00.
    cout << query_user << endl;
    for(int i=0;i<user_cnt;i++){
        if(calenders[i].getOwnerName() == query_user){
            calenders[i].printCalendarOldToNew();
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