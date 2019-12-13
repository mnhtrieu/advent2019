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

void printGame(map<pair<ll,ll>,char> & game){
  for(int y = minY; y <= maxY; y ++){
    for(int x = minX; x <= maxX; x++){
      char c;
      ll id = game[{x,y}];
      if(id == 0) c = ' ';
      else if(id == 1) c = '|';
      else if(id == 2) { c = '#'; }
      else if(id == 3) c = '_';
      else if(id == 4) c = 'o';
      cout << c;
    }
    cout << endl;
  }
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

map<pair<ll,ll>,char> opt(map<ll,ll>  m){
	size_t i = 0;
  ll base = 0;
  ll output = 0, x = 0, y = 0, id = 0, score = 0;
  ll paddle, ball;
  map<pair<ll,ll>,char> game;
  ll blocks = 0;
  m[0] = 2;
  while(i < m.size()){
    ll op, a, b, c;
    if(!parse(m, i, base, op, a, b, c)) break;
		switch(op){
			case 1: m[c] = m[a] + m[b]; i+=4; break;
			case 2: m[c] = m[a] * m[b]; i+=4; break;
			case 3: 
        if(paddle > ball) m[a] = -1;
        else if(paddle < ball) m[a] = 1;
        i+=2;
        break;
			case 4: 
        if(output == 0) x = m[a];
        else if(output == 1) y = m[a];
        else if(output == 2) {
          if(x == -1 && y == 0){
            score = m[a];
          }
          else{
            if(m[a] == 4) ball = x;
            else if(m[a] == 3) paddle = x;
            else if(m[a] == 2) blocks ++;
            game[{x,y}] = m[a];
          }
        }
        maxX = max(x,maxX); minX = min(x,minX);
        maxY = max(y,maxY); minY = min(y,minY);
        output = (output + 1) % 3;
        i+=2; 
        //printGame(game);
        break;
			case 5:	if(m[a] != 0) i = m[b]; else i += 3; break;
			case 6:	if(m[a] == 0) i = m[b]; else i+= 3;	break;
			case 7:	if(m[a] < m[b]) m[c] = 1; else m[c] = 0; i+=4; break;
			case 8: if(m[a] == m[b]) m[c] = 1; else m[c] = 0; i+=4; break;
      case 9: base += m[a]; i+=2; break;
		}
  }
  cout << "Blocks in game: " << blocks << endl;
  cout << "Score: " << score << endl;
  return game;
}


int main(){
  ios::sync_with_stdio(0);cin.tie(0);
  ll num;
  map<ll,ll> m;
  char delim;
  ll i = 0;
  while(cin >> num){ m[i++] = num; cin >> delim; }
  map<pair<ll,ll>, char> game = opt(m);
  cout << endl;
  return 0;
}