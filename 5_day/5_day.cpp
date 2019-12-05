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

void opt(vector<ll> v){
	size_t i = 0;
  while(i < v.size()){
    
		// cout << "PARSING: " << v[i] << endl;
		ll op = v[i] % 100;
		// cout << "OP: " << op << endl;
		if(op == 99) break;
		ll a = v[i] / 100 % 10;
		// cout << "FIRST OPERAND IS " << (a == 0 ? "positional" : "immediate") << endl;
		ll b = v[i] / 1000 % 10;
		// cout << "SECOND OPERAND IS " << (b == 0 ? "positional" : "immediate") << endl;
		if(a == 0) a = v[v[i+1]];
		else a = v[i+1];

		if(b == 0) b = v[v[i+2]];
		else b = v[i+2];

		switch(op){
			case 1:
				v[v[i+3]] = a + b; 
				i+=4;
				break;
			case 2:
				v[v[i+3]] = a * b;
				i+=4;
				break;
			case 3:
				v[v[i+1]] = 5;
				i+=2;
				break;
			case 4:
				cout << a << endl;
				i+=2;
				break;
			case 5:
				if(a != 0) i = b;
				else i += 3;
				break;
			case 6:
				if(a == 0) i = b;
				else i+= 3;
				break;
			case 7:
				if(a < b) v[v[i+3]] = 1;
				else v[v[i+3]] = 0;
				i+=4;
				break;
			case 8:
				if(a == b) v[v[i+3]] = 1;
				else v[v[i+3]] = 0;
				i+=4;
				break;
		}
  }
}

int main(){
  ios::sync_with_stdio(0);cin.tie(0);
  ll num;
  vector<ll> v;
  char delim;
  while(cin >> num){ v.PB(num); cin >> delim; }
  opt(v);
  return 0;
}

