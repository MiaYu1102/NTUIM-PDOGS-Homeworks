#include <iostream>
#include <string>
using namespace std;

struct Patient
{
    int idx;
    int age;
    int arrivalTime;
    int serviceTime;

    int serviceBy = -1;
    int finishTime = -1;
    
};

// Implement PatientVector class
class PatientVector{
    private:
        Patient** patients;
        int size; // the number of patients in the vector
        int capacity; // the capacity of the vector
    public:
        PatientVector(){
            size = 0;
            capacity = 50;
            patients = new Patient*[capacity];
        }
        void reserve(int n){ // reserve n space for the vector
            capacity = n;
            delete[] patients;
            patients = new Patient*[capacity];
        }
        void push_back(Patient patient){ // add a patient to the end of the vector
            if(size == capacity){
                capacity *= 2;
                Patient** temp = new Patient*[capacity];
                for(int i = 0; i < size; i++){
                    temp[i] = patients[i];
                }
                delete[] patients;
                patients = temp;
            }
            patients[size] = new Patient;
            patients[size]->idx = patient.idx;
            patients[size]->age = patient.age;
            patients[size]->arrivalTime = patient.arrivalTime;
            patients[size]->serviceTime = patient.serviceTime;
            patients[size]->serviceBy = patient.serviceBy;
            patients[size]->finishTime = patient.finishTime;
            
            size++;
        }
        int getSize(){ // get the size of the vector
            return size;
        }
        Patient& operator[](int idx){ // get the patient at index idx
            return *patients[idx];
        }
        void eraseBegin(){ // erase the first patient in the vector
            if (size > 0)
            {
                delete patients[0]; // 釋放第一個病患的記憶體
                for (int i = 0; i < size-1; i++)
                {
                    patients[i] = patients[i+1];
                }
                size--;
            }
        }
};

class Clinic
{
private:
    // initial data
    PatientVector patients;
    PatientVector doctorOnePatientsQueue;
    PatientVector doctorTwoPatientsQueue;
    int patientCnt;
    int ageThreshold;

    int doctorJoinThreshold;
    bool doctorTwoJoined;    // 紀錄醫師2是否已加入

    int currentTime;

    int doctorOneCount; // 醫師1看診人數
    int doctorTwoCount; // 醫師2看診人數


public:
    int servedPatientCnt = 0;
    Clinic(int patientCnt, int ageThreshold, int doctorJoinThreshold) // constructor
    {
        this->patientCnt = patientCnt;
        this->ageThreshold = ageThreshold;
        this->doctorJoinThreshold = doctorJoinThreshold;
        patients.reserve(patientCnt);
        doctorOnePatientsQueue.reserve(patientCnt);
        doctorTwoPatientsQueue.reserve(patientCnt);

        doctorTwoJoined = false; // 初始時醫師2未加入
        currentTime = 0;

        doctorOneCount = 0;
        doctorTwoCount = 0;

    }
    void push_back_client(int idx, int age, int arrivalTime, int serviceTime) // add a patient to the clinic
    {
        Patient patient;
        patient.idx = idx;
        patient.age = age;
        patient.arrivalTime = arrivalTime;
        patient.serviceTime = serviceTime;
        patients.push_back(patient);
    }
    void splitLoad(){ // split the load between doctor 1 and doctor 2
        bool odd = true;
        PatientVector temp;
        for(int i = 0; i < doctorOnePatientsQueue.getSize(); i++){
            if(doctorOnePatientsQueue[i].serviceBy == -1){
                if(odd){
                    doctorTwoPatientsQueue.push_back(doctorOnePatientsQueue[i]);
                }
                else{
                    temp.push_back(doctorOnePatientsQueue[i]);
                }
                odd = !odd;
            }
            else{
                temp.push_back(doctorOnePatientsQueue[i]);
            }
        }
        doctorOnePatientsQueue = temp;
    }
    
