#include <bits/stdc++.h>
using namespace std;

int main(){
    int x1,y1,x2,y2;
    cin>>x1>>y1>>x2>>y2;
    int a=x2-x1;
    int b=y2-y1;
    int c=9;
    if(a>0){
        if(b>0) c=1;
        if(b==0) c=8;
        if(b<0) c=7;
    }
    if(a==0){
        if(b>0) c=2;
        if(b==0) c=9;
        if(b<0) c=6;
    }
    if(a<0){
        if(b>0) c=3;
        if(b==0) c=4;
        if(b<0) c=5;
    }
    cout<<a<<","<<b<<","<<c;
    return 0;
}