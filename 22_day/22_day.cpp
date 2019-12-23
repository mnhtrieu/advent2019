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
const ll CARDS = 119315717514047LL;
#define MOD CARDS
// #define CARDS 10
// #define CARDS 10007
//==============================================================================
namespace part1{
vector<ll> reverse(vector<ll> cards){
  reverse(cards.begin(), cards.end());
  return cards;
}
vector<ll> cut(vector<ll> & cards, ll num){
  vector<ll> res(CARDS);
  if(num < 0) num = CARDS + num;
  for(ll i = num, j = 0; j < CARDS; ++i, ++j) res[j] = cards[i%CARDS];
  return res;
}

vector<ll> increment(vector<ll> & cards, ll num){
  vector<ll> res(CARDS);
  for(ll i = 0, j = 0; j < CARDS; i+=num, ++j) res[i % CARDS] = cards[j];
  return res;
}
}
//==============================================================================

namespace part2{

}
//==============================================================================
//==============================================================================

// using namespace part1;

void solve_1(vector<string> && in);
void solve_2(vector<string> && in);

inline ll mod(ll i, ll n=CARDS){
  if(i < 0) i = n + (i%CARDS);
  else i %= n;
  return i;
}

ll mulmod(ll a, ll b) { 
    ll res = 0; 
    a = mod(a,CARDS); 
    while (b) { 
      if (b & 1) res = mod(res + a);
      a = mod(2 * a);
      b >>= 1; 
    } 
    return mod(res); 
}

inline ll mpow(ll b,ll ex=CARDS-2){
  if(b==1)return 1;
  ll r=1;
  while(ex){
    if(ex&1)r=mulmod(r,b);
    ex>>=1;
    b=mulmod(b,b);
  }
  return r;
}

// rychle modularni umocnovani v case log(exp)
ll ipowMod(ll base, ll exp) {
  ll result = 1;
  while (exp)
  {
    if (exp & 1) result = mulmod(result, base);
    exp >>= 1;
    base = mulmod(base,base);
  }

  return result;
}


int main(){
  ios::sync_with_stdio(0);cin.tie(0);

  vector<string> in;
  string str;

  while(getline(cin, str)) in.PB(str);

  // solve_1(std::move(in));
  solve_2(std::move(in));
  return 0;
}

void solve_2(vector<string> && in){
  pair<ll,ll> deck = {0,1}; // (offset, increment)
  F(in.size()){
    string str = in[i];
    size_t pos = str.find_last_of(' ');
    if(str.substr(pos).find("stack") != string::npos) {
      deck.bb = mod(deck.bb*-1, CARDS);
      deck.aa = mod(deck.aa + deck.bb, CARDS);
    }
    else {
      ll num = atoi(str.substr(pos+1).c_str());
      string op = str.substr(0, pos);
      if(op == "cut") {
        bool flag = false;
        if(num < 0) { flag = true; num = abs(num); }
        deck.aa += mulmod(deck.bb, num) * (flag ? -1 : 1);
        deck.aa = mod(deck.aa, CARDS);
      }
      else if(op == "deal with increment") deck.bb = mulmod(deck.bb, mpow(num));

    }
  }
  ll iterations = 101741582076661;
  ll tmp = mpow(mod(1-deck.bb, CARDS));
  deck.bb = ipowMod(deck.bb, iterations);
  deck.aa = mod(mulmod(mulmod(deck.aa, mod(1 - deck.bb)), tmp));
  cout << mod(deck.aa + deck.bb * 2020, CARDS) << endl;
}




void solve_1(vector<string> && in){
  vector<ll> cards(CARDS);
  F(CARDS) cards[i] = i;
  
  while(true){
    F(in.size()){
      string str = in[i];
      size_t pos = str.find_last_of(' ');
      if(str.substr(pos).find("stack") != string::npos) cards = part1::reverse(cards);
      else {
        ll num = atoi(str.substr(pos+1).c_str());
        string op = str.substr(0, pos);
        if(op == "cut") cards = part1::cut(cards, num);
        else if(op == "deal with increment") cards = part1::increment(cards, num);
      }
    }
    break;
    // if(cards[0] == 0 && cards[1] == 1 && cards[119315717514046] == 119315717514046) break;
  }

  set<ll> test;
  F(CARDS){
    if(cards[i] == 2019) { cout << i << endl; break; }
  }
}
