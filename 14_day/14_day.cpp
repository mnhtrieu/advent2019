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

std::string ltrim(const std::string& s);
std::string rtrim(const std::string& s);
std::string trim(const std::string& s);

struct node{
  ll produced;
  vector<pair<ll,string>> nodes;
};

vector<pair<ll, string>> explode(string && input){
    vector<pair<ll,string>> res;
    istringstream is(input);
    for (string token; getline(is, token, ','); ) {
      string trimmed = trim(token);
      size_t idx = trimmed.find(" ");
      res.push_back({atoi(trimmed.substr(0,idx).c_str()), trimmed.substr(idx+1)});
    }

    return res;
}

map<string, ll> rec(map<string, node> & m, string str, ll n, map<string,ll> & reservoir){
  map<string, ll> res;
  for(auto & i: m[str].nodes){
    // cout << i.bb << ": NEED = " << i.aa << ", " << "can produce: " << m[i.bb].produced << endl;
    // basic unit
    map<string, ll> tmp;
    if(m[i.bb].nodes.size() == 1 && m[i.bb].nodes[0].bb == "ORE") {
      // cout << "sending: " << n << endl;
      res[i.bb] += n*i.aa;
    }
    else {
      ll need = n*i.aa;
      if(reservoir[i.bb] > 0) {
        if(need > reservoir[i.bb]) { need -= reservoir[i.bb]; reservoir[i.bb] = 0; }
        else{ reservoir[i.bb] -= need; continue; }
      }
      ll times = ceil((double)(need) / m[i.bb].produced);
      if(times * m[i.bb].produced > need) reservoir[i.bb] += times * m[i.bb].produced - need; // adding to reservoir
      tmp = rec(m, i.bb, times, reservoir);
      // cout << "sending: " << times*n << endl;
    }
    for(auto & i: tmp) res[i.first] += i.bb;
  }
  return res;
}

bool isUnit(node & n){
  return (n.nodes.size() == 1 && n.nodes[0].bb == "ORE");
}


ll before_rec(map<string, node> & m, ll fuel){
  map<string,ll> reservoir;
  map<string, ll> res = rec(m, "FUEL",fuel, reservoir);
  ll ores = 0;
  for(auto & i: res){
    if(!isUnit(m[i.aa])) continue;
    ll num = i.bb, prod = m[i.aa].produced;
    if(i.bb % prod == 0) num = i.bb;
    else num = num + prod - (num%prod);
    //cerr << num  << "(" << i.bb << ")" << " * " << i.first << endl;
    ll tmp = m[i.aa].nodes[0].aa;
    ores += ceil(num / (double)prod)*tmp;
  }
  return ores;
}

int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    string str;
    map<string, node> m;
    while(getline(cin, str)){
      size_t pos = str.find("=>");
      string input = str.substr(0, pos-1);
      string output = trim(str.substr(pos+3));
      size_t idx = output.find(" ");
      ll produced = atoi(output.substr(0, idx).c_str());
      string item = output.substr(idx+1);
      vector<pair<ll,string>> v = explode(move(input));

      //graph
      m[item].produced = produced;
      m[item].nodes = v;
    }

    ll res = before_rec(m,1);
    cout << "Need total of " << res << " ores for 1 fuel" << endl;


    int bot = 1, top = INT_MAX;
    while(bot < top) {
      ll mid = (bot+top+1)/2;
      ll res = before_rec(m, mid);
      if (res >= 1000000000000) top = mid-1;
      else bot = mid;
    }
    cout << "Can make " << bot << " FUELs" << endl;
    return 0;
}


const std::string WHITESPACE = " \n\r\t\f\v";

std::string ltrim(const std::string& s) {
	size_t start = s.find_first_not_of(WHITESPACE);
	return (start == std::string::npos) ? "" : s.substr(start);
}

std::string rtrim(const std::string& s) {
	size_t end = s.find_last_not_of(WHITESPACE);
	return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}

std::string trim(const std::string& s){
	return rtrim(ltrim(s));
}