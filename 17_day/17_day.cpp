#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using ld=double;
#define FOR(i,a,b) for(ll i=a;i<(ll)b;++i)
#define F(n) FOR(i,0,n)
#define FF(n) FOR(j,0,n)
#define EPS 1e-7
#define aa first
#define bb second
#define PB push_back
#define EQ(a,b) (fabs(a-b)<=(fabs(a+b)*EPS))
#define MOD ((ll)(1e9+7))
#define PI 3.14159265

// ========================================================================= INTCODE
bool parse(map<ll,ll> & m, ll i, ll base, ll & op, ll & a, ll & b, ll & c);
void opt(map<ll,ll>  m, function<ll()> && in, function<void(ll)> && out);
// =========================================================================

inline bool intersect(map<pair<ll,ll>,char> & board,ll x, ll y){
  return board[{x-1,y}] == '#' && board[{x+1,y}] == '#' &&
        board[{x,y+1}] == '#' && board[{x,y-1}] == '#';
}

ll intersections(map<pair<ll,ll>,char> & board,ll maxX, ll maxY){
  ll res = 0;
  FOR(y,0,maxY)
    FOR(x,0,maxX)
      if(board[{x,y}] == '#' && intersect(board,x,y)) res += x * y;
  return res;
}

void getDirection(map<pair<ll,ll>,char> & board, pair<ll,ll> pos, ll & direction){
  ll x,y; tie(x,y) = pos;
  if(direction == 0 || direction == 2){
    if(board[{x-1,y}] == '#') direction = 3;
    else if(board[{x+1,y}] == '#') direction = 1;
  }
  else if(direction == 1 || direction == 3){
    if(board[{x,y+1}] == '#') direction = 2;
    else if(board[{x,y-1}] == '#') direction = 0;
  }
}

string ch(ll prev, ll direction){
  if(prev == 0) return direction == 3 ? "L" : "R";
  else if(prev == 1) return direction == 0 ? "L" : "R";
  else if(prev == 2) return direction == 1 ? "L" : "R";
  return direction == 2 ? "L" : "R";
}

pair<ll,ll> getmove(ll direction, ll x, ll y){
  if(direction == 0) y--;
  else if(direction == 1) x++;
  else if(direction == 2) y++;
  else if(direction == 3) x--; 
  return {x,y};
}

ll occurences(string s, string p){
  ll res = 0;
  size_t pos = 0;
  while ((pos = s.find(p, pos)) != std::string::npos) {
    ++ res; pos += p.length();
  }
  return res;
}

string walkRobot(map<pair<ll,ll>,char> & board,ll maxX, ll maxY, pair<ll,ll> start){
  ll x,y;
  tie(x,y) = start;
  ll direction = 0;
  ll prev = 0;
  string str;
  while(board[{x,y}] != 'E'){
    prev = direction; getDirection(board,{x,y}, direction);
    ll steps = 0;
    while(true){
      ll tmpX, tmpY; tie(tmpX,tmpY) = getmove(direction,x,y);
      if(board[{tmpX,tmpY}] != '#' && board[{tmpX,tmpY}] != 'E')  break;
      x = tmpX; y = tmpY; steps++;
    }
    str += ch(prev, direction) + "," + to_string(steps) + ",";
  } 
  // cout << "STRING: " << str << endl;
  return str;
}

vector<string> routines(string str){
  string copy = str;
  vector<string> routines;
  string routine;
  while(str.size() > 1){
    ll i = 0;
    size_t pos = 0;
    string tmp;
    for(;; i = pos+1){
      pos = str.find(',',str.find(',',i)+1);
      string move = str.substr(i, pos-i+1);
      if(pos == string::npos) break;
      if(tmp.size() + move.size() >= 20) break;
      tmp += move;
      if(occurences(str,tmp) <= 1) break;
      routine = tmp;
    }
    pos = 0;
    // remove the found routine from the string
    while((pos = str.find(routine, pos)) != string::npos)
      str.replace(pos,routine.size(), "");
    
    pos = 0;
    // replace the main string with the routine id
    while((pos = copy.find(routine)) != string::npos)
      copy.replace(pos,routine.size(), string(1,'A' + routines.size()) + ",");

    routine[routine.size()-1] = '\n';
    routines.PB(routine);
  }
  copy[copy.size()-1] = '\n';
  routines.insert(routines.begin(), copy);
  return routines;
}

int main(){
  ios::sync_with_stdio(0);cin.tie(0);
  ll num;
  map<ll,ll> m;
  char delim;
  ll i = 0;
  while(cin >> num){ m[i++] = num; cin >> delim; }
  map<pair<ll,ll>, char> board;
  ll x=0,y=0,maxX=0,maxY=0;

  opt(m, []() -> ll { return 1; }, 
  [&board, &maxX, &maxY, &x,&y](ll i){ 
    board[{x,y}] = i;
    x ++;
    if(i == '\n') { y++; x = 0; }
    maxX = max(maxX,x);
    maxY = max(maxY,y);
  });

  cout << intersections(board,maxX,maxY) << endl;

  board[{4,12}] = 'E';
  string route = walkRobot(board,maxX,maxY,{12,28});
  vector<string> config = routines(route);
  config.PB("n\n");
  m[0] = 2;
  i = 0;
  ll j = 0;
  opt(m, [&i, &config, &j](){
    char c = config[i][j++];
    if(j == (ll)config[i].size()) i++, j=0;
    return c;
  }, [](ll i){
    if(i > 255) cout << i;
    else cout << (char)i;
  });
  return 0;
}


bool parse(map<ll,ll> & m, ll i, ll base, ll & op, ll & a, ll & b, ll & c){
  op = m[i] % 100;
  if(op == 99) return false;
  a = m[i] / 100 % 10; b = m[i] / 1000 % 10; c = m[i] / 10000 % 10;
  if(a == 0) a = m[i+1];
  else if(a == 1) a = i+1;
  else if(a == 2) a = base+m[i+1];

  if(b == 0) b = m[i+2];
  else if(b == 1) b = i+2;
  else if(b == 2) b = base+m[i+2];

  if(c == 0) c = m[i+3];
  else c = base + m[i+3];
  return true;
}
void opt(map<ll,ll>  m, function<ll()> && in, function<void(ll)> && out){
	size_t i = 0;
  ll base = 0;
  map<pair<ll,ll>,char> board;
  while(i < m.size()){
    ll op, a, b, c;
    if(!parse(m, i, base, op, a, b, c)) break;
    if(op == 1){ m[c] = m[a] + m[b]; i+=4; }
    else if(op == 2){ m[c] = m[a] * m[b]; i+=4; }
    else if(op == 3) { m[a] = in(); i+=2; }
    else if(op == 4){ out(m[a]); i+=2; }
    else if(op == 5){	if(m[a] != 0) i = m[b]; else i += 3; }
    else if(op == 6){	if(m[a] == 0) i = m[b]; else i+= 3;	}
    else if(op == 7){	if(m[a] < m[b]) m[c] = 1; else m[c] = 0; i+=4; }
    else if(op == 8){ if(m[a] == m[b]) m[c] = 1; else m[c] = 0; i+=4; }
    else if(op == 9){ base += m[a]; i+=2; }

  }
}
