#include <climits>
#include <iostream>
using namespace std;

const int MAX_PASSENGER_CNT = 18;

void getWaitingTimes(int highestFloor, int lowestFloor, int passengerCnt,
                     int currentFloor, int currentDirection,
                     const int passengerFloors[],
                     const int passengerDirections[], int waitingTimes[]);

int getMin(int a, int b);
int getMax(int a, int b);

int countSum(const int arr[], int n);

int main() {
    // read data
    int floorCnt, passengerCnt;
    cin >> floorCnt >> passengerCnt;

    int currentFloor;
    cin >> currentFloor;

    // init
    int passengerFloors[MAX_PASSENGER_CNT] = {0};
    int passengerDirections[MAX_PASSENGER_CNT] = {0};
    int waitingTimes_down[MAX_PASSENGER_CNT] = {0};
    int waitingTimes_up[MAX_PASSENGER_CNT] = {0};

    int highestFloor = INT_MIN;
    int lowestFloor = INT_MAX;

    for (int i = 0; i < passengerCnt; ++i)
    {
        cin >> passengerFloors[i] >> passengerDirections[i];
        highestFloor = getMax(highestFloor, passengerFloors[i]);
        lowestFloor = getMin(lowestFloor, passengerFloors[i]);
    }

    // calculate the waiting times of all passengers
    // up
    getWaitingTimes(highestFloor, lowestFloor, passengerCnt, currentFloor, 1,
                    passengerFloors, passengerDirections, waitingTimes_up);
    // down
    getWaitingTimes(highestFloor, lowestFloor, passengerCnt, currentFloor, -1,
                    passengerFloors, passengerDirections, waitingTimes_down);

    // count sum and print
    int TimeSum_up = countSum(waitingTimes_up, passengerCnt);
    int TimeSum_down = countSum(waitingTimes_down, passengerCnt);

    cout << getMin(TimeSum_up, TimeSum_down);

    return 0;
}

void getWaitingTimes(int highestFloor, int lowestFloor, int passengerCnt,
                     int currentFloor, int currentDirection,
                     const int passengerFloors[],
                     const int passengerDirections[], int waitingTimes[]) {
    
    // Handle out-of-bounds situations
    if (currentFloor > highestFloor && currentDirection == 1) {
        currentDirection *= -1;
    }
    else if (currentFloor < lowestFloor && currentDirection == -1) {
        currentDirection *= -1;
    }
    
    if (currentDirection == 1) {
        for (int i = 0; i < passengerCnt; i++)
        {
            if (currentDirection == passengerDirections[i])
            {
                if (passengerFloors[i] > currentFloor) {
                    waitingTimes[i] = (passengerFloors[i] - currentFloor);
                }
                else if (passengerFloors[i] == currentFloor) {
                    waitingTimes[i] = 0;
                }
                else {
                    waitingTimes[i] = 2 * (highestFloor - lowestFloor) -
                                      (currentFloor - passengerFloors[i]);
                }

            }
            else
            {
                waitingTimes[i] = (highestFloor - currentFloor) +
                                  (highestFloor - passengerFloors[i]);
            }
        }
    }
    if (currentDirection == -1) {
        for (int i = 0; i < passengerCnt; i++)
        {
            if (currentDirection == passengerDirections[i])
            {
                if (passengerFloors[i] < currentFloor) {
                    waitingTimes[i] = (currentFloor - passengerFloors[i]);
                }
                else if (passengerFloors[i] == currentFloor) {
                    waitingTimes[i] = 0;
                }
                else {
                    waitingTimes[i] = 2 * (highestFloor - lowestFloor) -
                                      (passengerFloors[i] - currentFloor);
                }

            }
            else
            {
                waitingTimes[i] = (currentFloor - lowestFloor) +
                                  (passengerFloors[i] - lowestFloor);
            }
        }
    }
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