#include <iostream>
#include <fstream>
using namespace std;

class Patient
{
private:
    int age; // 病人的年齡
    int arrivalTime; // 病人到達診所的時間
    int serviceTime; // 病人看診所需的時間
    int finishTime; // 病人看診結束並離開診所的時間
    int waitingTime; // 病人從到達診所到開始看診的等待時間
    int patientsInClinicCnt; // 病人到達診所時在診所裡的病人數量
public:

    // 建構子
    // a: 到達時間; s: 看診時間
    Patient(int g, int a, int s);

    // 計算看診結束時間和等待時間
    // currTime: 當前時間; startServiceTime: 病人開始看診的時間
    void computeFinishAndWaitingTime(int startServiceTime);

    // 如果病人和另一位病人年齡差異大於等於設定的閾值，返回 true
    bool hasHigherPrior(Patient* another, int threshold);
    
    // 返回病人是否已經離開診所
    bool isLeft(int currTime);

    // 設定在診所內的病人數量
    void setTotalPatients(int currPatientIdx, int nextLeftPatientIdx);

    // 輸出指定病人的資訊
    void printInformation() { cout << finishTime << ',' << waitingTime << ',' << patientsInClinicCnt << ','; };

    // 取得相關資料
    int getArrivalTime() { return arrivalTime; };
    int getServiceTime() { return serviceTime; };
    int getFinishTime() { return finishTime; };
    int getWaitingTime() { return waitingTime; };
    int getPatientsInClinicCnt() { return patientsInClinicCnt; };
};

Patient::Patient(int g, int a, int s)
{
    // 初始化
    age = g;
    arrivalTime = a;
    serviceTime = s;
    finishTime = 0;
    waitingTime = 0;
    patientsInClinicCnt = 0;
}

bool Patient::hasHigherPrior(Patient* another, int threshold)
{
    if (this->age >= another->age + threshold)
        return true;
    else
        return false;
}

void Patient::computeFinishAndWaitingTime(int startServiceTime)
{
    finishTime = startServiceTime + serviceTime;
    waitingTime = startServiceTime - arrivalTime;
}

bool Patient::isLeft(int currTime)
{
    if (currTime > arrivalTime && currTime <= finishTime)
        return false;
    else
        return true;
}

void Patient::setTotalPatients(int currPatientIdx, int nextLeftPatientIdx)
{
    patientsInClinicCnt = currPatientIdx - nextLeftPatientIdx;
}

void swapServiceOrder(Patient& a, Patient& b)
{
    Patient temp = a;
    a = b;
    b = temp;
}

void swapIdx(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

int main()
{
    // 讀取資料
    int totalPatientCnt = 0, ageThreshold = 0;
    cin >> totalPatientCnt >> ageThreshold;
    int* ages = new int[totalPatientCnt];
    for (int i = 0; i < totalPatientCnt; i++)
        cin >> ages[i];
    int* arrivalTimeList = new int[totalPatientCnt];
    for (int i = 0; i < totalPatientCnt; i++)
        cin >> arrivalTimeList[i];
    int* serviceTimeList = new int[totalPatientCnt];
    for (int i = 0; i < totalPatientCnt; i++)
        cin >> serviceTimeList[i];
    int kthPatient = 0, givenTime = 0;
    cin >> kthPatient;
    cin.ignore(); // 忽略逗號
    cin >> givenTime;

    // 創建變數
    Patient** serviceOrder = new Patient*[totalPatientCnt]; // 病人服務順序
    int* serviceOrderIdx = new int [totalPatientCnt]; // 儲存病人到達的順序
    for (int i = 0; i < totalPatientCnt; i++)
    {
        serviceOrder[i] = new Patient(ages[i], arrivalTimeList[i], serviceTimeList[i]); // 創建物件並初始化
        serviceOrderIdx[i] = i + 1;
    }

    int onServiceTime = serviceOrder[0]->getArrivalTime(); // 醫生結束看診並可為下一位病人服務的時間
    int startServiceTime = serviceOrder[0]->getArrivalTime(); // 病人開始看診的時間
    int nextLeftPatientIdx = 0; // 下一位將離開診所的病人索引
    int nextComePatientIdx = 1; // 下一位將到達診所的病人索引

    /* 
    此 while 迴圈邏輯：
    - 使用兩個索引追蹤下一位將離開和到達的病人
    - 計算病人離開時的等待時間和結束時間，並更新醫生的服務時間
    - 在醫生服務期間，如果有病人到達，內部 while 迴圈會檢查是否需要調整服務順序。如果需要，則交換順序
    - 計算病人到達時診所內的病人數量，即每當病人到達時，將 nextComePatientIdx 加 1
    */
    while (nextLeftPatientIdx < totalPatientCnt)
    {
        onServiceTime += serviceOrder[nextLeftPatientIdx]->getServiceTime(); // 更新醫生可為下一位病人服務的時間

        while (nextComePatientIdx < totalPatientCnt && serviceOrder[nextComePatientIdx]->getArrivalTime() <= onServiceTime) // 如果有病人到達且醫生正在服務其他病人
        {
            // 計算診所內的病人數量
            serviceOrder[nextComePatientIdx]->setTotalPatients(nextComePatientIdx, nextLeftPatientIdx);

            // 調整目前等候病人的服務順序
            int adjustIdx = 0;
            for (int i = nextComePatientIdx - 1; i > nextLeftPatientIdx; i--)
            {
                if (serviceOrder[nextComePatientIdx - adjustIdx]->hasHigherPrior(serviceOrder[i], ageThreshold)) // 檢查優先權
                {
                    // 後來的病人有更高的優先權 -> 改變順序（交換）
                    swapServiceOrder(*serviceOrder[i], *serviceOrder[nextComePatientIdx - adjustIdx]);
                    swapIdx(serviceOrderIdx[i], serviceOrderIdx[nextComePatientIdx - adjustIdx]);
                    adjustIdx++;
                }
                else // 一旦條件不符合，停止進一步比較
                    break;
            }

            // 跳至下一位病人
            nextComePatientIdx++;
        }
        
        // 計算病人的等待時間和結束時間
        serviceOrder[nextLeftPatientIdx]->computeFinishAndWaitingTime(startServiceTime);

        // 如果沒有病人在等待，看診時間更新
        if (nextLeftPatientIdx < totalPatientCnt - 1 && serviceOrder[nextLeftPatientIdx + 1]->getArrivalTime() >= onServiceTime)
            onServiceTime = serviceOrder[nextLeftPatientIdx + 1]->getArrivalTime();
        
        // 醫生移至下一位病人
        nextLeftPatientIdx++;
        startServiceTime = onServiceTime;
    }

    // 計算在指定時間內診所內的病人數量並查找指定病人在重新排序後的索引
    int patientsCntT = 0;
    int WTFPatientIdx = 0;
    for (int i = 0; i < totalPatientCnt; i++)
    {
        if (!serviceOrder[i]->isLeft(givenTime)) // 如果病人尚未離開，即仍在診所
            patientsCntT++;

        if (serviceOrderIdx[i] == kthPatient) // 通過查找到達索引來找到指定病人
            WTFPatientIdx = i;
    }

    // 輸出結果
    serviceOrder[WTFPatientIdx]->printInformation();
    cout << patientsCntT;

    return 0;
}