    void handleSwap(int doctorIdx){ // handle the swap between the clients in the queue
        // target: the last pushed client
        // if the target is older than its previous client by ageThreshold, and the client is not served, swap them
        // keep swap until the newly joined client is not older than its previous client by ageThreshold
        if(doctorIdx == 1){
            if(doctorOnePatientsQueue.getSize() > 2){
                for(int i = doctorOnePatientsQueue.getSize() - 1; i > 0; i--)
                {
                    if(doctorOnePatientsQueue[i].age - doctorOnePatientsQueue[i-1].age >= ageThreshold && doctorOnePatientsQueue[i-1].serviceBy == -1){
                        Patient temp = doctorOnePatientsQueue[i];
                        doctorOnePatientsQueue[i] = doctorOnePatientsQueue[i-1];
                        doctorOnePatientsQueue[i-1] = temp;
                    }
                    else{
                        break;
                    }
                }
            }
        }
        else if(doctorIdx == 2){
            if(doctorTwoPatientsQueue.getSize() > 2){
                for(int i = doctorTwoPatientsQueue.getSize() - 1; i > 0; i--)
                {
                    if(doctorTwoPatientsQueue[i].age - doctorTwoPatientsQueue[i-1].age >= ageThreshold && doctorTwoPatientsQueue[i-1].serviceBy == -1){
                        Patient temp = doctorTwoPatientsQueue[i];
                        doctorTwoPatientsQueue[i] = doctorTwoPatientsQueue[i-1];
                        doctorTwoPatientsQueue[i-1] = temp;
                    }
                    else{
                        break;
                    }
                }
            }
        }
    }
    void printAnswer(){ // print the answer
        cout << doctorOneCount << "," << doctorTwoCount; // 輸出D1和D2
    }
    void simulation(){
        while(servedPatientCnt < patientCnt){

            // check if there a patient arrived
            // check the first patient in the queue
            if(patients.getSize() > 0){
                if(patients[0].arrivalTime == currentTime){

                    if(!doctorTwoJoined){
                        doctorOnePatientsQueue.push_back(patients[0]);
                        handleSwap(1);
                        
                    }
                    else{
                        int doctorOneLoading = doctorOnePatientsQueue.getSize();
                        int doctorTwoLoading = doctorTwoPatientsQueue.getSize();

                        // see whose load is less
                        if(doctorOneLoading <= doctorTwoLoading){
                            doctorOnePatientsQueue.push_back(patients[0]);
                            handleSwap(1);
                        }
                        else{
                            doctorTwoPatientsQueue.push_back(patients[0]);
                            handleSwap(2);
                        }
                    }
                    patients.eraseBegin();
                }
            }   
            
            
            // check if the current client is served
            if(doctorOnePatientsQueue.getSize() > 0){
                if(doctorOnePatientsQueue[0].finishTime == currentTime){
                    cerr<<"Doctor 1 served patient "<<doctorOnePatientsQueue[0].idx<<" at time "<<currentTime<<endl;
                    servedPatientCnt++;
                    doctorOneCount++; // 醫師1看診人數加1
                    doctorOnePatientsQueue.eraseBegin();
                }
            }
            if(doctorTwoPatientsQueue.getSize() > 0){
                if(doctorTwoPatientsQueue[0].finishTime == currentTime){
                    servedPatientCnt++;
                    doctorTwoCount++; // 醫師2看診人數加1
                    doctorTwoPatientsQueue.eraseBegin();
                }
            }

            // check if theres a patient in the queue
            if(doctorOnePatientsQueue.getSize() > 0){
                if(doctorOnePatientsQueue[0].serviceBy == -1){
                    doctorOnePatientsQueue[0].serviceBy = 1;
                    doctorOnePatientsQueue[0].finishTime = currentTime + doctorOnePatientsQueue[0].serviceTime;
                    
                }
            }
            if(doctorTwoPatientsQueue.getSize() > 0){
                if(doctorTwoPatientsQueue[0].serviceBy == -1){
                    doctorTwoPatientsQueue[0].serviceBy = 2;
                    doctorTwoPatientsQueue[0].finishTime = currentTime + doctorTwoPatientsQueue[0].serviceTime;
                    
                }
            }

            // check if the second doctor should join
            if(!doctorTwoJoined && doctorOnePatientsQueue.getSize()-(doctorOnePatientsQueue.getSize()!=0) >= doctorJoinThreshold){

                doctorTwoJoined = true; // 醫師2加入看診
                splitLoad();
                if(doctorTwoPatientsQueue.getSize() > 0){
                    if(doctorTwoPatientsQueue[0].serviceBy == -1){
                        doctorTwoPatientsQueue[0].serviceBy = 2;
                        doctorTwoPatientsQueue[0].finishTime = currentTime + doctorTwoPatientsQueue[0].serviceTime;
                    }
                }
            }
            currentTime++;
        }
    }
};

int main()
{
    // 輸入診所參數
    int patientCnt, ageThreshold, doctorJoinThreshold;
    cin >> patientCnt >> ageThreshold >> doctorJoinThreshold;


    // 初始化診所物件
    Clinic clinic(patientCnt, ageThreshold, doctorJoinThreshold); // 移除目標病患與時間相關參數

    // 一次輸入每個病患的年齡、到診時間與看診時間
    for (int i = 0; i < patientCnt; i++)
    {
        int age, arrivalTime, serviceTime;
        cin >> age >> arrivalTime >> serviceTime;
        clinic.push_back_client(i, age, arrivalTime, serviceTime);
    }

    // 執行模擬
    clinic.simulation();

    // 輸出結果
    clinic.printAnswer();

    return 0;
}
