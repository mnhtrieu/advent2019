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
  ll i, res = 0;
  while(cin >> i){
    do{
      res += i = (i/3)-2; 
    } while((i/3)-2 > 0);
  }
  cout << res << endl;
  return 0;
}

