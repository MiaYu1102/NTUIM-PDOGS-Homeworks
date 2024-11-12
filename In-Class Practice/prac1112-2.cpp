#include<bits/stdc++.h>
using namespace std;

int main(){
    int n; cin >> n;
    string x; cin >> x;
    transform(x.begin(), x.end(), x.begin(), ::tolower);
    
    for(int i=0; i<n; i++){
        string d; cin >> d;
        if(x == d){
            cout << 1;
            return 0;
        }
    }

    cout << 0;
    return 0;
}