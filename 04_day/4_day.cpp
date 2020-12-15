#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using ld=double;
#define FOR(i,a,b) for(ll i=a;i<(ll)b;++i)
#define F(n) FOR(i,0,n)
#define FF(n) FOR(j,0,n)
#define aa first
#define bb second
#define PB push_back
#define EQ(a,b) (fabs(a-b)<=(fabs(a+b)*EPS))
#define MOD ((ll)(1e9+7))

int main(){
  ios::sync_with_stdio(0);cin.tie(0);
  ll res = 0;
  for(ll i = 246540; i < 787419; ++i){
    ll j = 10e4;
    ll tmp = i;
    ll prev = -1;
    bool doubled = false;
    ll doubled_num = -1;
    for(;j > 0; tmp%=j, j/=10){
      ll num = tmp/j;
      if(prev != -1 && prev > num) break;
      if(prev == num){
        if(!doubled && doubled_num == -1){
          // first double
          doubled = true;
          doubled_num = num;
        }
        else if(doubled && doubled_num == num){
          // if it's already doubled and it is part of the bigger group
          doubled = false;
        }
        else if(!doubled && doubled_num != num) {
          // not doubled, new group
          doubled = true;
          doubled_num = num;
        }
      }
      prev = num;
    }
    if(j == 0 && doubled) res ++; 
  }
  cout << res << endl;
  return 0;
}

