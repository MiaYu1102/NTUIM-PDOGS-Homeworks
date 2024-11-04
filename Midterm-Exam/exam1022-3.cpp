#include <bits/stdc++.h>
using namespace std;

int main(){
    int n,m,a; cin>>n>>m>>a;
    int d[n+5][m+5];
    int p[n+5][m+5];

    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>d[i][j];
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>p[i][j];
        }
    }

    int ans[n+5];

    for(int i=0;i<n;i++){
        int cumulative_prob=0;
        
        vector<pair<int, int>> demand_prob_pairs(m); 
        for (int j = 0; j < m; ++j) {
            demand_prob_pairs[j] = {d[i][j], p[i][j]};
        }

        sort(demand_prob_pairs.begin(), demand_prob_pairs.end());

        for(int j=0;j<m;j++){
            cumulative_prob += demand_prob_pairs[j].second;
            if(cumulative_prob >= a){
                ans[i]=demand_prob_pairs[j].first;
                break;
            }
        }
    }

    for(int i=0;i<n-1;i++){
        cout<<ans[i]<<",";
    }
    cout<<ans[n-1];


    return 0;
}