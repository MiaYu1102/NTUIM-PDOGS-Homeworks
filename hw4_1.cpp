#include<bits/stdc++.h>
using namespace std;

int main(){
    int n,k,g,s,b; cin>>n>>k>>g>>s>>b;
    int a[n]={0};
    int target=g*10000+s*100+b;
    for(int i=0;i<n;i++){
        int x,y,z; cin>>x>>y>>z;
        a[i]=x*10000+y*100+z;
    }
    sort(a,a+n,greater<int>());
    target+=a[k-1];
    a[k-1]=-1;
    sort(a,a+n,greater<int>());
    int cnt=1;
    for(int i=0;i<n-1;i++){
        if(a[i]<target) break;
        cnt++;
    }
    cout<<cnt;
    return 0;
}