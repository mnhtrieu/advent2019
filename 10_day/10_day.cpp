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
ll count(vector<pair<ll,ll>> & asteroids, ll idx){
	pair<ll,ll> curr = asteroids[idx];
	set<double> pos;
	for(auto & i: asteroids){
		if(i == curr) continue;
		pos.insert(atan2(curr.aa - i.aa, curr.bb - i.bb));
	}
	return pos.size();
}

pair<ll,ll> station(vector<pair<ll,ll>> & asteroids){
	ll best = 0;
	pair<ll,ll> bpos = {0,0};
	F(asteroids.size()){
		ll curr = count(asteroids,i);
		if(curr > best){
			best = curr;
			bpos = {asteroids[i]};
		}
	}
	// cout << "pos: [" << bpos.aa << ", " << bpos.bb << "] has the BEST LoS of " << best << " asteroids" << endl;
	return bpos;
}

void laser(pair<ll,ll> st, vector<pair<ll,ll>> & asteroids){
	ll x, y;
	vector<tuple<double,ll,pair<ll,ll>>> tmp;
	for(auto & i: asteroids){
		if(i == st) continue;
		double angle = atan2(st.aa - i.aa, st.bb - i.bb) * 180 / PI;
		double dist = sqrt((st.aa - i.aa)*(st.aa - i.aa) + (st.bb - i.bb)*(st.bb - i.bb));
		tmp.PB({angle > 0.0 ? angle : 360.0 + angle ,dist,i});
	}
	sort(tmp.begin(), tmp.end(), [](tuple<double,ll,pair<ll,ll>> a, tuple<double,ll,pair<ll,ll>> b)-> bool { 
		return get<0>(a) > get<0>(b) || (get<0>(a) == get<0>(b) && get<1>(a) < get<1>(b));
	});
	map<pair<ll,ll>, bool> lasered;
	double prevAngle = -1;
	
	for(int idx = 0, cnt = 0; cnt != 200; ++idx){
		auto & i = tmp[idx%tmp.size()];
		x = get<2>(i).aa;
		y = get<2>(i).bb;
		if(lasered[{x,y}]) continue;
		double angle = get<0>(i);
		if(EQ(angle,prevAngle)) continue;
		lasered[{x,y}] = true;
		cnt ++;
		prevAngle = angle;
		if(idx == 1){ idx = tmp.size(); prevAngle = -1; }
	}
	cout << x *100 + y << endl;
}


int main(){
  ios::sync_with_stdio(0);cin.tie(0);
  vector<pair<ll,ll>> asteroids;
	map<pair<ll,ll>,char> m;
	string str;
	ll y = 0, x = 0;
  while(cin >> str){
		stringstream ss(str);
  	char c;
		for(x = 0; ss >> c; ++x){ 
			if(c == '#') asteroids.PB({x,y}); 
			m[{x,y}] = c;
		}
		y ++;
  }

	pair<ll,ll> st = station(asteroids);
	laser(st, asteroids);

  return 0;
}

