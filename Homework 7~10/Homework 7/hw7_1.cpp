#include <iostream>
using namespace std;

class Country 
{
private:
    int gold;   // number of gold medals
    int silver; // number of silver medals
    int bronze; // number of bronze medals
public:
	
    // constructor
    // g: gold medals, s: silver medals, b: bronze medals
    Country();
    Country(int g, int s, int b); 
    
    // return true is the calling object should be ranked 
    // higher than "another" or false otherwise
    bool isRankedHigherThan(const Country& another) const;
    
    // increment the member variables according to the parameters
    // g: gold medals, s: silver medals, b: bronze medals
    void incrementMedals(int g, int s, int b); 
};

Country::Country()
{
    gold = 0;
    silver = 0;
    bronze = 0;
}
Country::Country(int g, int s, int b)
{
    gold = g;
    silver = s;
    bronze = b;
}

bool Country::isRankedHigherThan(const Country& another) const
{
    if (gold != another.gold) return gold > another.gold;
    if (silver != another.silver) return silver > another.silver;
    return bronze > another.bronze;
}

void Country::incrementMedals(int g, int s, int b)
{
    gold += g;
    silver += s;
    bronze += b;
}


int main() {
    int n, k;
    cin >> n >> k; // n: 國家數量, k: 要更新獎牌數的國家排名

    // 讀取排名第 k 名的國家所增加的金、銀、銅牌數
    int addGold, addSilver, addBronze;
    cin >> addGold >> addSilver >> addBronze;

    Country countries[105];

    // 讀取每個國家的初始獎牌數，並創建 Country 物件存入向量
    for (int i = 0; i < n; ++i) {
        int g, s, b;
        cin >> g >> s >> b;
        countries[i] = Country(g, s, b);
    }

    // 對第 k 名國家增加獎牌
    countries[k - 1].incrementMedals(addGold, addSilver, addBronze);
    
    // 計算該國的新排名
    int newRank = k;
    for (int i = k-2; i >= 0; --i) {
        if (countries[k - 1].isRankedHigherThan(countries[i])) {
            --newRank;
        }
        else break;
    }
    
    // 輸出新排名
    cout << newRank << endl;

    return 0;
}

