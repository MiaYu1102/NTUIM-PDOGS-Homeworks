#include <bits/stdc++.h>
using namespace std;

const int MAX_Elevator_CNT = 10;

int ElevatorFloors[MAX_Elevator_CNT];
int ElevatorDirections[MAX_Elevator_CNT];

int initHighestFloor[MAX_Elevator_CNT];
int initLowestFloor[MAX_Elevator_CNT];

int initInnerCallCnt[MAX_Elevator_CNT];
int TotalOuterCallCnt;

vector<vector<int>> innerCallFloors;
vector<int> TotalOuterCallFloors;
vector<int> TotalOuterCallDirections;

// Initialize variables for the number of elevators, floors, and time intervals
int n, k, capacity, _alpha, _beta, _gamma; // 要加底線不然會撞名
int timePerFloor, timePerDoorCycle;

// FUNCTIONS
int getResult(vector<int> individual);
vector <int> getRandomIndividual(int individualSize, int geneMinValue, int geneMaxValue);
int getWaitingTime(int currentFloor, int currentDirection,
				   int highestFloor, int lowestFloor,
                   vector<int> outerCallFloors, vector<int> outerCallDirections,
				   int innerCallCnt, int outerCallCnt, int Ind, bool isStop);


// TODO: Replace this function with GA in the future
vector<int> solveByRandomSearch(int generations) {
    int bestResult = INT_MAX;
    vector<int> bestIndividual;

    for (int i = 0; i < generations; i++) {
        vector<int> individual;

        individual = getRandomIndividual(TotalOuterCallCnt, 0, n-1);
        
        int result = getResult(individual);

        if (result < bestResult) {
            bestResult = result;
            bestIndividual = individual;
        }
    }
    return bestIndividual;
}

int main() {
    // Initialize variables for the number of elevators, floors, and time intervals
    cin >> n >> k >> capacity >> timePerFloor >> timePerDoorCycle >> _alpha >> _beta >> _gamma;
 
    for (int i = 0; i < n; i++) {
        cin >> ElevatorFloors[i] >> ElevatorDirections[i];
    }

    for (int i = 0; i < n; i++) {
        initLowestFloor[i] = 1;
        initHighestFloor[i] = k;
    }

    // Input the inner calls (calls made from inside the elevator)
    innerCallFloors.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> initInnerCallCnt[i];
        for (int j = 0; j < initInnerCallCnt[i]; j++) {
            int t; 
            cin >> t;
            innerCallFloors[i].push_back(t);
            initHighestFloor[i] = max(initHighestFloor[i], innerCallFloors[i][j]);
            initLowestFloor[i]  = min(initLowestFloor[i], innerCallFloors[i][j]);
        }
    }

    // Input the outer calls (calls made from outside the elevator)
    cin >> TotalOuterCallCnt;
    for (int j = 0; j < TotalOuterCallCnt; j++) {
        int u,v; cin >> u >> v;
        TotalOuterCallFloors.push_back(u);
        TotalOuterCallDirections.push_back(v);
    }

    // Try to find the best elevator distribution for the new request
    const int generations = 10000;
    vector<int> bestIndividual = solveByRandomSearch(generations);


    // output
    for (int i = 0; i < TotalOuterCallCnt - 1; i++)
        cout << bestIndividual[i] +1 << ',';
    cout << bestIndividual[TotalOuterCallCnt-1] +1 << endl;
}

unordered_set<string> seenIndividuals;
const int seed = 13705006;
mt19937 gen(seed);
vector <int> getRandomIndividual(int individualSize, int geneMinValue, int geneMaxValue) {
    vector<int> individual;
    for (int i = 0; i < individualSize; i++) {
        individual.push_back(uniform_int_distribution<int>(geneMinValue, geneMaxValue)(gen));
    }
    return individual;
}

int getResult(vector<int> individual){
    // Calculate the initial waiting time for each elevator
    vector<int> timeRec(MAX_Elevator_CNT);

    for (int i = 0; i < n; i++) {
        //分配外部呼叫&算最高最矮
        vector<int> outerCallFloors;
        vector<int> outerCallDirections;
        int hf= initHighestFloor[i];
        int lf= initLowestFloor[i];
        
        for (int j = 0; j < TotalOuterCallCnt; j++) {
            if(individual[j] == i){
                outerCallFloors.push_back(TotalOuterCallFloors[j]);
                outerCallDirections.push_back(TotalOuterCallDirections[j]);

                hf = max(TotalOuterCallFloors[j],hf);
                lf = min(TotalOuterCallFloors[j],lf);
            }
        }

        // 丟函數
        if (ElevatorDirections[i] == 0) {
            int time_up, time_down;
            time_up    = getWaitingTime(ElevatorFloors[i], 1,
										hf, lf,
                                        outerCallFloors, outerCallDirections,
										initInnerCallCnt[i], outerCallFloors.size(), i, 1);

            time_down  = getWaitingTime(ElevatorFloors[i], -1,
										hf, lf,
                                        outerCallFloors, outerCallDirections,
										initInnerCallCnt[i], outerCallFloors.size(), i, 1);
            timeRec[i] = min(time_up, time_down);
        } else {
            timeRec[i] = getWaitingTime(ElevatorFloors[i], ElevatorDirections[i],
                                        hf, lf,
                                        outerCallFloors, outerCallDirections,
                                        initInnerCallCnt[i], outerCallFloors.size(), i, 0);
        }
    }

    int sum = accumulate(timeRec.begin(), timeRec.end(), 0);
    return sum;
    
}


