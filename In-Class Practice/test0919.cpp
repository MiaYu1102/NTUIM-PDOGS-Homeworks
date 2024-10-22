#include<iostream>
#include<climits>
using namespace std;
const int MAX_PASSENGER_CNT = 18;

int getWaitingTime(int floorCnt, int currentFloor, int currentDirection, 
                   int passengerFloor, int passengerDirection);

void getWaitingTimes(int floorCnt, int passengerCnt, 
        int currentFloor, int currentDirection, 
        const int passengerFloors[], const int passengerDirections[], 
        int waitingTimes[]);

int getMax(int, const int [], int = INT_MIN);
int getMax(int, int);

int getMin(int, const int [], int = INT_MAX);
int getMin(int, int);

int main() 
{
    // read data
    int floorCnt, passengerCnt;
    cin >> floorCnt >> passengerCnt;
    int currentFloor, currentDirection;
    cin >> currentFloor;
    int passengerFloors[MAX_PASSENGER_CNT] = {0};
    int passengerDirections[MAX_PASSENGER_CNT] = {0};
    int waitingTimes[MAX_PASSENGER_CNT] = {0};
    for (int i = 0; i < passengerCnt; ++i) 
        cin >> passengerFloors[i] >> passengerDirections[i];

    //converting
    int difference;
    difference = (getMax(passengerCnt, passengerFloors, currentFloor) - getMin(passengerCnt, passengerFloors, currentFloor) + 1) 
        - getMax(passengerCnt, passengerFloors, currentFloor);
/*
    if(getMin(passengerCnt, passengerFloors) <= currentFloor) //min floor <= current floor
        difference = (getMax(passengerCnt, passengerFloors) - getMin(passengerCnt, passengerFloors) + 1) - getMax(passengerCnt, passengerFloors);
    else //min floor > current floor
        difference = (getMax(passengerCnt, passengerFloors) - currentFloor + 1) - getMax(passengerCnt, passengerFloors);
*/
    for(int i = 0; i < passengerCnt; i++)
        passengerFloors[i] += difference; 
    currentFloor += difference;
    floorCnt = getMax(passengerCnt, passengerFloors, currentFloor);
/*
    for(int i=0; i<18; i++)
        cout << passengerFloors[i] << " ";
    cout << endl;
    cout << "floorCnt: " << floorCnt << endl;
*/
    for(int i = 0; i < passengerCnt; i++) //turn around for top floor passengers
        if(passengerFloors[i] == getMax(passengerCnt, passengerFloors, currentFloor))
            passengerDirections[i] = -1;
    for(int i = 0; i < passengerCnt; i++) //turn around for ground floor passengers
        if(passengerFloors[i] == getMin(passengerCnt, passengerFloors, currentFloor))
            passengerDirections[i] = 1;
    

    int sum[2] = {0}; //[0] for up, [1] for down
    //case start direction == up
//    cout << "case up" << endl;
    currentDirection = 1;
    if(currentFloor >= floorCnt) //elevator is at top floor
        currentDirection = -1;
    getWaitingTimes(floorCnt, passengerCnt, currentFloor, currentDirection, 
                    passengerFloors, passengerDirections, waitingTimes);
    for(int i = 0; i < passengerCnt; i++)
        sum[0] += waitingTimes[i];

    //case start direction == down 
//    cout << "case down" << endl;
    currentDirection = -1;
    if(currentFloor <= 1) //elevator is at ground floor
        currentDirection = 1;
    getWaitingTimes(floorCnt, passengerCnt, currentFloor, currentDirection, 
                    passengerFloors, passengerDirections, waitingTimes);
    for(int i = 0; i < passengerCnt; i++)
        sum[1] += waitingTimes[i];
    
    // print out the waiting times of all passengers
    cout << getMin(2, sum);
    
    return 0;
}

//問題出在這塊
int getWaitingTime(int floorCnt, int currentFloor, int currentDirection, 
                   int passengerFloor, int passengerDirection)
{
    int timeUsage = 0;
    while(currentFloor != passengerFloor || currentDirection != passengerDirection)
    {
        cout<<currentFloor<<endl;
        if(currentDirection == 1) //up
            currentFloor++;
        else //down
            currentFloor--;
        timeUsage++;

        if(currentFloor >= floorCnt || currentFloor <= 1) //turn around
            currentDirection *= -1;
    }
    
    return timeUsage;
}

void getWaitingTimes(int floorCnt, int passengerCnt, 
        int currentFloor, int currentDirection, 
        const int passengerFloors[], const int passengerDirections[], 
        int waitingTimes[])
{
    for(int i = 0; i < passengerCnt; i++)
        waitingTimes[i] = getWaitingTime(floorCnt, currentFloor, currentDirection, passengerFloors[i], passengerDirections[i]);
}

int getMax(int passengerCnt, const int passengerFloors[], int currentFloor)
{
    int max = 0;
    for(int i = 0; i < passengerCnt; i++)
        if(passengerFloors[i] > max)
            max = passengerFloors[i];
    max = getMax(max, currentFloor);
    return max;
}

int getMax(int a, int b)
{
    if(a > b)
        return a;
    else
        return b;
}

int getMin(int passengerCnt, const int passengerFloors[], int currentFloor)
{
    int min = INT_MAX;
    for(int i = 0; i < passengerCnt; i++)
        if(passengerFloors[i] < min)
            min = passengerFloors[i];
    min = getMin(min, currentFloor);
    return min;
}

int getMin(int a, int b)
{
    if(a < b)
        return a;
    else
        return b;
}