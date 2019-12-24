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

namespace part1{
  ll count(map<pair<ll,ll>,char> & m, pair<ll,ll> pos){
  ll res = 0;
  if(m[{pos.aa-1,pos.bb}] == '#') res++;
  if(m[{pos.aa+1,pos.bb}] == '#') res++;
  if(m[{pos.aa,pos.bb-1}] == '#') res++;
  if(m[{pos.aa,pos.bb+1}] == '#') res++;
  return res;
  }

  void gameoflife(map<pair<ll,ll>, char> m){
    vector<string> str;
    while(true){
      map<pair<ll,ll>, char> res = m;
      FOR(y,0,5){
        FOR(x,0,5){
          ll neighbours = count(m, {x,y});
          if(m[{x,y}] == '#' && neighbours != 1) res[{x,y}] = '.';
          else if(m[{x,y}] == '.' && (neighbours == 1 || neighbours == 2)) res[{x,y}] = '#';
        }
      }
      m = res;
      string tmp;
      FOR(y,0,5) FOR(x,0,5) tmp += string(1,m[{x,y}]);
      FOR(i,0,str.size()) if(tmp == str[i]) { 
        cout << "first layout to be repeated!" << endl;
        ll res = 0, k = 0;
        FOR(y,0,5) {
          FOR(x,0,5) { 
            if(str[i][k] == '#') { res += pow(2, k);} 
            cout << str[i][k];
            k++;
          }
          cout << endl;
        }
        cout << "Biodiversity " << res << endl;
        return; 
      }
      str.PB(tmp);
    }
  }
}


namespace part2 {

ll count(map<ll, map<pair<ll,ll>, char>> & m, pair<ll,ll> pos, ll level){
  ll res = 0;
  //------ left
  if(pos.aa == 0) { if(m[level-1][{1,2}] == '#') res++; }
  else if(pos == pair<ll,ll>({3,2})) { FOR(y,0,5) if(m[level+1][{4,y}] == '#') res++; }
  else if(pos.aa != 0 && m[level][{pos.aa-1,pos.bb}] == '#') res++;
  //------ right
  if(pos.aa == 4) { if(m[level-1][{3,2}] == '#') res++; }
  else if(pos == pair<ll,ll>({1,2})) { FOR(y,0,5) if(m[level+1][{0,y}] == '#') res++; }
  else if(pos.aa != 4 && m[level][{pos.aa+1,pos.bb}] == '#') res++;
  //------ top
  if(pos.bb == 0) { if(m[level-1][{2,1}] == '#') res++; }
  else if(pos == pair<ll,ll>({2,3})) { FOR(x,0,5) if(m[level+1][{x,4}] == '#') res++; }
  else if(pos.bb != 0 && m[level][{pos.aa,pos.bb-1}] == '#') res++;
  //------ bottom
  if(pos.bb == 4) { if(m[level-1][{2,3}] == '#') res++; }
  else if(pos == pair<ll,ll>({2,1})) { FOR(x,0,5) if(m[level+1][{x,0}] == '#') res++; }
  else if(pos.bb != 4 && m[level][{pos.aa,pos.bb+1}] == '#') res++;
  
  return res;
}

void gameoflife(map<ll, map<pair<ll,ll>, char>> infinity){
  ll minLevel = 0, maxLevel = 0;
  FOR(iter, 0, 200){
    map<ll, map<pair<ll,ll>, char>> res = infinity;
    for(ll level = minLevel, upper = maxLevel; level <= upper; ++ level){
      FOR(offset, -1, 2){
        FOR(y,0,5){ 
          FOR(x,0,5){
            if(pair<ll,ll>{x,y} == pair<ll,ll>{2,2}) continue;
            ll neighbours = count(infinity, {x,y}, level+offset);
            if(infinity[level+offset][{x,y}] == '#' && neighbours != 1) res[level+offset][{x,y}] = '.';
            else if(infinity[level+offset][{x,y}] != '#' && (neighbours == 1 || neighbours == 2)) {
              res[level+offset][{x,y}] = '#';
              minLevel = min(minLevel,level+offset);
              maxLevel = max(maxLevel,level+offset);
            }
          }
        }
      }
    }
    infinity = res;
  }
  ll res = 0;
  cout << "Minlevel: " << minLevel << ", MaxLevel: " << maxLevel << endl;
  FOR(level, minLevel, maxLevel+1){
    FOR(y,0,5){ 
      FOR(x,0,5){
        if(infinity[level][{x,y}] == '#') res++;
      }
    }
  }
  cout << "Bugs: " << res << endl;
}

}// /namespace


int main(){
  ios::sync_with_stdio(0);cin.tie(0);
  map<pair<ll,ll>, char> m;
  char c;
  ll x = 0, y = 0;
  while(cin >> noskipws >> c){
    if(c == '\n') { y ++; x = 0; continue; }
    m[{x++,y}] = c;
  }
  cout << "--- PART 1 ---" << endl;
  part1::gameoflife(m);
  cout << endl;
  cout << "--- PART 2 ---" << endl;
  map<ll, map<pair<ll,ll>, char>> infinity;
  infinity[0] = m;
  part2::gameoflife(infinity);
  cout << "--------------" << endl;
  return 0;
}

