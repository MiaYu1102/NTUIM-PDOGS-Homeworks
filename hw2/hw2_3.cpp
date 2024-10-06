#include <iostream>
using namespace std;

//build function
int getBiggestByReordering(int theValue);
int getSmallestByReordering(int theValue);

int main() {
    //init
    int aValue;
    cin >> aValue;

    //cout process
    while (aValue != 6174) {
        int biggest = getBiggestByReordering(aValue);
        int smallest = getSmallestByReordering(aValue);
        aValue = biggest - smallest;
        if (aValue == 6174) {
            cout << aValue;
        } else {
            cout << aValue << ",";
        }
    }
    return 0;
}

int getBiggestByReordering(int theValue) {
    int a[4];
    for (int i = 0; i < 4; i++) {
        a[i] = theValue % 10;
        theValue /= 10;
    }
    // swap
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3 - i; j++) {
            if (a[j] < a[j + 1]) {
                int t = a[j];
                a[j] = a[j + 1];
                a[j + 1] = t;
            }
        }
    }

    // assemble
    int biggest = 0;
    for (int i = 0; i < 4; i++) {
        biggest += a[i];
        biggest *= 10;
    }
    return biggest / 10;
}

int getSmallestByReordering(int theValue) {
    int a[4];
    for (int i = 0; i < 4; i++) {
        a[i] = theValue % 10;
        theValue /= 10;
    }
    // swap
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3 - i; j++) {
            if (a[j] > a[j + 1]) {
                int t = a[j];
                a[j] = a[j + 1];
                a[j + 1] = t;
            }
        }
    }

    // assemble
    int biggest = 0;
    for (int i = 0; i < 4; i++) {
        biggest += a[i];
        biggest *= 10;
    }
    return biggest / 10;
}