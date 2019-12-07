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

ll ampl(ll amp, vector<vector<ll>> & input, vector<ll> & v, ll & pos, vector<bool> & first){
	while(pos < v.size()){
		ll op = v[pos] % 100;
		if(op == 99) { return INT_MAX; }
		ll a = (v[pos] / 100 % 10 == 0) ? v[v[pos+1]] : v[pos+1];
		ll b = (v[pos] / 1000 % 10 == 0)? v[v[pos+2]] : v[pos+2];

		switch(op){
			case 1: v[v[pos+3]] = a + b; pos+=4; break;
			case 2: v[v[pos+3]] = a * b; pos+=4; break;
			case 3:
				if(first[amp]){
					v[v[pos+1]] = input[amp][0];
					first[amp] = false;
				}
				else {
					v[v[pos+1]] = input[amp][1];
				}
				pos+=2;
				break;
			case 4:
				input[(amp+1)%5][1] = a;
				pos+=2;
				return a;
			case 5: if(a != 0) pos = b; else pos += 3; break;
			case 6: if(a == 0) pos = b; else pos+= 3; break;
			case 7: if(a < b) v[v[pos+3]] = 1; else v[v[pos+3]] = 0; pos+=4; break;
			case 8: if(a == b) v[v[pos+3]] = 1; else v[v[pos+3]] = 0; pos+=4; break;
		}
	}	
	return -1;
}


ll opt(vector<ll> v, vector<ll> phase){
	vector<vector<ll>> input(5);
	F(5){ input[i].PB(phase[i]); input[i].PB(0); }
	ll res = 0;
	vector<ll> p = {0,0,0,0,0};
	vector<bool> first = {true, true, true, true, true};
	vector<vector<ll>> prog = {v,v,v,v,v};
	while(true){
		ll ret = 0;
		FOR(amp,0,5){
			ret = ampl(amp, input, prog[amp], p[amp], first);
		}
		if(ret == INT_MAX) break;
		else res = max(ret, res);
	}
	return res;
}

int main(){
  ios::sync_with_stdio(0);cin.tie(0);
  ll num;
  vector<ll> v;
  char delim;
  while(cin >> num){ v.PB(num); cin >> delim; }
	ll res = 0;
	tuple<ll,ll,ll,ll,ll> settings;
	// vector<ll>phase = {0,1,2,3,4};
	vector<ll>phase = {5,6,7,8,9}; // part 2
	do{
		//cout << "trying setting " << i << j << k << l << h << endl;
		ll curr = opt(v,phase);
		res = max(res, curr);
	} while(next_permutation(phase.begin(),phase.end()));
	cout << res << endl;
  return 0;
}

