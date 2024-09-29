#include<bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int m,n; cin>>m>>n;
    int a[m][n];
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            cin>>a[i][j];
        }
    }
    int sum=0;
    bool isFirst=1;
    
    if(m<=n){
        for(int i=0;i<m;i++){
            int v=-1,ind=-1;
            for(int j=0;j<n;j++){
                if(a[i][j]>v){
                    v=a[i][j];
                    ind=j;
                }
            }
            sum+=v;
            if(isFirst){
                cout<<ind+1;
                isFirst=0;
            }
            else{
                cout<<","<<ind+1;
            }
            for(int j=0;j<m;j++){
                a[j][ind]=INT32_MIN;
            }
        }
    }
    else{
        
        for(int i=0;i<n;i++){
            int v=-1,ind=-1;
            for(int j=0;j<m;j++){
                if(a[j][i]>v){
                    v=a[j][i];
                    ind=j;
                }
            }
            sum+=v;
            if(isFirst){
                cout<<ind+1;
                isFirst=0;
            }
            else{
                cout<<","<<ind+1;
            }
            for(int j=0;j<n;j++){
                a[ind][j]=INT32_MIN;
            }
        }

    }
    cout<<";"<<sum;
    return 0;
}