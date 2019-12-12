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

ll maxX = INT_MIN;
ll minX = INT_MAX;
ll maxY = INT_MIN;
ll minY = INT_MAX;

void move(ll & x, ll & y, ll & direction, ll output){
  if(output == 1){ // right 90 degrees
    direction = (direction+1) % 4;
  }
  else {
    direction = direction - 1;
    direction = direction < 0 ? 4 + direction : direction;
  }
  if(direction == 0) y+=1;
  else if(direction == 1) x+=1;
  else if(direction == 2) y-=1;
  else if(direction == 3) x-=1;
  maxX = max(maxX, x);
  minX = min(minX, x);
  minY = min(minY, y);
  maxY = max(maxY, y);
}
void opt(map<ll,ll> & m){
	size_t i = 0;
  ll base = 0;
  set<pair<ll,ll>> coords;
  map<pair<ll,ll>, bool> hull;
  ll direction = 0, x = 0, y = 0;
  hull[{0,0}] = 1; // white
  bool painting = true;
  while(i < m.size()){
		ll op = m[i] % 100;
		if(op == 99) break;
		ll a = m[i] / 100 % 10, b = m[i] / 1000 % 10, c = m[i] / 10000 % 10;
		if(a == 0) a = m[i+1];
		else if(a == 1) a = i+1;
    else if(a == 2) a = base+m[i+1];

		if(b == 0) b = m[i+2];
		else if(b == 1) b = i+2;
    else if(b == 2) b = base+m[i+2];
    
    if(c == 0) c = m[i+3];
    else c = base + m[i+3];

		switch(op){
			case 1: m[c] = m[a] + m[b]; i+=4; break;
			case 2: m[c] = m[a] * m[b]; i+=4; break;
			case 3:
        m[a] = hull[{x,y}];
        i+=2; 
        break;
			case 4: 
        if(painting) { hull[{x,y}] = m[a]; coords.insert({x,y}); }
        else {
          move(x,y,direction, m[a]);
        }
        //cout << m[a] << endl; 
        painting = !painting;
        i+=2; 
        break;
			case 5:	if(m[a] != 0) i = m[b]; else i += 3; break;
			case 6:	if(m[a] == 0) i = m[b]; else i+= 3;	break;
			case 7:	if(m[a] < m[b]) m[c] = 1; else m[c] = 0; i+=4; break;
			case 8: if(m[a] == m[b]) m[c] = 1; else m[c] = 0; i+=4; break;
      case 9: base += m[a]; i+=2; break;
		}
  }
  for(int i = maxY; i >= minY; i --){
    for(int j = minX; j <= maxX; j ++){
        cout << (hull[{j,i}] == 1 ? '#' : ' ');
    }
    cout << endl;
  }

  cout << coords.size() << endl;
}

int main(){
  ios::sync_with_stdio(0);cin.tie(0);
  ll num;
  map<ll,ll> m;
  char delim;
  ll i = 0;
  while(cin >> num){ m[i++] = num; cin >> delim; }
  opt(m);
  return 0;
}

