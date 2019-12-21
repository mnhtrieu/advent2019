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

pair<pair<ll,ll>,ll> getPortal(map<pair<ll,ll>,ll> & m, ll x, ll y){
  if('A' <= m[{x+1,y}] && m[{x+1,y}] <= 'Z' ) return {{x+1,y},m[{x+1,y}]};
  else if('A' <= m[{x-1,y}] && m[{x-1,y}] <= 'Z' ) return {{x-1,y},m[{x-1,y}]};
  else if('A' <= m[{x,y+1}] && m[{x,y+1}] <= 'Z' ) return {{x,y+1},m[{x,y+1}]};
  else if('A' <= m[{x,y-1}] && m[{x,y-1}] <= 'Z' ) return {{x,y-1},m[{x,y-1}]};
  return {{0,0},'#'};
}

string getpos(pair<ll,ll> pos){
  return "[" + to_string(pos.aa) + ", " + to_string(pos.bb) + "]"; 
}

void processMap(map<pair<ll,ll>, ll> & m, ll width, ll height, map<string, pair<pair<ll,ll>, bool>> & portals){
  FOR(y,0,height){
    FOR(x,0,width){
      if(m[{x,y}] == '.'){
        ll c, c2;
        pair<ll,ll> portal;
        pair<ll,ll> portal2;
        //cout << "checking pos " << x << ", " << y << endl;
        tie(portal, c) = getPortal(m,x,y);
        if(c == '#') continue;
        tie(portal2, c2) = getPortal(m, portal.aa, portal.bb);
        string str = string(1,c) + string(1,c2);
        if(portals.find(str) != portals.end()) reverse(str.begin(), str.end());
        portals[str].aa = {x,y};
        if(x == 2 || x == width-3 || y == 2 || y == height-3) portals[str].bb = true;
        else portals[str].bb = false;

        cout << "FOUND PORTAL " << str << " at pos " << getpos({x,y}) 
        << (portals[str].bb ? " IS "  : " IS NOT ") << "outer" << endl;
        
        if(str == "AA") m[portal] = '#';
        //make_border(portal, m);
        
        
      }
    }
  }
  return;
}

string isPortal(map<string, pair<pair<ll,ll>, bool>> & portals, pair<ll,ll> pos){
  for(auto & i: portals){
    if(i.bb.aa == pos) return i.aa;
  }
  return "NONE";
}

// 7610

bool pushQueue(queue<tuple<pair<ll,ll>,ll,ll>> & q, pair<ll,ll> check, 
              set<pair<pair<ll,ll>,ll>> & visited, map<pair<ll,ll>, ll> & m, 
              map<string, pair<pair<ll,ll>, bool>> & portals, ll steps, ll level){
  //cout << "trying pos " << getpos(check) << endl;
  if(m[check] == '.' && visited.find({check, level}) == visited.end()){
    ll add = 1;
    string str = isPortal(portals, check);
    if(str == "AA") return false;
    if(str == "ZZ") { 
      if(level == 0) return true; 
      else return false;
    }
    if(str != "NONE") { 
      visited.insert({check, level});
      reverse(str.begin(),str.end()); 
      check = portals[str].aa; 
      add += 1;
      if(portals[str].bb == true) level ++;
      else {
        if(level == 0) return false;
        level --;
      }
    }
    q.push({check, steps+add, level});
    visited.insert({check, level});
  }
  return false;
}
int main(){
  ios::sync_with_stdio(0);cin.tie(0);
  string str;
  map<pair<ll,ll>, ll> m;
  ll x=0,y=0,width=0,height=0;
  while(getline(cin, str)){
    stringstream ss(str);
    char c;
    while(ss >> noskipws >> c){
      m[{x++,y}] = c;
    }
    width = x;
    x = 0;
    y++;
  }
  height = y;
  map<string, pair<pair<ll,ll>, bool>> portals;
  processMap(m, width, height, portals);

  /// print map
  cout << "HEIGHT: " << height << ", WIDTH: " << width << endl; 
  F(height){
    FF(width){
      cout << (char) m[{j,i}];
    }
    cout << endl;
  }

  cout << endl;
  queue<tuple<pair<ll,ll>, ll, ll>> q;
  q.push({portals["AA"].aa,0, 0});
  set<pair<pair<ll,ll>,ll>> visited;
  visited.insert({portals["AA"].aa,0});
  ll steps = 0, level = 0;
  while(true){
    pair<ll,ll> pos, check;
    tie(pos,steps,level) = q.front(); q.pop();
    if(pushQueue(q,{pos.aa-1,pos.bb}, visited, m, portals, steps, level)) break;
    if(pushQueue(q,{pos.aa+1,pos.bb}, visited, m, portals, steps, level)) break;
    if(pushQueue(q,{pos.aa,pos.bb-1}, visited, m, portals, steps, level)) break;
    if(pushQueue(q,{pos.aa,pos.bb+1}, visited, m, portals, steps, level)) break;
  }
  cout << steps+1 << endl;
  return 0;

}

