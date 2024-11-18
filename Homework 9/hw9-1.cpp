#include <iostream>
#include <queue>
#include <vector>
using namespace std;

class Patient {
public:
    int id;                // 病患編號
    int arrival_time;      // 到達時間
    int service_time;      // 看診所需時間
    int age;               // 年齡
    int wait_time = 0;     // 等待時間
    int finish_time = 0;   // 完成時間
    int personCnt = 0;     // 前方有多少人在排隊

    bool has_arrived = false;       // 是否已到達
    bool is_being_served = false;   // 是否正在看診

    bool isOlder(Patient other_patient, int age_threshold) {
        return other_patient.age + age_threshold <= age;
    }
};

// 用於處理患者交換
void swapPatients(Patient &a, Patient &b) {
    Patient temp = a;
    a = b;
    b = temp;
}

int main() {
    const int MAX_PATIENTS = 101;
    int num_patients, age_threshold, V;
    cin >> num_patients >> age_threshold >> V;

    Patient patients[MAX_PATIENTS];
    for (int i = 1; i <= num_patients; ++i) {
        patients[i].id = i;
        cin >> patients[i].age;
    }
    for (int i = 1; i <= num_patients; ++i) {
        cin >> patients[i].arrival_time;
    }
    for (int i = 1; i <= num_patients; ++i) {
        cin >> patients[i].service_time;
    }

    int target_id, target_time;
    char delimiter;
    cin >> target_id >> delimiter >> target_time;

    queue<Patient*> doctor_queues[2]; // 醫生 A 和 B 的診間
    Patient* current_patient[2] = {nullptr, nullptr};
    bool currently_serving[2] = {false, false};
    Patient* next_to_arrive = patients + 1;
    Patient* next_to_serve = patients + 1;
    int current_time = 0, time_person_cnt = -1;
    bool doctor_b_joined = false;

    while (next_to_serve || currently_serving[0] || currently_serving[1]) {
        // 計算診所內的病患數
        int personCnt = (next_to_arrive - next_to_serve) + next_to_arrive->has_arrived;
        for (int d = 0; d < 2; ++d) {
            if (currently_serving[d]) personCnt++;
            personCnt += doctor_queues[d].size();
        }

        // 紀錄目標時間的人數
        if (current_time == target_time) {
            time_person_cnt = personCnt;
        }

        // 醫生完成看診
        for (int d = 0; d < 2; ++d) {
            if (currently_serving[d] && current_time >= current_patient[d]->finish_time) {
                current_patient[d]->finish_time = current_time;
                currently_serving[d] = false;
                current_patient[d] = nullptr;
            }
        }

        // 新患者到達
        if (next_to_arrive && !next_to_arrive->has_arrived && current_time >= next_to_arrive->arrival_time) {
            next_to_arrive->has_arrived = true;

            if (!doctor_b_joined || doctor_queues[0].size() <= doctor_queues[1].size()) {
                doctor_queues[0].push(next_to_arrive);
            } else {
                doctor_queues[1].push(next_to_arrive);
            }

            if (next_to_arrive != (patients + num_patients)) {
                next_to_arrive++;
            } else {
                next_to_arrive = nullptr;
            }
        }

        // 醫生 B 加入
        if (current_time == V && !doctor_b_joined) {
            doctor_b_joined = true;
            queue<Patient*> temp_queue;
            int index = 0;

            while (!doctor_queues[0].empty()) {
                Patient* patient = doctor_queues[0].front();
                doctor_queues[0].pop();

                if (index % 2 == 0) {
                    doctor_queues[1].push(patient);
                } else {
                    temp_queue.push(patient);
                }
                index++;
            }
            doctor_queues[0] = temp_queue;
        }

        // 醫生開始看診
        for (int d = 0; d < 2; ++d) {
            if (!currently_serving[d] && !doctor_queues[d].empty()) {
                current_patient[d] = doctor_queues[d].front();
                doctor_queues[d].pop();

                current_patient[d]->wait_time = current_time - current_patient[d]->arrival_time;
                current_patient[d]->finish_time = current_time + current_patient[d]->service_time;
                currently_serving[d] = true;
            }
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

    if (time_person_cnt < 0) {
        time_person_cnt = (target_time > patients[num_patients].finish_time) ? 0 : 1;
    }
    cout << time_person_cnt << endl;
    return 0;
}
