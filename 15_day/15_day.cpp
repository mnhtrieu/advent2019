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
ll maxX = INT_MIN, maxY = INT_MIN, minX = INT_MAX, minY = INT_MAX;

void printBoard(map<pair<ll,ll>,char> & board, pair<ll,ll> curr, pair<ll,ll> end){
  for(int y = maxX+2; y >= minY-2; y --){
    for(int x = minX-2; x <= maxX+2; x++){
      if(curr.aa == x && curr.bb == y) cout << 'D';
      else if(end.aa == x && end.bb == y) cout << 'X';
      else cout << board[{x,y}];
    }
    cout << endl;
  }
  cout << "_________" << endl;
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

ll convert(ll direction){
  if(direction == 0) return 1;
  else if(direction == 1) return 4;
  else if(direction == 2) return 2;
  else if(direction == 3) return 3;
  return -1;
}

ll inverse(ll direction){
  if(direction == 0) return 2;
  else if(direction == 1) return 3;
  else if(direction == 2) return 0;
  else if(direction == 3) return 1;
  return -1;
}

pair<ll,ll> move(ll x, ll y, ll direction){
  if(direction == 0) y+= 1;
  else if(direction == 1) x+= 1;
  else if(direction == 2) y-=1;
  else if(direction == 3) x-=1;

  maxX = max(x,maxX); minX = min(x,minX);
  maxY = max(y,maxY); minY = min(y,minY);
  return {x,y};
}

struct node{
  set<ll> s;
  ll from;
};

inline string pos(ll x, ll y){
  string str = "[" + to_string(x) + ", " + to_string(y) + "]";
  return str;
}

tuple<map<pair<ll,ll>,char>,ll,ll> opt(map<ll,ll> & m){
	size_t i = 0;
  ll base = 0, x = 0, y = 0, tmpX = 0, tmpY = 0;
  ll direction = 0;
  map<pair<ll,ll>, char> board;
  map<pair<ll,ll>, node> nodes;
  ll steps = 0;
  while(i < m.size()){
		ll op, a, b, c, out;
		if(!parse(m, i, base, op, a, b, c)) break;
    if(op == 1){ m[c] = m[a] + m[b]; i+=4; }
    else if(op == 2){ m[c] = m[a] * m[b]; i+=4; }
    else if(op == 3){ 
      ll j = 0;
      node & s = nodes[{x,y}];
      ll prev = direction;
      while(s.s.size() > 0 && (s.s.find(direction) != s.s.end() || direction == inverse(s.from))) {
        direction = (direction + 1) % 4;
        j++;
        if(direction == prev) break;
      }
      if(j >= 4 && direction == prev) {
        direction = inverse(s.from); 
        s.s.clear();
      }
      m[a] = convert(direction); 
      tie(tmpX, tmpY) = move(x,y,direction);
      i+=2;
    }
    else if(op == 4){  
      out = m[a];
      nodes[{x,y}].s.insert(direction);
      if(out == 0){
        board[{tmpX,tmpY}] = '#';
        direction = (direction+1)%4;
      }
      else if(out == 1){ // MOVED
        board[{x,y}] = '.';
        x = tmpX; y = tmpY;
        nodes[{x,y}].from = direction;
      }
      else if(out == 2){ // FINAL
        board[{0,0}] = 'S';
        board[{x,y}] = '.';
        // cout << "FINAL" << endl;
        x = tmpX; y = tmpY;
        if(steps++ == 1) break; // bruteforce the whole map
        nodes[{x,y}].from = direction;
        // break;
      }
      i+=2;
    }
    else if(op == 5){	if(m[a] != 0) i = m[b]; else i += 3; }
    else if(op == 6){	if(m[a] == 0) i = m[b]; else i+= 3; }
    else if(op == 7){	if(m[a] < m[b]) m[c] = 1; else m[c] = 0; i+=4; }
    else if(op == 8){ if(m[a] == m[b]) m[c] = 1; else m[c] = 0; i+=4; }
    else if(op == 9){ base += m[a]; i+=2; }
  }
  return {board,x,y};
}

void bfs(map<pair<ll,ll>, char> & board, ll eX, ll eY){
  queue<pair<pair<ll,ll>, ll>> q;
  q.push({{0,0},0});
  map<pair<ll,ll>, bool> visited;
  cout << "Doing bfs" << endl;
  while(!q.empty()){
    pair<pair<ll,ll>, ll> node = q.front(); q.pop();
    ll x = node.aa.aa, y = node.aa.bb;
    ll steps = node.bb;
    if(x == eX && y == eY) { cout << "minimum of steps: " << steps << endl; break; }
    if(board[{x+1,y}] == '.' && !visited[{x+1,y}]) q.push({{x+1,y}, steps+1});
    if(board[{x,y+1}] == '.' && !visited[{x,y+1}]) q.push({{x,y+1}, steps+1});
    if(board[{x,y-1}] == '.' && !visited[{x,y-1}]) q.push({{x,y-1}, steps+1});
    if(board[{x-1,y}] == '.' && !visited[{x-1,y}]) q.push({{x-1,y}, steps+1});
    visited[{x,y}] = true;
  }
}
void bfs2(map<pair<ll,ll>, char> & board, ll eX, ll eY){
  queue<pair<pair<ll,ll>, ll>> q;
  q.push({{eX,eY},0});
  map<pair<ll,ll>, bool> visited;
  cout << "Doing bfs" << endl;
  ll res = 0;
  while(!q.empty()){
    pair<pair<ll,ll>, ll> node = q.front(); q.pop();
    ll x = node.aa.aa, y = node.aa.bb;
    ll steps = node.bb;
    res = max(res,steps);
    if(board[{x+1,y}] == '.' && !visited[{x+1,y}]) q.push({{x+1,y}, steps+1});
    if(board[{x,y+1}] == '.' && !visited[{x,y+1}]) q.push({{x,y+1}, steps+1});
    if(board[{x,y-1}] == '.' && !visited[{x,y-1}]) q.push({{x,y-1}, steps+1});
    if(board[{x-1,y}] == '.' && !visited[{x-1,y}]) q.push({{x-1,y}, steps+1});
    board[{x,y}] = 'O';
    visited[{x,y}] = true;
  }
  cout << "Minutes: " << res << endl;
}

int main(){
  ios::sync_with_stdio(0);cin.tie(0);
  ll num;
  map<ll,ll> m;
  char delim;
  ll i = 0;
  while(cin >> num){ m[i++] = num; cin >> delim; }
  map<pair<ll,ll>, char> board; 
  ll x,y;
  tie(board,x,y)= opt(m);
  printBoard(board,{0,0}, {x,y});
  bfs(board,x,y);
  bfs2(board,x,y);
  return 0;
}

