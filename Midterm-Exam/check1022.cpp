#include <bits/stdc++.h>
using namespace std;

struct Item{
    int index;
    int price;
    int volume;
    string name;
    int result;
};

bool compareItems(const Item& a, const Item& b) {
    int a_value = a.price * a.volume;
    int b_value = b.price * b.volume;

    if (a_value != b_value) {
        return a_value < b_value; // 先依據 price * volume 排序
    } else {
        return a.name < b.name;   // 如果相同，則依據 name 字典序排序
    }
}

bool compareIndex(const Item& a, const Item& b) {
    return a.index < b.index; 
}

int main(){
    int n,m,a,b; cin>>n>>m>>a>>b;
    //計算採購量(p3)
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
    //
    int v[n+5];
    
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
                v[i]=demand_prob_pairs[j].first;
                break;
            }
        }
    }

    for(int i=0;i<n-1;i++){
        cout<<v[i]<<",";
    }
    cout<<v[n-1]<<endl;

    Item items[n+5];
    for(int i=0;i<n;i++){
        items[i].index=i;
    }
    for(int i=0;i<n;i++){
        int pri; cin>>pri;
        items[i].price=pri;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for(int i=0;i<n;i++){
        string ItemName;
        getline(cin, ItemName);
        items[i].name=ItemName;
    }

    for(int i=0;i<n;i++){
        items[i].volume=v[i];
    }

    for(int i=0;i<n;i++){
        items[i].result=0;
    }

    sort(items,items+n,compareItems);

    for(int i=0;i<n;i++){
        int cost = items[i].volume * items[i].price;
        if(b >= cost){
            items[i].result = items[i].volume;
            b -= cost;
        }
        else{
            items[i].result = b / items[i].price;
            b -= items[i].price * items[i].result;
        }
        if(b<=0) break;
    }

    sort(items,items+n,compareIndex);
    for(int i=0;i<n-1;i++){
        cout<<items[i].result<<",";
    }
    cout<<items[n-1].result<<";";
    cout<<b;
    return 0;
}