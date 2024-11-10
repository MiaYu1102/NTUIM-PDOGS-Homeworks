#include <bits/stdc++.h>
using namespace std;

const int MAX_Elevator_CNT = 10;

int timePerFloor, timePerDoorCycle;

int ElevatorFloors[MAX_Elevator_CNT];
int ElevatorDirections[MAX_Elevator_CNT];

int highestFloor[MAX_Elevator_CNT];
int lowestFloor[MAX_Elevator_CNT];

int innerCallCnt[MAX_Elevator_CNT];
int TotalOuterCallCnt;

vector<vector<int>> innerCallFloors;
vector<int> TotalOuterCallFloors;
vector<int> TotalOuterCallDirections;


//int getOneElevatorTime();

int getResult(int n, vector<int> cb);

int getWaitingTime(int currentFloor, int currentDirection,
				   int highestFloor, int lowestFloor,
                   vector<int> outerCallFloors, vector<int> outerCallDirections,
				   int innerCallCnt, int outerCallCnt, int Ind);

vector<int> getCB(int n);

int countSum(const int arr[], int n);


int main() 
{
    // Initialize variables for the number of elevators, floors, and time intervals
    int n, k, c, alpha, beta, gamma;
    cin >> n >> k >> c >> timePerFloor >> timePerDoorCycle >> alpha >> beta >> gamma;


    for (int i = 0; i < n; i++) {
        cin >> ElevatorFloors[i] >> ElevatorDirections[i];
    }

    // Arrays to track the highest and lowest floors each elevator will visit
    
    for (int i = 0; i < n; i++) {
        highestFloor[i] = 1;
        lowestFloor[i]  = k;
    }

    // Input the inner calls (calls made from inside the elevator)
    
    for (int i = 0; i < n; i++) {
        cin >> innerCallCnt[i];
        for (int j = 0; j < innerCallCnt[i]; j++) {
            int t; cin>>t;
            innerCallFloors[i].push_back(t);
            highestFloor[i] = max(highestFloor[i], innerCallFloors[i][j]);
            lowestFloor[i]  = min(lowestFloor[i], innerCallFloors[i][j]);
        }
    }

    // Input the outer calls (calls made from outside the elevator)
    cin >> TotalOuterCallCnt;
    for (int j = 0; j < TotalOuterCallCnt; j++) {
        int u,v; cin>>u>>v;
        TotalOuterCallFloors.push_back(u);
        TotalOuterCallDirections.push_back(v);
    }

    // Try to find the best elevator for the new request
    int randCnt = 10;
    int minimumTime = INT_MAX;
    vector<int> bestCB;
    for (int i = 0; i < randCnt; i++) 
    {
        vector<int> randvec = getCB(n);
        int currentTime = getResult(n, randvec);
        if (currentTime < minimumTime) {
            minimumTime = currentTime;
            bestCB = randvec;
        }
    }

    // output
    for(int i=0;i<TotalOuterCallCnt-1;i++)
        cout<<bestCB[i]<<',';
    cout<<bestCB[TotalOuterCallCnt-1];

    return 0;
}

