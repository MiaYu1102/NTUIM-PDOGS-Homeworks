#include<iostream>
#include<cmath>
using namespace std;


const int MAX_MKT_CNT = 20;
const int MAX_LOC_CNT = 10;


int getBestFacility ( int mktCnt , int locCnt , int unitShippingCost , const int
distances [][MAX_LOC_CNT], const int oprtCosts [] , const int demands [],
const bool curDCs []);


int main(){
    //init
    int mktCnt,locCnt,unitShippingCost;
    cin>>locCnt>>mktCnt>>unitShippingCost;
    
    int locX[MAX_LOC_CNT];
    int locY[MAX_LOC_CNT];
    for(int i=0;i<locCnt;i++)
        cin>>locX[i];
    for(int i=0;i<locCnt;i++)
        cin>>locY[i];

    int mktX[MAX_MKT_CNT];
    int mktY[MAX_MKT_CNT];
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
    for(int i=0;i<locCnt;i++)
        cin>>curDCs[i];
    

    //count distances
    int distances[MAX_MKT_CNT][MAX_LOC_CNT];
    for(int i=0;i<mktCnt;i++){
        for(int j=0;j<locCnt;j++){
            distances[i][j]=abs(mktX[i]-locX[j])+abs(mktY[i]-locY[j]);
        }
    }

    //run getBestFacility
    int newDC=0;
    newDC=getBestFacility (mktCnt , locCnt , unitShippingCost , distances,  oprtCosts , demands,curDCs );
    cout<<newDC;
    return 0;
}

int getBestFacility(int mktCnt, int locCnt, int unitShippingCost,
 const int distances[][MAX_LOC_CNT], const int oprtCosts[] ,
  const int demands[], const bool curDCs[]){
    
    // count previous total cost
    int preTotalCost=0;
    //part 1
    for(int j=0;j<mktCnt;j++){
        int c=2000000000;
        for(int k=0;k<locCnt;k++){
            if(curDCs[k])
                c=min(c,distances[j][k]*demands[j]*unitShippingCost);
        }
        preTotalCost+=c;
    }
    //part 2
    for(int k=0;k<locCnt;k++){
        if(curDCs[k])
            preTotalCost+=oprtCosts[k];
    }

    // count total cost
    int index=0;
    int minCost=preTotalCost;

    for(int i=0;i<locCnt;i++){
        if(curDCs[i]) continue;
        int nowTotalCost=0;
        //part 1
        for(int j=0;j<mktCnt;j++){
            int c=2000000000;
            for(int k=0;k<locCnt;k++){
                if(curDCs[k]||k==i)
                    c=min(c,distances[j][k]*demands[j]*unitShippingCost);
            }
            nowTotalCost+=c;
        }
        //part 2
        for(int k=0;k<locCnt;k++){
            if(curDCs[k]||k==i)
                nowTotalCost+=oprtCosts[k];
        }
        //compare
        if(nowTotalCost<minCost){
            minCost=nowTotalCost;
            index=i+1;
        }
    }
    return index;
}
