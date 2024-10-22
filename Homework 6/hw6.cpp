#include <bits/stdc++.h>
using namespace std;


const int MAX_Elevator_CNT = 10;

int getWaitingTime(int currentFloor, int currentDirection,
				   int highestFloor, int lowestFloor, 
				   int innerCallCnt, int outerCallCnt,
                   int* innerCallFloors, int* outerCallFloors, int* outerCallDirections, 
				   int timePerFloor, int timePerDoorCycle);


int countSum(const int arr[], int n);


int main() 
{
    // Initialize variables for the number of elevators, floors, and time intervals
    int elevatorCnt, floorCnt, timePerFloor, timePerDoorCycle;
    cin >> elevatorCnt >> floorCnt >> timePerFloor >> timePerDoorCycle;

    // Arrays to store the current floor and direction of each elevator
    int ElevatorFloors[MAX_Elevator_CNT];
    int ElevatorDirections[MAX_Elevator_CNT];

    for (int i = 0; i < elevatorCnt; i++) {
        cin >> ElevatorFloors[i] >> ElevatorDirections[i];
    }

    // Arrays to track the highest and lowest floors each elevator will visit
    int highestFloor[MAX_Elevator_CNT];
    int lowestFloor[MAX_Elevator_CNT];
    for (int i = 0; i < elevatorCnt; i++) {
        highestFloor[i] = 1;
        lowestFloor[i]  = floorCnt;
    }

    // Input the inner calls (calls made from inside the elevator)
    int** innerCall = nullptr;
    innerCall       = new int*[MAX_Elevator_CNT];
    int innCallCnt[MAX_Elevator_CNT];
    for (int i = 0; i < elevatorCnt; i++) {
        cin >> innCallCnt[i];
        innerCall[i] = new int[innCallCnt[i] + 1];
        for (int j = 0; j < innCallCnt[i]; j++) {
            cin >> innerCall[i][j];
            highestFloor[i] = max(highestFloor[i], innerCall[i][j]);
            lowestFloor[i]  = min(lowestFloor[i], innerCall[i][j]);
        }
    }

    // Input the outer calls (calls made from outside the elevator)
    int** outerCall           = nullptr;
    int** outerCallDirections = nullptr;  
    outerCall                 = new int*[MAX_Elevator_CNT];
    outerCallDirections       = new int*[MAX_Elevator_CNT];

    int outCallCnt[MAX_Elevator_CNT];
    for (int i = 0; i < elevatorCnt; i++) {
        cin >> outCallCnt[i];
        outerCall[i]           = new int[outCallCnt[i] + 1];
        outerCallDirections[i] = new int[outCallCnt[i] + 1];

        for (int j = 0; j < outCallCnt[i]; j++) {
            cin >> outerCall[i][j] >> outerCallDirections[i][j];
            highestFloor[i] = max(highestFloor[i], outerCall[i][j]);
            lowestFloor[i]  = min(lowestFloor[i], outerCall[i][j]);
        }
    }

    // Input the floor and direction of the new request
    int newCallFloor, newCallDirection;
    cin >> newCallFloor >> newCallDirection;

    // Calculate the initial waiting time for each elevator
    int timeRec[MAX_Elevator_CNT];
    for (int i = 0; i < elevatorCnt; i++) {
        if (ElevatorDirections[i] == 0) {
            int time_up, time_down;
            time_up    = getWaitingTime(ElevatorFloors[i], 1,
										highestFloor[i], lowestFloor[i], 
										innCallCnt[i], outCallCnt[i], 
										innerCall[i], outerCall[i], outerCallDirections[i],
				   						timePerFloor, timePerDoorCycle);

            time_down  = getWaitingTime(ElevatorFloors[i], -1, 
										highestFloor[i], lowestFloor[i], 
										innCallCnt[i], outCallCnt[i], 
										innerCall[i], outerCall[i], outerCallDirections[i],
				   						timePerFloor, timePerDoorCycle);

            timeRec[i] = min(time_up, time_down);
        } else
            timeRec[i] = getWaitingTime(ElevatorFloors[i], ElevatorDirections[i], 
										highestFloor[i], lowestFloor[i],
										innCallCnt[i], outCallCnt[i], 
										innerCall[i], outerCall[i], outerCallDirections[i],
										timePerFloor, timePerDoorCycle);
    }

    int sum = countSum(timeRec, elevatorCnt);

    // Try to find the best elevator for the new request
    int bestElevatorindex = -1;
    int minimumTime       = INT_MAX;
    for (int i = 0; i < elevatorCnt; i++) 
    {
        // Add the new request to the current outer calls of the elevator
        outerCall[i][outCallCnt[i]]  = newCallFloor;
        outerCallDirections[i][outCallCnt[i]] = newCallDirection;
        highestFloor[i]           = max(highestFloor[i], outerCall[i][outCallCnt[i]]);
        lowestFloor[i]            = min(lowestFloor[i], outerCall[i][outCallCnt[i]]);

        int newCallTime;
        if (ElevatorDirections[i] == 0) {
            int time_up, time_down;
            time_up   = getWaitingTime(ElevatorFloors[i], 1, 
									   highestFloor[i], lowestFloor[i],
									   innCallCnt[i], outCallCnt[i] + 1, 
									   innerCall[i], outerCall[i], outerCallDirections[i],
									   timePerFloor, timePerDoorCycle);

            time_down = getWaitingTime(ElevatorFloors[i], -1, 
									   highestFloor[i], lowestFloor[i], 
									   innCallCnt[i], outCallCnt[i] + 1, 
									   innerCall[i], outerCall[i], outerCallDirections[i],
									   timePerFloor, timePerDoorCycle);

            newCallTime = min(time_up, time_down);

        } else {
            newCallTime = getWaitingTime(ElevatorFloors[i], ElevatorDirections[i],
                               highestFloor[i], lowestFloor[i], 
							   innCallCnt[i], outCallCnt[i] + 1, 
							   innerCall[i], outerCall[i], outerCallDirections[i],
							   timePerFloor, timePerDoorCycle);
		}

        int currentTime = sum - timeRec[i] + newCallTime;
        if (currentTime < minimumTime) {
            minimumTime       = currentTime;
            bestElevatorindex = i;
        }
    }

    // output
    cout << ++bestElevatorindex << "," << minimumTime << endl;

    // release the dynamically allocated memory
    for (int i = 0; i < elevatorCnt; i++) delete[] innerCall[i];
    delete[] innerCall;

    for (int i = 0; i < elevatorCnt; i++) delete[] outerCall[i];
    delete[] outerCall;

    for (int i = 0; i < elevatorCnt; i++) delete[] outerCallDirections[i];
    delete[] outerCallDirections;

    return 0;
}

int getWaitingTime(int currentFloor, int currentDirection, 
				   int highestFloor, int lowestFloor, 
				   int innerCallCnt, int outerCallCnt,
                   int* innerCallFloors, int* outerCallFloors, int* outerCallDirections, 
				   int timePerFloor, int timePerDoorCycle) {

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
            if (innerCallFloors[i] >= currentFloor) {
                WaitingTime[i + outerCallCnt] = (innerCallFloors[i] - currentFloor);
            } else {
                WaitingTime[i + outerCallCnt] = (highestFloor - currentFloor) +
                                (highestFloor - innerCallFloors[i]);
            }
        }
    }
    if (currentDirection == -1) {
        for (int i = 0; i < innerCallCnt; i++) {
            if (innerCallFloors[i] <= currentFloor) {
                WaitingTime[i + outerCallCnt] = (currentFloor - innerCallFloors[i]);
            } else {
                WaitingTime[i + outerCallCnt] = (currentFloor - lowestFloor) +
                                (innerCallFloors[i] - lowestFloor);
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


int countSum(const int arr[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    return sum;
}


