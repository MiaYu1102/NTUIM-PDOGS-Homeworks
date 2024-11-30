#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    string ans;
    
    while (getline(cin, s)) {
        if (s == ".") break;

        // 檢查長度是否正確
        if (s.length() != 8) {
            ans += "N";
            continue;
        }

        // 檢查第一碼是否是合法的大寫字母
        if (!(s[0] >= 'A' && s[0] <= 'Z') || s[0] == 'I' || s[0] == 'O') {
            ans += "N";
            continue;
        }

        // 檢查第二到第七碼是否為合法數字且不包含數字 4
        bool isValid = true;
        int sum = 0;
        for (int i = 1; i < 7; i++) {
            if (!isdigit(s[i]) || s[i] == '4') {
                isValid = false;
                break;
            }
            sum += s[i] - '0';
        }
        
        if (!isValid) {
            ans += "N";
            continue;
        }

        // 檢查第八碼是否為數字
        if (!isdigit(s[7])) {
            ans += "N";
            continue;
        }
        sum += s[7] - '0';

        // 檢查檢查碼是否符合條件
        if ((s[0] >= 'A' && s[0] <= 'H' && sum % 10 != 0) ||
            (s[0] >= 'J' && s[0] <= 'Q' && sum % 10 != 5) ||
            (s[0] >= 'R' && s[0] <= 'Z' && sum % 10 != 9)) {
            ans += "N";
            continue;
        }

        // 如果通過所有檢查，標記為合法
        ans += "Y";
    }

    cout << ans;
    return 0;
}