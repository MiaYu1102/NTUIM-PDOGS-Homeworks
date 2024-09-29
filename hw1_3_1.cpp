#include <climits>
#include <iostream>
using namespace std;

/*
Topic: Platform transaction matching
Author: Mia
Student ID: B13705006
*/

/*
Explanation:
Although "BubbleSort" was not taught in class,
I think the pattern of using "swap" and "compare"
to find the top3 in this question is very similar to it.
Besides, using BubbleSort can make this program project more scalable,
(e.g. to find top4 or top5)
so I used it.
*/
void BubbleSort(int **a, int m) 
{
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= m - i; j++) {
            if (a[j][1] < a[j + 1][1]) {
                int temp = a[j][0];
                a[j][0] = a[j + 1][0];
                a[j + 1][0] = temp;

                temp = a[j][1];
                a[j][1] = a[j + 1][1];
                a[j + 1][1] = temp;
            }
        }
    }
}

int main() 
{
    // Step1 <Init> : input and build array
    int m, n, k, h;
    cin >> m >> n >> k >> h;

    /*
    Explanation:
    List[][0] = seller's number
    List[][1] = score
    */
    int** List = new int*[m + 1];
    for (int i = 1; i <= m; i++) {
        List[i] = new int[2];
    }
    
    for (int i = 1; i <= m; i++) {
        List[i][0] = i;
        List[i][1] = INT_MIN; // use minimum num as base state
    }
    
    int** Matrix = new int*[m + 1];
    for (int i = 1; i <= m; i++) {
        Matrix[i] = new int[n+1];
    }

    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            cin >> Matrix[i][j];

    for (int i = 1; i <= h; i++) {
        int temp;
        cin >> temp;
        List[temp][1] = 0;
        for (int j = 1; j <= n; j++) {
            if (Matrix[temp][j])
                List[temp][1] += Matrix[temp][j] - k;
        }
    }

    // Step2 <Compare>: find the top3 and ouput
    BubbleSort(List, m);

    int cnt;
    if (h < m) {
        cnt = h;
    } else {
        cnt = m;
    }
    if (cnt > 3)
        cnt = 3;

    bool isFirst = true;
    for (int i = 1; i <= cnt; i++) {
        if (isFirst) {
            cout << List[i][0];
            isFirst = false;
        } else
            cout << "," << List[i][0];
    }

    // Step3 <Release>: release memories
    for (int i = 1; i <= m; i++) {
        delete[] Matrix[i];
        delete[] List[i]; 
    }
    delete[] Matrix;
    delete[] List;

    return 0;
}

/*
Sample 1

Input
4 6 4 4
0 0 5 3 0 0
0 3 1 0 1 5
4 0 0 0 0 5
5 0 2 4 0 5
3 1 4 2

Output
3,1,4
---------------
Sample 2

Input
5 6 4 2
0 0 5 3 0 0
0 3 1 0 1 5
4 0 0 0 0 5
5 0 2 4 0 5
5 5 5 5 5 5
3 5

Output
5,3
*/