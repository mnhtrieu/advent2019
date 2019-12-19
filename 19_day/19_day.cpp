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
void opt(map<ll,ll> m, function<ll()> && in, function<void(ll)> && out);
// =========================================================================

int main(){
  ios::sync_with_stdio(0);cin.tie(0);
  ll num;
  map<ll,ll> m;
  char delim;
  ll i = 0;
  while(cin >> num){ m[i++] = num; cin >> delim; }
  ll x=0,y=0;
  bool sw = false;
  map<pair<ll,ll>,char> board;
  ll cnt = 0;
  while(true){
    opt(m, [&sw, &x,&y]() -> ll { ll a = sw ? y : x; sw = !sw; return a; }, 
    [&board,&x,&y,&cnt](ll i){ if(i == 1) cnt ++; cout << (i == 1 ? '#' : '.'); });
    x ++;
    if(x == 50) { cout << '\n'; y ++; x = 0; }
    if(y == 50) break;
  }
  cout << "Part 1: " << cnt << endl;
  x = 3, y = 4; // starting point
  // ll limit = 0;
  ll ret = 0, ret2 = 0;
  while(true){
    // if(limit++ > 20) break;
    while(true){
      opt(m, [x,y,&sw]() -> ll { ll a = sw ? y : x; sw = !sw; return a; }, [&ret](ll i){ ret = i;});
      // cout << "Testing [" << x << "," << y << "] with symbol: " << (ret == 0 ? '.' : '#') << endl;
      if(ret == 1) break;
      x ++;
    }
    opt(m, [x,y,&sw]() -> ll { ll a = sw ? y-99 : x; sw = !sw; return a; }, [&ret](ll i){ ret = i;}); // left top corner
    // cout << "Testing left top corner [" << x+99 << "," << y-99 << "] with ret = " << ret2 << endl;
    opt(m, [x,y,&sw]() -> ll { ll a = sw ? y-99 : x+99; sw = !sw; return a; }, [&ret2](ll i){ ret2 = i;}); // right top corner
    // cout << "Testing right top corner [" << x+99 << "," << y-99 << "] with ret = " << ret2 << endl;
    if(ret == 1 && ret2 == 1){
      cout << "Part 2: " << x * 10000 + (y-99) << " [" << x << ", " << y-99 << "]" << endl;
      break;
    } 
    y ++;
  }
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
