#include<bits/stdc++.h>
using namespace std;

int main(){
    int n,m,q; cin>>n>>m>>q;

    vector<int> a[n+1];
    for(int i=0;i<m;i++){  //修改
        int u,v; cin>>u>>v;
        a[u].push_back(v);
        a[v].push_back(u);

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
    for(int i=1;i<=q+1;i++){
        int x=p[i-1];
        int y=p[i];

        auto it = find(a[x].begin(), a[x].end(), y);
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
        }
    }

    if(isConnected) cout<<sum;
   
    return 0;
}