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

struct point{
  vector<ll> dist;
  set<ll> wires;
};

int main(){
  ios::sync_with_stdio(0);cin.tie(0);
  map<pair<ll,ll>, point> m;
  ll steps, wire = 0, res = INT_MAX;
  string in;
  while(getline(cin, in)){
    stringstream ss(in);
    pair<ll,ll> prev = {0,0};
    char w;
    ll dist = 0;
    while(ss >> w >> steps){
      char delim;
      ll x = prev.aa, y = prev.bb;
      F(steps){
        dist ++;
        if(w == 'R') x ++; else if(w == 'L') x--;
        else if(w == 'U') y++; else if(w == 'D') y--;
        if(i != steps) { 
          if(m[{x,y}].wires.insert(wire).second){
            m[{x,y}].dist.push_back(dist);

            if(m[{x,y}].wires.size() == 2){
              ll tmp = 0;
              for(auto & i: m[{x,y}].dist) tmp += i;
              res = min(res, tmp);
            } 
          }
        }
      }
      prev = {x,y};
      ss >> delim;
    }
    wire ++;
  }
  cout << res << endl;
  return 0;
}
