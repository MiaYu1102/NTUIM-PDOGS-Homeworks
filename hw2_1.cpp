#include<bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int n,m; cin>>n>>m;
    int a[n+5][n+5];
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            a[i][j]=0;
        }
    }
    for(int k=1;k<=m;k++){
        int i,j; cin>>i>>j;
        a[i][j]=1;
    }
    //find ans 1
    int ans1=-1;
    for(int i=1;i<=n;i++){
        int temp=0;
        for(int j=1;j<=n;j++){
            temp+=a[j][i];
        }
        ans1=max(ans1,temp);
    }

    //find ans 2
    int ans2=-1;
    for(int i=1;i<=n;i++){
        int temp=0;
        for(int j=1;j<=n;j++){
            temp+=a[i][j];
        }
        ans2=max(ans2,temp);
    }

    cout<<ans1<<","<<ans2;
    return 0;
}