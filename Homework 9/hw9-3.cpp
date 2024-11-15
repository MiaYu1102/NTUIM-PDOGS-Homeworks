#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
using namespace std;

class Country {
private:
    string ID;
    string print_name;
    int gold;
    int silver;
    int bronze;
    int last_gold_time;

public:
    Country();
    Country(string ID, string print_name);

    void AddMedal();

    Country operator<(const Country& cty) const;

};

//
void Sort();
void PrintTopThree();
bool isNameExist();


int main() {
    //引入txt
    string file_address;
    cin>>file_address;
    ifstream inFile(file_address);

    //讀取內容
    string line;
    while(getline(inFile, line)) {
        stringstream ss(line);
        string country;
        while (getline(ss, country, ',')){
            
        }
    }

    //排序
    Sort();

    //輸出
    PrintTopThree();

    inFile.close();
    return 0;
}

