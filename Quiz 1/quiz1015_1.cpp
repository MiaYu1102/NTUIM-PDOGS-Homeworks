#include <bits/stdc++.h>
using namespace std;

int main(){
    int x1,y1,x2,y2;
    cin>>x1>>y1>>x2>>y2;
    int a=abs(x1-x2);
    int b=abs(y1-y2);
    if(a==b) cout<<1<<",";
    else cout<<0<<",";
    cout<<a*b;
    return 0;
}