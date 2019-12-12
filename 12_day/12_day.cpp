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

// fasater than __gcd
ll gcd(ll a, ll b) {
  if (b == 0) return a;
  while (a != 0) swap(b=b%a,a);
  return b;
}

ll lcm(ll a, ll b) {
  return a/gcd(a,b)*b;
}

struct moon{
  moon(ll x, ll y, ll z){
    pos[0] = x;
    pos[1] = y;
    pos[2] = z;
    vel[0] = vel[1] = vel[2] = 0;
  }
  ll pos[3];
  ll vel[3];
  bool operator==(const moon & m) const {
    return pos[0] == m.pos[0] && pos[1] == m.pos[1] && pos[2] == m.pos[2] &&
           vel[0] == m.vel[0] && vel[1] == m.vel[1] && vel[2] == m.vel[2];
  }
};

void update(vector<moon> & v){
  for(auto i = v.begin(); i != v.end(); ++i){
    for(int j = 0; j < 3; ++j) i->pos[j] += i->vel[j];
  }
}


void gravity(vector<moon> & v){
  for(size_t i = 0; i < v.size(); ++i){
    for(size_t j = i+1; j < v.size(); ++j){
      for(size_t dim = 0; dim < 3; ++dim){
        if(v[i].pos[dim] < v[j].pos[dim]){ 
          v[i].vel[dim] += 1;
          v[j].vel[dim] -= 1;
        }
        else if(v[i].pos[dim] > v[j].pos[dim]){
          v[i].vel[dim] -= 1;
          v[j].vel[dim] += 1;
        }
      }
    }
  }
}
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    vector<moon> v;
    ll x,y,z;
    char c;
    while(scanf(" < x = %lld , y = %lld , z = %lld %c", &x,&y,&z,&c) != EOF){
      //cout << "<x=" << x << ", y=" << y << ", z=" << z << ">" << endl;
      v.PB(moon(x,y,z));
    }
    vector<moon> initial(v);
    ll steps = 0;
    ll periodic[3] = {-1,-1,-1};
    ll dimensions = 3;
    do{
      gravity(v);
      update(v);
      steps++;
      for(size_t dim = 0; dim < 3; ++dim){
        if(periodic[dim] != -1) continue;
        bool period = true;
        for(size_t i = 0; i < v.size(); ++i){
          if(v[i].pos[dim] != initial[i].pos[dim] || v[i].vel[dim] != initial[i].vel[dim]){
            period = false;
            break;
          } 
        }
        if(period){
          periodic[dim] = steps;
          dimensions --;
        }
      }
      //cerr << steps << endl;
      if(dimensions == 0) break;
    } while(v != initial);

    cout << lcm(periodic[0], lcm(periodic[1],periodic[2])) << endl;

    //cout << steps << endl;
    // PART 1
    /*while(steps++ < 1000){
      //cout << "After " << steps << " steps:" << endl;
      gravity(v);
      update(v);
      //cout << endl;
    }
    ll res = 0;
    for(auto i = v.begin(); i != v.end(); ++i){
      res += (abs(i->x) + abs(i->y) + abs(i->z)) * (abs(i->vx) + abs(i->vy) + abs(i->vz));
    }
    cout << res << endl;*/

    return 0;
}

