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

// ========================================================================= INTCODE
class INTCODE{
public:
  INTCODE(const map<ll,ll> & m, ll id): _m(m), _i(0), _base(0), 
          _out(0), _in(0), _id(id),
          _packet({0,0,0}), _boot(true) { }
  bool parse();
  bool opt();
  void receive(pair<ll,ll> p){ _q.push(p); }
  static ll idle;
  static pair<ll,ll> last;
private: 
  map<ll,ll> _m;
  ll _i, _base, _op, _a, _b, _c, _out, _in, _id;
  queue<pair<ll,ll>> _q;
  tuple<ll,ll,ll> _packet;
  bool _boot;
};
// =========================================================================
vector<INTCODE> intcodes;
ll INTCODE::idle;
pair<ll,ll> INTCODE::last;
// =========================================================================

namespace part1{
bool send(ll x, ll y, ll i){
  cout << "sending packet with {" << x << ", " << y << "} to INTCODE #" << i << endl;
  if(i == 255) { cout << y << endl; return true; }
  intcodes[i].receive({x,y});
  return false;
}
}

namespace part2{
bool send(ll x, ll y, ll i){
  cout << "sending packet with {" << x << ", " << y << "} to INTCODE #" << i << endl;
  if(i == 255) { 
    INTCODE::last = {x,y};
    return false;
  }
  intcodes[i].receive({x,y});
  return false;
}
}

// using namespace part1;
using namespace part2;


int main(){
  ios::sync_with_stdio(0);cin.tie(0);
  ll num;
  map<ll,ll> m;
  char delim;
  ll i = 0;
  while(cin >> num){ m[i++] = num; cin >> delim; }
  
  F(50) intcodes.PB(INTCODE(m,i));
  ll twice = 0;
  while(true){
    bool flag = false;
    INTCODE::idle = 0;
    F(50) if(intcodes[i].opt()) flag = true;
    
    if(flag) break; 
    if(INTCODE::idle == 50) { 
      cout << "sending" << endl;
      send(INTCODE::last.aa, INTCODE::last.bb, 0);  
      if(twice == 1){
        cout << INTCODE::last.bb << endl;
        return 0;
      }
      twice = 2;
      // cout << "IDLE FIDDLE" << endl; break; 
    }
    else twice --; 
  }
  return 0;
}


bool INTCODE::parse(){
  _op = _m[_i] % 100;
  if(_op == 99) return false;
  _a = _m[_i] / 100 % 10; _b = _m[_i] / 1000 % 10; _c = _m[_i] / 10000 % 10;
  if(_a == 0) _a = _m[_i+1];
  else if(_a == 1) _a = _i+1;
  else if(_a == 2) _a = _base+_m[_i+1];

  if(_b == 0) _b = _m[_i+2];
  else if(_b == 1) _b = _i+2;
  else if(_b == 2) _b = _base+_m[_i+2];

  if(_c == 0) _c = _m[_i+3];
  else _c = _base + _m[_i+3];
  return true;
}
bool INTCODE::opt(){
  while(_i < (ll)_m.size()){
    if(!parse()) break;
    if(_op == 1){ _m[_c] = _m[_a] + _m[_b]; _i+=4; }
    else if(_op == 2){ _m[_c] = _m[_a] * _m[_b]; _i+=4; }
    else if(_op == 3) { 
      bool end = false;
      if(_boot){ _boot = false; _m[_a] = _id; end = true; }
      else if(_q.empty()) { _m[_a] = -1; end = true; INTCODE::idle++; }
      else{
        if(_in == 0) _m[_a] = _q.front().aa;
        else _m[_a] = _q.front().bb;
        _in ++;
        if(_in == 2) { end = true; _q.pop(); _in = 0; }
      }
      _i+=2; 
      if(end) return false;
    }
    else if(_op == 4){  
      bool end = false;
      if(_out == 0) get<0>(_packet) = _m[_a];
      else if(_out == 1) get<1>(_packet) = _m[_a];
      else if(_out == 2) get<2>(_packet) = _m[_a];
      _out ++;
      if(_out == 3) { 
        _out = 0; end = true; 
        bool flag = send(get<1>(_packet), get<2>(_packet), get<0>(_packet)); 
        if(flag) return true;  
      }
      _i+=2;
      if(end) return false;
    }
    else if(_op == 5){	if(_m[_a] != 0) _i = _m[_b]; else _i+= 3; }
    else if(_op == 6){	if(_m[_a] == 0) _i = _m[_b]; else _i+= 3;	}
    else if(_op == 7){	if(_m[_a] < _m[_b]) _m[_c] = 1; else _m[_c] = 0; _i+=4; }
    else if(_op == 8){ if(_m[_a] == _m[_b]) _m[_c] = 1; else _m[_c] = 0; _i+=4; }
    else if(_op == 9){ _base += _m[_a]; _i+=2; }
  }
  return true;
}