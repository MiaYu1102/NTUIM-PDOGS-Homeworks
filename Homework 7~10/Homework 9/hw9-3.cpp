#include <cctype>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
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
    void AddMedal(int g, int s, int b, int t);
    bool operator<(const Country& cty) const;

    string GetID() const { return ID; }
    string GetName() const { return print_name; }
    int GetGold() const { return gold; }
    int GetSilver() const { return silver; }
    int GetBronze() const { return bronze; }
};

// Default constructor
Country::Country()
    : ID(""), print_name(""), gold(0), silver(0), bronze(0),
      last_gold_time(0){};

// Parameterized constructor
Country::Country(string ID, string print_name)
    : ID(ID), print_name(print_name), gold(0), silver(0), bronze(0),
      last_gold_time(0){};

void Country::AddMedal(int g, int s, int b, int t) {
    gold += g;
    silver += s;
    bronze += b;

    // 更新 last_gold_time（假設這裡傳入的 g > 0 意味著有金牌新增）
    if (g > 0) {
        last_gold_time = t;
    }
}

// Overload < operator for comparison
bool Country::operator<(const Country& cty) const {
    // Compare by gold medals
    if (gold != cty.gold) {
        return gold < cty.gold;
    }
    // Compare by silver medals if gold is the same
    if (silver != cty.silver) {
        return silver < cty.silver;
    }
    // Compare by bronze medals if gold and silver are the same
    if (bronze != cty.bronze) {
        return bronze < cty.bronze;
    }
    // Compare by last gold time if all medals are the same
    return last_gold_time > cty.last_gold_time;
}

// function
void Sort(Country*& countries, int size);
void PrintTopThree(Country* countries);
bool isNameExist(Country* countries, int size, const string& name);
string AdjustName(string name, bool needToLower);
void expandArray(Country*& countries, int& capacity);

int main() {
    // 引入txt
    string file_address;
    cin >> file_address;
    ifstream inFile(file_address);
    if (!inFile) {
        cerr << "Error opening file." << endl;
        return 1;
    }

    // 創建動態陣列
    int capacity = 100; // Initial capacity
    int size = 0;       // Current number of elements
    Country* countries = new Country[capacity];

    // 讀取內容
    string line;
    int time = 0;
    while (getline(inFile, line)) {
        stringstream ss(line);
        time++;
        string country_name;
        int medal_type = 1;
        bool needToLower = 0;

        while (getline(ss, country_name, ',')) {
            needToLower = 0;
            country_name = AdjustName(country_name, needToLower);
            needToLower = 1;
            string adjust_country = AdjustName(country_name, needToLower);

            bool exists = isNameExist(countries, size, adjust_country);
            if (!exists) {
                // 擴充動態陣列
                if (size >= capacity) {
                    expandArray(countries, capacity);
                }
                // 塞入陣列
                countries[size] = Country(country_name, adjust_country);
                size++;
            }
            // 找到國家後更新獎牌數
            for (int i = 0; i < size; i++) {
                if (countries[i].GetName() == adjust_country) {
                    countries[i].AddMedal(medal_type == 1, medal_type == 2,
                                          medal_type == 3, time);
                    break;
                }
            }
            medal_type++;
        }
    }

    // 排序
    Sort(countries, size);

    // 輸出
    PrintTopThree(countries);

    delete[] countries;
    inFile.close();
    return 0;
}

void Sort(Country*& countries, int size) {
    for (int i = 1; i < size; i++) {
        Country key = countries[i];
        int j = i - 1;

        while (j >= 0 && countries[j] < key) {
            countries[j + 1] = countries[j];
            j--;
        }
        countries[j + 1] = key;
    }
}

void PrintTopThree(Country* countries) {
    for (int i = 0; i < 3; i++) {
        cout << countries[i].GetID() << ":" << countries[i].GetGold() << ","
             << countries[i].GetSilver() << "," << countries[i].GetBronze()
             << endl;
    }
}

// 比對名稱是否存在
bool isNameExist(Country* countries, int size, const string& name) {
    for (int i = 0; i < size; i++) {
        if (countries[i].GetName() == name) {
            return true;
        }
    }
    return false;
}

// 將國家名稱去除空格並改為全小寫
string AdjustName(string str, bool needToLower) {

    // 去除前導空白
    auto start = str.begin();
    while (start != str.end() && isspace(*start)) {
        ++start;
    }

    // 去除後導空白
    auto end = str.end();
    do {
        --end;
    } while (end != start && isspace(*end));

    // 將有效範圍轉換為新的字串
    str = string(start, end + 1);

    // 使用 stringstream 處理中間多餘的空格
    istringstream iss(str);
    string word, result;
    while (iss >> word) {
        if (!result.empty()) {
            result += " "; // 插入單一空格
        }
        result += word;
    }
    if (needToLower) {
        for (char& c : result) {
            c = tolower(c);
        }
    }
    return result;
}

// Function to expand the dynamic array
void expandArray(Country*& countries, int& capacity) {
    int new_capacity = capacity * 2;
    Country* new_array = new Country[new_capacity];

    for (int i = 0; i < capacity; i++) {
        new_array[i] = countries[i];
    }

    delete[] countries;
    countries = new_array;
    capacity = new_capacity;
}
