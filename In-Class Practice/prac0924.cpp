#include<bits/stdc++.h>
using namespace std;

int main(){
    int n,t; cin>>n>>t;
    int a[n];
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    sort(a,a+n);
    int l=0;
    int r=n-1;
    while(l<r){
        int m=(l+r)/2;
        if(a[m]==t){
            cout<<1;
            return 0;
        }
        else if(a[m]>t){
            r=m;
        }
        else{
            l=m+1;
        }
    }
    if(a[l]==t) cout<<1;
    else cout<<0;
    return 0;
}