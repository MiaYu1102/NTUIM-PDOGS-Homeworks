#include<bits/stdc++.h>
using namespace std;

int main(){
    int n,m,q; cin>>n>>m>>q;
    int a[n][n];
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin>>a[i][j];
        }
    }
    int h[n];
    for(int i=0;i<n;i++) cin>>h[i];
    int p[q+2];
    p[0]=1;
    for(int i=1;i<=q;i++) cin>>p[i];
    p[q+1]=1;
    
    /*
    cout<<"p[]=";
    for(int i=0;i<=q+1;i++){
        cout<<p[i]<<",";
    }
    cout<<endl;
    */

    //mock
    bool isConnected=true;
    bool isFirst=true;
    int sum=0;
    for(int i=1;i<=q+1;i++){
        int x=p[i-1];
        int y=p[i];
        if(a[x-1][y-1]==0){
            isConnected=0;
            if(isFirst){
                isFirst=0;
                cout<<x<<","<<y;
            }
            else{
                cout<<";"<<x<<","<<y;
            }
        }
        else{
            sum+=h[x-1];
        }
    }

    if(isConnected) cout<<sum;
   
    return 0;
}