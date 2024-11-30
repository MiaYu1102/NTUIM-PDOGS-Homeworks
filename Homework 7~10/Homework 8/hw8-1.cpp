#include<bits/stdc++.h>
using namespace std;

int main(){
    int n,m,q; cin>>n>>m>>q;

    vector<pair<int,int>> a[n+1];

    for(int i=0;i<m;i++){  //修改
        int u,v,r; cin>>u>>v>>r;
        a[u].push_back({v,r});
        a[v].push_back({u,r});
    }
    int h[n];
    for(int i=0;i<n;i++) cin>>h[i];
    int p[q+2];
    p[0]=1;
    for(int i=1;i<=q;i++) cin>>p[i];
    p[q+1]=1;
    
    //mock
    bool isConnected=true;
    bool isFirst=true;
    int sum=0;
    int sum_d=0;
    for(int i=1;i<=q+1;i++){
        int x=p[i-1];
        int y=p[i];

        auto it = find_if(a[x].begin(), a[x].end(), [y](const pair<int, int>& p) {
            return p.first == y;
        });
        if(it == a[x].end()){ 
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
            sum_d+=it->second;
        }
    }

    if(isConnected) cout<<sum<<","<<sum_d;
   
    return 0;
}