#include <iostream>
using namespace std;

const int MAX_PASSENGER_CNT = 18;

// This is the prototype of the function that you need to implement
// the return values should be stored in the array waitingTimes
void getWaitingTimes(int floorCnt, int passengerCnt, 
        int currentFloor, int currentDirection, 
        const int passengerFloors[], const int passengerDirections[], 
        int waitingTimes[]);

int main() 
{
    // read data
    int floorCnt, passengerCnt;
    cin >> floorCnt >> passengerCnt;

    int currentFloor, currentDirection;
    cin >> currentFloor >> currentDirection;

    int passengerFloors[MAX_PASSENGER_CNT] = {0};
    int passengerDirections[MAX_PASSENGER_CNT] = {0};
    int waitingTimes[MAX_PASSENGER_CNT] = {0};
	
    for (int i = 0; i < passengerCnt; ++i) 
        cin >> passengerFloors[i] >> passengerDirections[i];
    
    // calculate the waiting times of all passengers
    getWaitingTimes(floorCnt, passengerCnt, currentFloor, currentDirection, 
                    passengerFloors, passengerDirections, waitingTimes);

    // print out the waiting times of all passengers
    for(int i = 0; i < passengerCnt - 1; i++)
        cout << waitingTimes[i] << ",";
    cout << waitingTimes[passengerCnt - 1];
    
    return 0;
}

// PDOGS will copy and paste the code you upload to this place 
// and compile the resulting program

void getWaitingTimes(int floorCnt, int passengerCnt, int currentFloor, int currentDirection, const int passengerFloors[], const int passengerDirections[], int waitingTimes[]){
    for(int i=0;i<passengerCnt;i++){
        int cf=currentFloor;
        int cd=currentDirection;
        int waitingTime =0;
        if(floorCnt==1) waitingTimes[i]=waitingTime;
        while(!((cf==passengerFloors[i])&&(cd==passengerDirections[i]))) //沒接到
        {
            waitingTime++;
            //cout<<"now floor:"<<cf<<endl;
            cf+=cd;
            if(cf==floorCnt) //到頂
            {
                cd=-1;
            }
            if(cf==1) //到底
            {
                cd=1;
            }
        }
        waitingTimes[i]=waitingTime;
    }
}