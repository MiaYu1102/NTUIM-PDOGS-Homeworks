#include<iostream>
using namespace std;

int main(){
    int nodeCnt = 0;
    int** neighbors= nullptr;
    int* degrees=nullptr;
    cin >> nodeCnt;

    neighbors = new int* [nodeCnt];
    degrees = new int [nodeCnt];
    for(int i = 0; i < nodeCnt; i++)
    {
        cin >> degrees[i];
        neighbors[i] = new int[degrees[i]];
        for(int j = 0; j < degrees[i]; j++)
        cin >> neighbors[i][j];
    }
        
    // printing out the desired results
    for(int i = 0; i < nodeCnt; i++)
    {
        // cout << "Node " << i << ": ";
        for(int j = 0; j < degrees[i]; j++)
        cout << neighbors[i][j] << " ";
        cout << "\n";
    }
    
    // release the dynamically allocated memory
    for(int i = 0; i < nodeCnt; i++)
        delete [] neighbors[i];
    delete [] neighbors;
    delete [] degrees;

    return 0;
}