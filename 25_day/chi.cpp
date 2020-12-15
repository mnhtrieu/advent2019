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
  INTCODE(const map<ll,ll> & m): _m(m), _i(0), _base(0) { }
  bool parse();
  void opt(function<ll()> && in, function<void(ll)> && out);
private: 
  map<ll,ll> _m;
  ll _i;
  ll _base;
  ll _op, _a, _b, _c;
};
// =========================================================================
// GAMIFYING
int main(){
  ios::sync_with_stdio(0);cin.tie(0);
  ll num;
  map<ll,ll> m;
  char delim;
  size_t i = 0;
  ifstream is("input.in");
  while(is >> num){ m[i++] = num; is >> delim; }
  INTCODE intcode(m);
  string str;
  string output;
  size_t idx = 0;
  cout << "Starting intcode" << endl;
  intcode.opt(
    [&str, &idx]() -> ll { return str[idx++]; }, 
    [&output, &str, &idx](ll i){ 
      cout << (char) i << flush;
      if(i == '\n'){
        if(output.find("Command?") != string::npos) {
          getline(cin,str);
          str += "\n";
          idx = 0;
          output.clear();
          return;
        }
      }
      output += string(1,i);
    }
  );
   
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
void INTCODE::opt(function<ll()> && in, function<void(ll)> && out){
  while(_i < (ll)_m.size()){
    if(!parse()) break;
    if(_op == 1){ _m[_c] = _m[_a] + _m[_b]; _i+=4; }
    else if(_op == 2){ _m[_c] = _m[_a] * _m[_b]; _i+=4; }
    else if(_op == 3) { _m[_a] = in(); _i+=2; }
    else if(_op == 4){ out(_m[_a]); _i+=2; }
    else if(_op == 5){	if(_m[_a] != 0) _i = _m[_b]; else _i+= 3; }
    else if(_op == 6){	if(_m[_a] == 0) _i = _m[_b]; else _i+= 3;	}
    else if(_op == 7){	if(_m[_a] < _m[_b]) _m[_c] = 1; else _m[_c] = 0; _i+=4; }
    else if(_op == 8){ if(_m[_a] == _m[_b]) _m[_c] = 1; else _m[_c] = 0; _i+=4; }
    else if(_op == 9){ _base += _m[_a]; _i+=2; }
  }
}