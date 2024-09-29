# include <iostream>
using namespace std;

// This is the prototype of the function that you need to implement
int getWaitingTime (int floorCnt , int currentFloor , int currentDirection ,int passengerFloor , int passengerDirection );

int main ()
{
// read data
int floorCnt = 0, currentFloor = 0, currentDirection = 0,
passengerFloor = 0, passengerDirection = 0;
cin >> floorCnt ;
cin >> currentFloor >> currentDirection ;
cin >> passengerFloor >> passengerDirection ;

// calculate the waiting time of the passenger
int waitingTime = getWaitingTime (floorCnt , currentFloor ,currentDirection , passengerFloor ,passengerDirection );

// print out the waiting time of the passenger
cout << waitingTime << endl;
return 0;
}

// PDOGS will copy and paste the code you upload to this place
// and compile the resulting program
int getWaitingTime (int floorCnt , int currentFloor , int currentDirection ,int passengerFloor , int passengerDirection ){
    int waitingTime =0;
    if(floorCnt==1) return waitingTime;
    while(!((currentFloor==passengerFloor)&&(currentDirection==passengerDirection))) //沒接到
    {
        waitingTime++;
        //cout<<"now floor:"<<currentFloor<<endl;
        currentFloor+=currentDirection;
        if(currentFloor==floorCnt) //到頂
        {
            currentDirection=-1;
        }
        if(currentFloor==1) //到底
        {
            currentDirection=1;
        }
    }
    return waitingTime;
}