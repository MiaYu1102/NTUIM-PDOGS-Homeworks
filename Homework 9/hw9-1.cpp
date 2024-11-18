#include<bits/stdc++.h>
using namespace std;

class Patient {
    public:
        int id;                // 病患編號
        int arrival_time;      // 到達時間
        int service_time;      // 看診所需時間
        int age;               // 年齡
        int wait_time;         // 等待時間
        int finish_time;       // 完成時間
        int personCnt;          // 前方有多少人在排隊

        bool has_arrived = false;       // 是否已到達
        bool is_being_served = false;   // 是否正在看診

        // 判斷當前病患是否年長於比較的病患
        bool isOlder(Patient other_patient, int age_threshold) {
            return other_patient.age + age_threshold <= age;
        }
};

// 自訂 swap 函式，用於交換兩個 Patient 物件的值
void swapPatients(Patient &a, Patient &b) {
    Patient temp = a;
    a = b;
    b = temp;
}

int main(){
    
    const int MAX_PATIENTS = 101; // 病患的最大數量
    int num_patients, age_threshold;
    cin >> num_patients >> age_threshold;

    Patient patients[MAX_PATIENTS];

    // 輸入病患的年齡
    for (int i = 1; i <= num_patients; ++i) {
        patients[i].id = i;
        cin >> patients[i].age;
    }

    // 輸入病患的到達時間
    for (int i = 1; i <= num_patients; ++i) {
        cin >> patients[i].arrival_time;
    }

    // 輸入病患的看診時間
    for (int i = 1; i <= num_patients; ++i) {
        cin >> patients[i].service_time;
    }

    int target_id, target_time;
    char delimiter;
    cin >> target_id >> delimiter >> target_time;

    
    return 0;
}