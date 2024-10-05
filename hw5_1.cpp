#include<bits/stdc++.h>
using namespace std;

const int N = 10000001;
vector<int> pri;
bool not_prime[N];

void EulerSieve(int n) {
  for (int i = 2; i <= n; ++i) {
    if (!not_prime[i]) pri.push_back(i);
    for (int pri_j : pri) {
      if (i * pri_j > n) break;
      not_prime[i * pri_j] = true;
      if (i % pri_j == 0) break;
    }
  }
}

int main(){
    int n; cin>>n;
    int fib[9]={2,3,5,13,89,233,1597,28657,514229};
    EulerSieve(n);
    int ans=pri.size();
    for(int i=0;i<9;i++){
        if(n<fib[i]) break;
        ans--;
    }
    cout<<ans;
    return 0;
}