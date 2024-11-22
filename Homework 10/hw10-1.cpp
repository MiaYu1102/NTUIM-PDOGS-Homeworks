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
    int waitingTime = -1;
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
            patients[size]->waitingTime = patient.waitingTime;
            size++;
        }
        int getSize(){ // get the size of the vector
            return size;
        }
        Patient& operator[](int idx){ // get the patient at index idx
            return *patients[idx];
        }
        void eraseBegin(){ // erase the first patient in the vector
            for(int i = 0; i < size-1; i++){
                patients[i] = patients[i+1];
            }
            size--;
        }
};

class Clinic
{
private:
    // initial data
    PatientVector patients;
    PatientVector doctorOnePatientsQueue;
    PatientVector doctorTwoPatientsQueue;
    PatientVector servedPatients;
    int patientCnt;
    int ageThreshold;
    int secondDoctorJoinTime;

    int currentTime;


    int targetPatientIdx;
    int targetTime;

    int targetTimePatientCnt;
    int targetPatientPatientCnt;

public:
    Clinic(int patientCnt, int ageThreshold, int secondDoctorJoinTime, int targetPatientIdx, int targetTime) // constructor
    {
        this->patientCnt = patientCnt;
        this->ageThreshold = ageThreshold;
        this->secondDoctorJoinTime = secondDoctorJoinTime;
        patients.reserve(patientCnt);
        doctorOnePatientsQueue.reserve(patientCnt);
        doctorTwoPatientsQueue.reserve(patientCnt);
        servedPatients.reserve(patientCnt);

        currentTime = 0;

        this->targetPatientIdx = targetPatientIdx-1;
        this->targetTime = targetTime;

        targetTimePatientCnt = 0;
        targetPatientPatientCnt = 0;
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
    void sortServedClient() // sort the served clients by their idx
    {
        // sort by the idx of served clients, from smallest to largest
        for (int i = 0; i < servedPatients.getSize(); i++)
        {
            for (int j = 0; j < servedPatients.getSize() - i - 1; j++)
            {
                if (servedPatients[j].idx > servedPatients[j + 1].idx)
                {
                    Patient temp = servedPatients[j];
                    servedPatients[j] = servedPatients[j + 1];
                    servedPatients[j + 1] = temp;
                }
            }
        }
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
        sortServedClient();
        for(int i = 0; i < servedPatients.getSize(); i++){
        }
        cout << servedPatients[targetPatientIdx].finishTime << "," << servedPatients[targetPatientIdx].waitingTime << "," << targetPatientPatientCnt << "," << targetTimePatientCnt;
    }
    void simulation(){
        while(servedPatients.getSize() < patientCnt){

            // check if the it's target time
            if(currentTime == targetTime){
                targetTimePatientCnt = 0;
                targetTimePatientCnt += doctorOnePatientsQueue.getSize();
                targetTimePatientCnt += doctorTwoPatientsQueue.getSize();
            }

            // check if there a patient arrived
            // check the first patient in the queue
            if(patients.getSize() > 0){
                if(patients[0].arrivalTime == currentTime){

                    // check if the target patient is in the clinic
                    if(patients[0].idx == targetPatientIdx){
                        targetPatientPatientCnt = 0;
                        targetPatientPatientCnt += doctorOnePatientsQueue.getSize();
                        targetPatientPatientCnt += doctorTwoPatientsQueue.getSize();
                    }

                    if(currentTime <= secondDoctorJoinTime){
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
                    servedPatients.push_back(doctorOnePatientsQueue[0]);
                    doctorOnePatientsQueue.eraseBegin();
                }
            }
            if(doctorTwoPatientsQueue.getSize() > 0){
                if(doctorTwoPatientsQueue[0].finishTime == currentTime){
                    servedPatients.push_back(doctorTwoPatientsQueue[0]);
                    doctorTwoPatientsQueue.eraseBegin();
                }
            }

            // check if theres a patient in the queue
            if(doctorOnePatientsQueue.getSize() > 0){
                if(doctorOnePatientsQueue[0].serviceBy == -1){
                    doctorOnePatientsQueue[0].serviceBy = 1;
                    doctorOnePatientsQueue[0].finishTime = currentTime + doctorOnePatientsQueue[0].serviceTime;
                    doctorOnePatientsQueue[0].waitingTime = currentTime - doctorOnePatientsQueue[0].arrivalTime;
                }
            }
            if(doctorTwoPatientsQueue.getSize() > 0){
                if(doctorTwoPatientsQueue[0].serviceBy == -1){
                    doctorTwoPatientsQueue[0].serviceBy = 2;
                    doctorTwoPatientsQueue[0].finishTime = currentTime + doctorTwoPatientsQueue[0].serviceTime;
                    doctorTwoPatientsQueue[0].waitingTime = currentTime - doctorTwoPatientsQueue[0].arrivalTime;
                }
            }

            // check if the second doctor should join
            if(currentTime == secondDoctorJoinTime){
                splitLoad();
                if(doctorTwoPatientsQueue.getSize() > 0){
                    if(doctorTwoPatientsQueue[0].serviceBy == -1){
                        doctorTwoPatientsQueue[0].serviceBy = 2;
                        doctorTwoPatientsQueue[0].finishTime = currentTime + doctorTwoPatientsQueue[0].serviceTime;
                        doctorTwoPatientsQueue[0].waitingTime = currentTime - doctorTwoPatientsQueue[0].arrivalTime;
                    }
                }
            }
            currentTime++;
        }
    }
};

int main()
{
    // data input
    int patientCnt;
    int ageThreshold;
    int secondDoctorJoinTime;
    cin >> patientCnt >> ageThreshold >> secondDoctorJoinTime;
    int* age = new int [patientCnt];
    int* arrivalTime = new int [patientCnt];
    int* serviceTime = new int [patientCnt];
    for(int i = 0; i < patientCnt; i++){
        cin >> age[i];
    }
    for(int i = 0; i < patientCnt; i++){
        cin >> arrivalTime[i];
    }
    for(int i = 0; i < patientCnt; i++){
        cin >> serviceTime[i];
    }
    int targetPatientIdx, targetTime;
    char c;
    cin >> targetPatientIdx >> c >> targetTime;

    // Clinic object, and push the clients into the clinic
    Clinic clinic(patientCnt, ageThreshold, secondDoctorJoinTime, targetPatientIdx, targetTime);
    for(int i = 0; i < patientCnt; i++){
        clinic.push_back_client(i, age[i], arrivalTime[i], serviceTime[i]);
    }

    // Clinic simulation
    clinic.simulation();

    // print the answer
    clinic.printAnswer();

    delete[] age;
    delete[] arrivalTime;
    delete[] serviceTime;
}
