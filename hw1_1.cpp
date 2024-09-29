#include<bits/stdc++.h>
using namespace std;

int main(){
    int n,k; cin>>n>>k;
    
    if(k==1){
        cout<<1;
        for(int i=2;i<=n;i++){
            if(n%i==0) cout<<","<<i;
        }
    }
    else{
        bool arr[n+1];
        for(int i=2;i<=n;i++){
            arr[i]=1;
        }
        
        for(int i=2;i<=n;i++){
            if(arr[i]){
                for(int j=i*i;j<=n;j+=i) arr[j]=0;
            }
        }
        bool isFirst=1;
        for(int i=2;i<=n;i++){
            if(arr[i] && n%i==0){
                if(isFirst){
                    cout<<i;
                    isFirst=0;
                }
                else{
                    cout<<","<<i;
                }
            }
        }
    }

    return 0;
}