int getWaitingTime(int currentFloor, int currentDirection, 
				   int highestFloor, int lowestFloor,
                   vector<int> outerCallFloors, vector<int> outerCallDirections, 
				   int innerCallCnt, int outerCallCnt, int Ind) {

    if(outerCallCnt+innerCallCnt==0) return 0;
    
    int WaitingTime[outerCallCnt+innerCallCnt];
    for(int i=0;i<outerCallCnt+innerCallCnt;i++){
        WaitingTime[i]=0;
    }

    // Handle out-of-bounds situations
    if (currentFloor > highestFloor && currentDirection == 1) {
        currentDirection *= -1;
    } else if (currentFloor < lowestFloor && currentDirection == -1) {
        currentDirection *= -1;
    }

    // Calculate waiting time for outer calls
    if (currentDirection == 1) {
        for (int i = 0; i < outerCallCnt; i++) {

            if (currentDirection == outerCallDirections[i]) {

                if (outerCallFloors[i] >= currentFloor) {
                    WaitingTime[i] = (outerCallFloors[i] - currentFloor);
                }  else {
                    WaitingTime[i] = 2 * (highestFloor - lowestFloor) -
                                    (currentFloor - outerCallFloors[i]);
                }

            } else {
                WaitingTime[i]= (highestFloor - currentFloor) +
                                (highestFloor - outerCallFloors[i]);
            }
        }
    }
    if (currentDirection == -1) {
        for (int i = 0; i < outerCallCnt; i++) {
            if (currentDirection == outerCallDirections[i]) {
                if (outerCallFloors[i] <= currentFloor) {
                    WaitingTime[i] = (currentFloor - outerCallFloors[i]);
                } else {
                    WaitingTime[i] = 2 * (highestFloor - lowestFloor) -
                                     (outerCallFloors[i] - currentFloor);
                }

            } else {
                WaitingTime[i] = (currentFloor - lowestFloor) +
                                (outerCallFloors[i] - lowestFloor);
            }
        }
    }

    // Calculate waiting time for inner calls
    if (currentDirection == 1) {
        for (int i = 0; i < innerCallCnt; i++) {
            if (innerCallFloors[Ind][i] >= currentFloor) {
                WaitingTime[i + outerCallCnt] = (innerCallFloors[Ind][i] - currentFloor);
            } else {
                WaitingTime[i + outerCallCnt] = (highestFloor - currentFloor) +
                                (highestFloor - innerCallFloors[Ind][i]);
            }
        }
    }
    if (currentDirection == -1) {
        for (int i = 0; i < innerCallCnt; i++) {
            if (innerCallFloors[Ind][i] <= currentFloor) {
                WaitingTime[i + outerCallCnt] = (currentFloor - innerCallFloors[Ind][i]);
            } else {
                WaitingTime[i + outerCallCnt] = (currentFloor - lowestFloor) +
                                (innerCallFloors[Ind][i] - lowestFloor);
            }
        }
    }
    sort(WaitingTime, WaitingTime+(innerCallCnt + outerCallCnt));
    int doorCnt = 0;
    int tempCnt = 0;
    for(int i = 0; i < (innerCallCnt + outerCallCnt); i++){
        doorCnt += tempCnt;
        tempCnt++;
        if(i > 0 && WaitingTime[i-1] == WaitingTime[i]){
            tempCnt--;
            doorCnt--;
        } 
    }

    int WaitingTimes = 0;
    for(int i = 0; i < (innerCallCnt + outerCallCnt); i++){
        WaitingTimes += WaitingTime[i];
    }

    return WaitingTimes * timePerFloor + timePerDoorCycle * doorCnt;
}

int getResult(int n, vector<int> cb){
    
    for(int s:cb)
            cerr<<s<<" ";
        cerr<<endl;

    // Calculate the initial waiting time for each elevator
    int timeRec[MAX_Elevator_CNT];
    
    for (int i = 0; i < n; i++) {
        cerr<<"i="<<i<<endl;
        //分配外部呼叫&算最高最矮
        vector<int> outerCallFloors;
        vector<int> outerCallDirections;
        int hf=highestFloor[i];
        int lf=lowestFloor[i];
        
        for(int j=0; j<TotalOuterCallCnt ;j++){
            if(cb[j]==i+1){
                outerCallFloors.push_back(TotalOuterCallFloors[j]);
                outerCallDirections.push_back(TotalOuterCallDirections[j]);

                hf=max(TotalOuterCallFloors[j],hf);
                lf=min(TotalOuterCallFloors[j],lf);
            }
        }
        for(int s:outerCallFloors)
            cerr<<s<<" ";
        cerr<<endl;
        for(int s:outerCallDirections)
            cerr<<s<<" ";
        cerr<<endl;

        cerr<<"check"<<endl;
        //丟函數
        if (ElevatorDirections[i] == 0) {
            int time_up, time_down;
            time_up    = getWaitingTime(ElevatorFloors[i], 1,
										hf, lf,
                                        outerCallFloors, outerCallDirections,
										innerCallCnt[i], outerCallFloors.size(), i);

            time_down  = getWaitingTime(ElevatorFloors[i], -1,
										hf, lf,
                                        outerCallFloors, outerCallDirections,
										innerCallCnt[i], outerCallFloors.size(), i);
            timeRec[i] = min(time_up, time_down);
        } else
            timeRec[i] = getWaitingTime(ElevatorFloors[i], ElevatorDirections[i],
										hf, lf,
                                        outerCallFloors, outerCallDirections,
										innerCallCnt[i], outerCallFloors.size(), i);
    }

    int sum = countSum(timeRec, n);
    cout<<"sum="<<sum<<endl;
    return sum;
}

int countSum(const int arr[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    return sum;
}

vector<int> getCB(int n) {
    int seed=13705006;
    mt19937 gen(seed);

    vector<int> vec;
    for(int i=0;i<n;i++){
        int k= uniform_int_distribution<int>(1,n)(gen);
        vec.push_back(k);
        cerr<<k<<" ";
    }
    cerr<<endl;
    //寫unordermap防相同
    for(int s:vec)
        cerr<<s<<" ";
    cerr<<endl;

    return vec;
}


