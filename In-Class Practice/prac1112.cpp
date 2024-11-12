#include<bits/stdc++.h>
using namespace std;

int main(){
    string s;
    getline(cin,s);
    int len = s.length();
    int cnt = 0;

    for(int i=0; i<len; i++)
        if(ispunct(s[i])) cnt++;

    cout << cnt;
    return 0;
}