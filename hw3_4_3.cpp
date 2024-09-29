#include <bits/stdc++.h>
using namespace std;

const int MAX_ITEM_CNT = 50;
int n;
int weightH, weightS;
int H,S;

struct Item{
    int id;
    int r;
    int h;
    int s;
    bool isSelected;
};

Item items[MAX_ITEM_CNT];

void BubbleSort(){
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - i-1; j++) {
            if (items[j].r * (weightS*items[j+1].s + weightH*items[j+1].h) > items[j+1].r *(weightS*items[j].s + weightH*items[j].h)) {
               swap(items[j],items[j+1]);
            }
            else if (items[j].r * (weightS*items[j+1].s + weightH*items[j+1].h) == items[j+1].r *(weightS*items[j].s + weightH*items[j].h)&&items[j].r>items[j+1].r) {
               swap(items[j],items[j+1]);
            }
        }
    }
}

int main(){
    
    cin>>n>>weightH>>weightS>>H>>S;
    int nowH=0;
    int nowS=0;
    for(int i=0;i<n;i++){
        items[i].id=i;
    }
    for(int i=0;i<n;i++){
        cin>>items[i].r;
    }
    for(int i=0;i<n;i++){
        cin>>items[i].h;
        nowH+=items[i].h;
    }
    for(int i=0;i<n;i++){
        cin>>items[i].s;
        nowS+=items[i].s;
    }
    for(int i=0;i<n;i++){
        items[i].isSelected=1;
    }
    BubbleSort();

    int cnt=0;
    int ans[MAX_ITEM_CNT];
    for(int i=0;i<n;i++){
        ans[i]=1;
    }

    while(!(H>=nowH && S>=nowS)){ //持續減
        int num=items[cnt].id;
        ans[num]=0;
        items[cnt].isSelected=0;
        nowH-=items[cnt].h;
        nowS-=items[cnt].s;
        cnt++;
    }
    
    for(int i=0;i<n-1;i++){
        cout<<ans[i]<<",";
    }
    cout<<ans[n-1]<<";";
    int SumValue=0;
    for(int i=0;i<n;i++){
        if(items[i].isSelected){
            SumValue+=items[i].r;
        }
    }
    cout<<SumValue;
    
    return 0;
}