int getWaitingTime(int currentFloor, int currentDirection, 
				   int highestFloor, int lowestFloor,
                   vector<int> outerCallFloors, vector<int> outerCallDirections, 
				   int innerCallCnt, int outerCallCnt, int Ind, bool isStop) {

    if(outerCallCnt + innerCallCnt==0) return 0;
    vector<pair<int, int>> WaitingTime(outerCallCnt+innerCallCnt, {INT_MAX, 0});

    // Handle out-of-bounds situations
    if (currentFloor > highestFloor && currentDirection == 1) {
        currentDirection *= -1;
    } else if (currentFloor < lowestFloor && currentDirection == -1) {
        currentDirection *= -1;
    }

    // Calculate waiting time for outer calls
    int outerWaitingTime = 0;
    if (currentDirection == 1) {
        for (int i = 0; i < outerCallCnt; i++) {
            if(isStop == 1 && outerCallFloors[i] == currentFloor){
                WaitingTime[i] = {0,0};
            }
            else if (currentDirection == outerCallDirections[i]) {
                if (outerCallFloors[i] > currentFloor) {
                    WaitingTime[i] = {(outerCallFloors[i] - currentFloor),0};
                }  else {
                    WaitingTime[i] = {2 * (highestFloor - lowestFloor) -
                                    (currentFloor - outerCallFloors[i]),0};
                }

            } else {
                WaitingTime[i]= {(highestFloor - currentFloor) +
                                (highestFloor - outerCallFloors[i]),0};
            }
            outerWaitingTime += WaitingTime[i].first;
        }
    }
    if (currentDirection == -1) {
        for (int i = 0; i < outerCallCnt; i++) {
            if(isStop == 1 && outerCallFloors[i] == currentFloor){
                WaitingTime[i] = {0,0};
            }
            else if (currentDirection == outerCallDirections[i]) {
                if (outerCallFloors[i] < currentFloor) {
                    WaitingTime[i] = {(currentFloor - outerCallFloors[i]),0};
                } else {
                    WaitingTime[i] = {2 * (highestFloor - lowestFloor) -
                                     (outerCallFloors[i] - currentFloor),0};
                }

            } else {
                WaitingTime[i] = {(currentFloor - lowestFloor) +
                                (outerCallFloors[i] - lowestFloor),0};
            }
            outerWaitingTime += WaitingTime[i].first;
        }
    }
    outerWaitingTime *= timePerFloor;
    
    // Calculate waiting time for inner calls
    int innerWaitingTime = 0;
    if (currentDirection == 1) {
        for (int i = 0; i < innerCallCnt; i++) {
            if (innerCallFloors[Ind][i] >= currentFloor) {
                WaitingTime[i + outerCallCnt] = {(innerCallFloors[Ind][i] - currentFloor), 1};
            } else {
                WaitingTime[i + outerCallCnt] = {(highestFloor - currentFloor) +
                                (highestFloor - innerCallFloors[Ind][i]), 1};
            }
            innerWaitingTime += WaitingTime[i + outerCallCnt].first;
        }
    }
    if (currentDirection == -1) {
        for (int i = 0; i < innerCallCnt; i++) {
            if (innerCallFloors[Ind][i] <= currentFloor) {
                WaitingTime[i + outerCallCnt] = {(currentFloor - innerCallFloors[Ind][i]), 1};
            } else {
                WaitingTime[i + outerCallCnt] = {(currentFloor - lowestFloor) +
                                (innerCallFloors[Ind][i] - lowestFloor), 1};
            }
            innerWaitingTime += WaitingTime[i + outerCallCnt].first;
        }
    }
    innerWaitingTime *= timePerFloor;

    sort(WaitingTime.begin(), WaitingTime.end(), [](pair<int, int> a, pair<int, int> b) {
        if (a.first == b.first) return a.second > b.second;
        return a.first < b.first;
    });
    
    int doorCnt = -1;
    int burden = 0;
    int personCnt = innerCallCnt;

    for(int i = 0; i < (innerCallCnt + outerCallCnt); i++){
        doorCnt ++;
        if(i > 0 && WaitingTime[i-1].first == WaitingTime[i].first){
            doorCnt--;
        }
        if(WaitingTime[i].second == 1){
            personCnt--;
            innerWaitingTime += timePerDoorCycle * doorCnt;
        }
        if(WaitingTime[i].second == 0){
            personCnt++;
            burden += max(personCnt-capacity, 0);
            outerWaitingTime += timePerDoorCycle * doorCnt;
        }
    }

    return outerWaitingTime * _alpha + innerWaitingTime * _beta + burden * _gamma;
}