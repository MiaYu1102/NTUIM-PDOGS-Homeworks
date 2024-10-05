#include <climits>
#include <cmath>
#include <algorithm>
#include <iostream>
using namespace std;

//剛寫好拿上去丟的版本

const int MAX_Elevator_CNT = 10;

int getWaitingTime(int currentFloor, int currentDirection,
				   int highestFloor, int lowestFloor, 
				   int innerCallCnt, int outerCallCnt,
                   int* innerCallFloors, int* outerCallFloors, int* outerCallDirections, 
				   int timePerFloor, int timePerDoorCycle);

int getMin(int a, int b);
int getMax(int a, int b);

int countSum(const int arr[], int n);

int main() {
    // 初
    int n, k, timePerFloor, timePerDoorCycle;
    cin >> n >> k >> timePerFloor >> timePerDoorCycle;

    // 本體
    int ElevatorFloors[MAX_Elevator_CNT];
    int ElevatorDirections[MAX_Elevator_CNT];

    for (int i = 0; i < n; i++) {
        cin >> ElevatorFloors[i] >> ElevatorDirections[i];
    }

    //
    int highestFloor[MAX_Elevator_CNT];
    int lowestFloor[MAX_Elevator_CNT];
    for (int i = 0; i < n; i++) {
        highestFloor[i] = 1;
        lowestFloor[i]  = k;
    }

    // 內
    int** innerCall = nullptr;
    innerCall       = new int*[MAX_Elevator_CNT];
    int innCallCnt[MAX_Elevator_CNT];
    for (int i = 0; i < n; i++) {
        cin >> innCallCnt[i];
        innerCall[i] = new int[innCallCnt[i] + 1];
        for (int j = 0; j < innCallCnt[i]; j++) {
            cin >> innerCall[i][j];
            highestFloor[i] = getMax(highestFloor[i], innerCall[i][j]);
            lowestFloor[i]  = getMin(lowestFloor[i], innerCall[i][j]);
        }
    }

    // 外
    int** outerCall           = nullptr;
    int** outerCallDirections = nullptr;  //
    outerCall                 = new int*[MAX_Elevator_CNT];
    outerCallDirections       = new int*[MAX_Elevator_CNT];

    int outCallCnt[MAX_Elevator_CNT];
    for (int i = 0; i < n; i++) {
        cin >> outCallCnt[i];
        outerCall[i]           = new int[outCallCnt[i] + 1];
        outerCallDirections[i] = new int[outCallCnt[i] + 1];

        for (int j = 0; j < outCallCnt[i]; j++) {
            cin >> outerCall[i][j] >> outerCallDirections[i][j];
            highestFloor[i] = getMax(highestFloor[i], outerCall[i][j]);
            lowestFloor[i]  = getMin(lowestFloor[i], outerCall[i][j]);
        }
    }

    // 待
    int f, d;
    cin >> f >> d;

    // 原時間計算
    int timeRec[MAX_Elevator_CNT];
    for (int i = 0; i < n; i++) {
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

            timeRec[i] = getMin(time_up, time_down);
        } else
            timeRec[i] = getWaitingTime(ElevatorFloors[i], ElevatorDirections[i], 
										highestFloor[i], lowestFloor[i],
										innCallCnt[i], outCallCnt[i], 
										innerCall[i], outerCall[i], outerCallDirections[i],
										timePerFloor, timePerDoorCycle);
    }

    int sum = countSum(timeRec, n);

    // 暴力嘗試每台電梯
    int bestElevatorindex = -1;
    int minimumTime       = INT_MAX;
    for (int i = 0; i < n; i++) {
        // 把待接塞進原陣列
        outerCall[i][outCallCnt[i]]  = f;
        outerCallDirections[i][outCallCnt[i]] = d;
        highestFloor[i]           = getMax(highestFloor[i], outerCall[i][outCallCnt[i]]);
        lowestFloor[i]            = getMin(lowestFloor[i], outerCall[i][outCallCnt[i]]);

        int t;
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

            t = getMin(time_up, time_down);

        } else {
            t = getWaitingTime(ElevatorFloors[i], ElevatorDirections[i],
                               highestFloor[i], lowestFloor[i], 
							   innCallCnt[i], outCallCnt[i] + 1, 
							   innerCall[i], outerCall[i], outerCallDirections[i],
							   timePerFloor, timePerDoorCycle);
		}

        int currentTime = sum - timeRec[i] + t;
        if (currentTime < minimumTime) {
            minimumTime       = currentTime;
            bestElevatorindex = i;
        }
    }

    // output
    cout << ++bestElevatorindex << "," << minimumTime << endl;

    // release the dynamically allocated memory
    for (int i = 0; i < n; i++) delete[] innerCall[i];
    delete[] innerCall;

    for (int i = 0; i < n; i++) delete[] outerCall[i];
    delete[] outerCall;

    for (int i = 0; i < n; i++) delete[] outerCallDirections[i];
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
    // 外
    if (currentDirection == 1) {
        for (int i = 0; i < outerCallCnt; i++) {

            if (currentDirection == outerCallDirections[i]) {

                if (outerCallFloors[i] > currentFloor) {
                    WaitingTime[i]= (outerCallFloors[i] - currentFloor);
                } else if (outerCallFloors[i] == currentFloor) {
                    WaitingTime[i]= 0;
                } else {
                    WaitingTime[i]= 2 * (highestFloor - lowestFloor) -
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
                if (outerCallFloors[i] < currentFloor) {
                    WaitingTime[i]= (currentFloor - outerCallFloors[i]);
                } else if (outerCallFloors[i] == currentFloor) {
                    WaitingTime[i]= 0;
                } else {
                    WaitingTime[i]= 2 * (highestFloor - lowestFloor) -
                                    (outerCallFloors[i] - currentFloor);
                }

            } else {
                WaitingTime[i]= (currentFloor - lowestFloor) +
                                (outerCallFloors[i] - lowestFloor);
            }
        }
    }

    // 內
    if (currentDirection == 1) {
        for (int i = 0; i < innerCallCnt; i++) {
            if (innerCallFloors[i] >= currentFloor) {
                WaitingTime[i+outerCallCnt]= (innerCallFloors[i] - currentFloor);
            } else {
                WaitingTime[i+outerCallCnt]= (highestFloor - currentFloor) +
                                (highestFloor - innerCallFloors[i]);
            }
        }
    }
    if (currentDirection == -1) {
        for (int i = 0; i < innerCallCnt; i++) {
            if (innerCallFloors[i] <= currentFloor) {
                WaitingTime[i+outerCallCnt]= (currentFloor - innerCallFloors[i]);
            } else {
                WaitingTime[i+outerCallCnt]= (currentFloor - lowestFloor) +
                                (innerCallFloors[i] - lowestFloor);
            }
        }
    }
    sort(WaitingTime,WaitingTime+(innerCallCnt + outerCallCnt));
    int doorCnt=0;
    int temp=0;
    for(int i=0;i<(innerCallCnt + outerCallCnt);i++){
        doorCnt+=temp;
        temp++;
        if(i>0 && WaitingTime[i-1]==WaitingTime[i]){
            temp--;
            doorCnt--;
        } 
    }

    int WaitingTimes=0;
    for(int i=0;i<(innerCallCnt + outerCallCnt);i++){
        WaitingTimes+=WaitingTime[i];
    }

    return WaitingTimes * timePerFloor + timePerDoorCycle * doorCnt;
}

int getMin(int a, int b) {
    if (a < b)
        return a;
    else
        return b;
}

int getMax(int a, int b) {
    if (a > b)
        return a;
    else
        return b;
}

int countSum(const int arr[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    return sum;
}
