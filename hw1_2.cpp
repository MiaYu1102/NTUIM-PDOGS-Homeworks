#include<bits/stdc++.h>
using namespace std;

int main(){
    //init
    int n; cin>>n;
    int a[n+1];
    priority_queue<int> pq;
    for(int i=0;i<n;i++){
        cin>>a[i];
        pq.push(a[i]);
    }
    int m; cin>>m;

    //compute
    pq.pop();
    cout<<pq.top()<<";"<<m*a[0];
    for(int i=1;i<n;i++)
        cout<<","<<m*a[i];

    return 0;
}