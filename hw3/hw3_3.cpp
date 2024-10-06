#include <iostream>
using namespace std;

const int MAX_PASSENGER_CNT = 18;

// This is the prototype of the function that you need to implement
// the return values should be stored in the array waitingTimes
void getWaitingTimes(int floorCnt,int l,int passengerCnt, 
        int currentFloor, int currentDirection, 
        const int passengerFloors[], const int passengerDirections[], 
        int waitingTimes[]);

int getMin(int a,int b);
int getMax(int a,int b);

int main() 
{
    // read data
    int floorCnt, passengerCnt;
    cin >> floorCnt >> passengerCnt;

    int currentFloor;
    cin >> currentFloor ;

    int passengerFloors[MAX_PASSENGER_CNT] = {0};
    int passengerDirections[MAX_PASSENGER_CNT] = {0};
    int waitingTimes_d[MAX_PASSENGER_CNT] = {0};
    int waitingTimes_u[MAX_PASSENGER_CNT] = {0};
	int h=-1;
    int l=11;
    for (int i = 0; i < passengerCnt; ++i) {
        cin >> passengerFloors[i] >> passengerDirections[i];
        if(passengerFloors[i]>h) h=passengerFloors[i];
        if(passengerFloors[i]<l) l=passengerFloors[i];
    }
   
    // calculate the waiting times of all passengers
    getWaitingTimes(h,l, passengerCnt, currentFloor, 1, 
                    passengerFloors, passengerDirections, waitingTimes_u);
    getWaitingTimes(h,l, passengerCnt, currentFloor, -1, 
                    passengerFloors, passengerDirections, waitingTimes_d);

    // print out the waiting times of all passengers
    int u=0;
    int d=0;
    for(int i = 0; i < passengerCnt ; i++){
        u+=waitingTimes_u[i];
    }
    for(int i = 0; i < passengerCnt ; i++){
        d+=waitingTimes_d[i];
    }
    cout<<"u="<<u<<",d="<<d;
    
    return 0;
}

// PDOGS will copy and paste the code you upload to this place 
// and compile the resulting program

void getWaitingTimes(int floorCnt,int l, int passengerCnt, int currentFloor, int currentDirection, const int passengerFloors[], const int passengerDirections[], int waitingTimes[]){
    for(int i=0;i<passengerCnt;i++){
        int cf=currentFloor;
        
        int cd=currentDirection;
        int waitingTime =0;
        if(cf>floorCnt){
            waitingTime+=
            cf=floorCnt;
            
        }
        if(cf<l){

        }
        cout<<"now passsenger:"<<i<<endl;  
        
        while(!(((cf==passengerFloors[i])&&(cd==passengerDirections[i]))||((cf==passengerFloors[i])&&(passengerFloors[i]==(l||floorCnt))))) //沒接到
        {
            waitingTime++;
            cout<<"now floor:"<<cf<<endl;
            cf+=cd;
            if(cf==floorCnt) //到頂
            {
                cd=-1;
            }
            if(cf==l) //到底
            {
                cd=1;
            }
        }
        waitingTimes[i]=waitingTime;
    }
}

int getMin(int a,int b){
    if(a<b) return a;
    else return b;
}

int getMax(int a,int b){
    if(a>b) return a;
    else return b;
}