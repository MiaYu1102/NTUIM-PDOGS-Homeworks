#include<iostream>
#include<cmath>
#include<climits>
using namespace std;


const int MAX_MKT_CNT = 10000;
const int MAX_LOC_CNT = 10000;


int locX[MAX_LOC_CNT];
int locY[MAX_LOC_CNT];
int mktX[MAX_MKT_CNT];
int mktY[MAX_MKT_CNT];

bool isBuild=false;

int getBestFacility ( int mktCnt , int locCnt , int unitShippingCost 
, const int oprtCosts [] , const int demands [],
const bool curDCs []);


int main(){
    //init
    int mktCnt,locCnt,unitShippingCost;
    cin>>locCnt>>mktCnt>>unitShippingCost;
    
    for(int i=0;i<locCnt;i++)
        cin>>locX[i];
    for(int i=0;i<locCnt;i++)
        cin>>locY[i];

    for(int i=0;i<mktCnt;i++)
        cin>>mktX[i];
    for(int i=0;i<mktCnt;i++)
        cin>>mktY[i];

    int oprtCosts[MAX_LOC_CNT];
    for(int i=0;i<locCnt;i++)
        cin>>oprtCosts[i];
    
    int demands[MAX_MKT_CNT];
    for(int i=0;i<mktCnt;i++)
        cin>>demands[i];

    bool curDCs[MAX_LOC_CNT];
    for(int i=0;i<locCnt;i++){
        cin>>curDCs[i];
        if(curDCs[i]) isBuild=true;
    }
    
    //run getBestFacility
    int newDC=0;
    newDC=getBestFacility (mktCnt , locCnt , unitShippingCost , oprtCosts , demands,curDCs );
    cout<<newDC;
    return 0;
}

int getBestFacility(int mktCnt, int locCnt, int unitShippingCost,
 const int oprtCosts[] ,
  const int demands[], const bool curDCs[]){
    
    //儲存最近距離
    int md[mktCnt];
    for(int j=0;j<mktCnt;j++){
        md[j]=INT_MAX;
    }

    // count previous total cost
    for(int j=0;j<mktCnt;j++){
        for(int k=0;k<locCnt;k++){
            if(curDCs[k]){
                int d=abs(mktX[j]-locX[k])+abs(mktY[j]-locY[k]);
                md[j]=min(md[j],d);
            }
        }
    }

    // count total cost
    int index=0;
    int minCost=0;
    for(int i=0;i<locCnt;i++){
        if(curDCs[i]) continue;
        int nowTotalCost=0;
        //part 1
        for(int j=0;j<mktCnt;j++){
            int d=abs(mktX[j]-locX[i])+abs(mktY[j]-locY[i]);
            if(d<md[j]){
                nowTotalCost-=(md[j]-d)*demands[j]*unitShippingCost;
            }
        }
        //part 2
        nowTotalCost+=oprtCosts[i];

        //compare
        if(nowTotalCost<minCost){
            minCost=nowTotalCost;
            index=i+1;
        }
    }
    return index;
}
