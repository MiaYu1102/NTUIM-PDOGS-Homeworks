#include <bits/stdc++.h>
using namespace std;

main(){
    random_device rd;
    int seed=13705006;
    mt19937 gen(seed);

    int n; cin>>n;

    for(int i=0;i<7;i++){
        int t; cin>>t;
    }
    for(int i=0;i<n;i++){
        int a,b; cin>>a>>b;
    }

    for(int i=0;i<n;i++){
        int t; cin>>t;
        for(int j=0;j<t;j++){
            int p; cin>>p;
        }
    }
    int r; cin>>r;
    for(int i=0;i<r;i++){
        int s; cin>>s;
    }

    for(int i=0;i<r-1;i++){
        int k= uniform_int_distribution<int>(1,n)(gen);
        cout<<k<<",";
    }
    int k= uniform_int_distribution<int>(1,n)(gen);
    cout<<k;

    return 0;
}