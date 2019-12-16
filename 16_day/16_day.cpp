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

void fft(vector<ll> v, vector<ll> & pattern){
	ll phase = 0;
	while(phase++ < 100){
		vector<ll> v2(v);
		for(size_t i = 0; i < v.size(); ++i){
			vector<int> p;
			for(size_t j = 0; j < pattern.size(); ++j){
				for(size_t k = 0; k <= i; ++k) p.PB(pattern[j]);
			}
			ll sum = 0;
			for(size_t curr = i; curr < v.size(); ++curr){
				ll idx = (curr + 1) % p.size();
				sum += (p[idx] * v[curr]);
			}
			v2[i] = abs(sum) % 10;
		}
		v = v2;
	}
	cout << "First part: ";
	F(8) cout << v[i];
	cout << endl;
}


int main(){
	ios::sync_with_stdio(0);cin.tie(0);
	vector<ll> v;
	vector<ll> pattern = {0,1,0,-1};
	char c;
	while(cin >> c){
		v.PB(c - '0');
	}
	//fft(v, pattern);

	ll size = v.size();
	F(10000-1){
		FF(size) v.PB(v[j]);
	}

	ll offset = 0;
	F(7) {
		offset = v[i] + offset * 10;
	}
	//99974970
	cout << "offset = " << offset << " to size = " << v.size() << endl;
	vector<ll> res(v.size());
	ll phases = 0;
	while(phases++ < 100){
		ll sum = 0;
		for(size_t i = v.size()-1; i >= offset; --i){
			sum = (sum+v[i]);
			res[i] = sum%10;	
		}
		for(size_t i = v.size()-1; i >= ; --i){
			v[i] = res[i];
		}
	}
	cout << "Second part: ";
	F(8) cout << v[offset+i];
	cout << endl;	

	return 0;
}

