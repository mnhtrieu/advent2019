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
//---------------------------------------
void part1(){
  ll w = 25; // width
  ll h = 6; // height
  ll res = INT_MAX;
  char c;
  map<char, ll> res_map;
  while(!cin.eof()){
    map<char,ll> m;
    F(h*w){
      cin >> c;
      m[c] ++;
    }
    if(m['0'] > 0 && m['0'] < res){
      res_map = m;
      res = m['0'];
    }
  }
  cout << res_map['1'] * res_map['2'] << endl;
}
//---------------------------------------
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    char c;
    ll w = 25; // width
    ll h = 6; // height

    vector<vector<char>> m;
    m.resize(h);
    F(h) m[i].resize(w);
    F(h) FF(w) m[i][j] = '3';
    while(!cin.eof()){
      F(h){
        FF(w){  
          cin >> c;
          if(m[i][j] == '2') m[i][j] = c;
          else if(m[i][j] == '3') m[i][j] = c;
        }
      }
    }

    F(h){
      FF(w){
        //cout << m[i][j];
        cout << (m[i][j] == '1' ? (char)219 : ' ');
      }
      cout << endl;
    }
    return 0;
}

