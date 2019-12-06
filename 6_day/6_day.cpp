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

ll bfs(map<string, vector<string>> & m){
  queue<pair<string, ll>> q;
  unordered_map<string, bool> vis;
  q.push({"YOU", 0});
  while(!q.empty()){
    pair<string, ll> front = q.front(); q.pop();
    vis[front.aa] = true;
    for(auto & i: m[front.aa]){
      if(vis[i]) continue;
      if(i == "SAN") return front.bb;
      q.push({i,front.bb+1});
    }
    //cout << "visiting " << front.aa << " from YOU it is " << front.bb << " steps" << endl;
  }
  return 0; // can't reach
}

ll dfs(map<string, vector<string>> & m){
  stack<pair<string,ll>> s;
  s.push({"COM", 0});
  ll res = 0;
  while(!s.empty()){
    pair<string,ll> front = s.top(); s.pop();
    for(const auto & i: m[front.aa]){
      s.push({i,front.bb+1});
    }
//    cout << "for " << front.aa << " counting " << front.bb << endl;
    res += front.bb;
  }
  return res;
}


int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    string str;
    map<string, vector<string>> m;
    while(cin >> str){
      size_t p = str.find(")");
      m[str.substr(0,p)].PB(str.substr(p+1,str.size()));
      // second part
      m[str.substr(p+1,str.size())].PB(str.substr(0,p));
    }
    cout << bfs(m)-1 << endl;

    return 0;
}

