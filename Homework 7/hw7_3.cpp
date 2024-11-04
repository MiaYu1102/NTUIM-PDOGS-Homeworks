#include <iostream>
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

int main() {
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

    bool currently_serving = false;
    Patient* current_patient = nullptr; // 正在看診的病患指標
    Patient* next_to_arrive = patients + 1; // 下一位到達的病患指標
    Patient* next_to_serve = patients + 1;  // 下一位等待叫號的病患指標
    int current_time = 0;
    int target_result = -1;

    while (next_to_serve) {
        int personCnt = (next_to_arrive - next_to_serve) + currently_serving + next_to_arrive->has_arrived;

        // 在目標時間 t 計算順位
        if (current_time == target_time) target_result = personCnt;

        // 檢查是否結束看診
        if (currently_serving && current_time >= current_patient->finish_time) {
            current_patient->finish_time = current_time;
            currently_serving = false;
            current_patient = nullptr;
        }
        // 檢查是否有病患到達
        if (next_to_arrive && !next_to_arrive->has_arrived && current_time >= next_to_arrive->arrival_time) {
            next_to_arrive->has_arrived = true;
            next_to_arrive->personCnt = personCnt;

            // 根據年齡優先權排序
            Patient* ptr = next_to_arrive;
            while (ptr != next_to_serve && ptr->isOlder(*(ptr - 1), age_threshold)) {
                swapPatients(*ptr, *(ptr - 1));  // 使用自訂的 swap 函式
                ptr--;
            }

            if (ptr->id != num_patients) {
                next_to_arrive++;
            }
        }

        // 若無人在看診且有病患到達，則叫號
        if (!currently_serving && next_to_serve && next_to_serve->has_arrived) {
            current_patient = next_to_serve;

            // 更新下一位等待看診的病患
            if (next_to_serve != (patients + num_patients)) {
                next_to_serve++;
            } else {
                next_to_serve = nullptr;
            }
            
            current_patient->wait_time = current_time - current_patient->arrival_time;
            current_patient->finish_time = current_time + current_patient->service_time;
            current_patient->is_being_served = true;
            currently_serving = true;
        }

        current_time++;
    }

    // 找出指定病患的完成時間、等待時間和順位
    for (int i = 1; i <= num_patients; ++i) {
        if (patients[i].id == target_id) {
            cout << patients[i].finish_time << ",";
            cout << patients[i].wait_time << ",";
            cout << patients[i].personCnt << ",";
            break;
        }
    }

    // 如果未到達時間點，則設置目標結果為 0 或 1
    if (target_result < 0) {
        target_result = (target_time > patients[num_patients].finish_time) ? 0 : 1;
    }
    cout << target_result << endl;
}