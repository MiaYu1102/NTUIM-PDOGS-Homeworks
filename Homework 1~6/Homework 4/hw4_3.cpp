#include <climits>
#include <cmath>
#include <iostream>
using namespace std;

const int MAX_MKT_CNT = 20;
const int MAX_LOC_CNT = 10;

int getBestFacility(int mktCnt, int locCnt, int unitShippingCost,
                    const int distances[][MAX_LOC_CNT], const int oprtCosts[],
                    const int demands[], const bool curDCs[]);

int getMin(int a, int b);

int main() {
    // init
    int mktCnt, locCnt, unitShippingCost;
    cin >> locCnt >> mktCnt >> unitShippingCost;

    int locX[MAX_LOC_CNT];
    int locY[MAX_LOC_CNT];
    for (int i = 0; i < locCnt; i++)
        cin >> locX[i];
    for (int i = 0; i < locCnt; i++)
        cin >> locY[i];

    int mktX[MAX_MKT_CNT];
    int mktY[MAX_MKT_CNT];
    for (int i = 0; i < mktCnt; i++)
        cin >> mktX[i];
    for (int i = 0; i < mktCnt; i++)
        cin >> mktY[i];

    int oprtCosts[MAX_LOC_CNT];
    for (int i = 0; i < locCnt; i++)
        cin >> oprtCosts[i];

    int demands[MAX_MKT_CNT];
    for (int i = 0; i < mktCnt; i++)
        cin >> demands[i];

    bool curDCs[MAX_LOC_CNT] = {0};
    curDCs[0] = 1;

    // count distances
    int distances[MAX_MKT_CNT][MAX_LOC_CNT];
    for (int i = 0; i < mktCnt; i++) {
        for (int j = 0; j < locCnt; j++) {
            distances[i][j] = abs(mktX[i] - locX[j]) + abs(mktY[i] - locY[j]);
        }
    }

    // run getBestFacility
    int newDC = 0;
    for (int i = 0; i < locCnt; i++) {
        newDC = getBestFacility(mktCnt, locCnt, unitShippingCost, distances,
                                oprtCosts, demands, curDCs);
        if (newDC == -1)
            break;
        curDCs[newDC] = 1;
    }

    // output
    for (int i = 0; i < locCnt - 1; i++) {
        cout << curDCs[i] << ",";
    }
    cout << curDCs[locCnt - 1];

    return 0;
}

int getBestFacility(int mktCnt, int locCnt, int unitShippingCost,
                    const int distances[][MAX_LOC_CNT], const int oprtCosts[],
                    const int demands[], const bool curDCs[]) {

    // count previous total cost
    int preTotalCost = 0;
    // part 1: transCost
    for (int j = 0; j < mktCnt; j++) {
        int transCost = INT_MAX;
        for (int k = 0; k < locCnt; k++) {
            if (curDCs[k])
                transCost = getMin(transCost, distances[j][k] * demands[j] * unitShippingCost);
        }
        preTotalCost += transCost;
    }
    // part 2: oprtCost
    for (int k = 0; k < locCnt; k++) {
        if (curDCs[k])
            preTotalCost += oprtCosts[k];
    }

    // count total cost
    int index = -1;
    int minCost = preTotalCost;

    for (int i = 0; i < locCnt; i++) {
        if (curDCs[i])
            continue;
        int nowTotalCost = 0;
        // part 1: transCost
        for (int j = 0; j < mktCnt; j++) {
            int transCost = INT_MAX;
            for (int k = 0; k < locCnt; k++) {
                if (curDCs[k] || k == i)
                    transCost = getMin(transCost,distances[j][k] * demands[j] * unitShippingCost);
            }
            nowTotalCost += transCost;
        }
        // part 2: oprtCost
        for (int k = 0; k < locCnt; k++) {
            if (curDCs[k] || k == i)
                nowTotalCost += oprtCosts[k];
        }
        // compare
        if (nowTotalCost < minCost) {
            minCost = nowTotalCost;
            index = i;
        }
    }
    return index;
}

int getMin(int a, int b) {
    if (a < b)
        return a;
    else
        return b;
}
