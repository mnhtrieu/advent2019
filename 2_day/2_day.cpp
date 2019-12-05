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

ll opt(vector<ll> v){
  for(size_t i = 0; i < v.size(); i+=4){
    if(v[i] == 99) break;
      
    ll left = v[i+1];
    ll right = v[i+2];
    ll pos = v[i+3];
    
    if(v[i] == 1) v[pos] = v[left] + v[right];
    else if(v[i] == 2) v[pos] = v[left] * v[right];
  }
  return v[0];
}

int main(){
  ios::sync_with_stdio(0);cin.tie(0);
  ll num;
  vector<ll> v;
  char delim;
  while(cin >> num){ v.PB(num); cin >> delim; }
  F(100){
    FF(100){
      v[1] = i;
      v[2] = j;
      if(opt(v) == 19690720){ 
        cout << 100 * v[1] + v[2] << endl;
        return 0;
      }
    }
  }
  return 0;
}

