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

struct node{
	ll total;
	uint32_t hasKeys;
	pair<ll,ll> pos;
};


void drawMap(map<pair<ll,ll>, char> & m, ll width, ll height);
void redraw(map<pair<ll,ll>, char> & m, pair<ll,ll> start);
void unlockMaze(map<pair<ll,ll>, char> & m, ll total, pair<ll,ll> start);
bool checkPos(map<pair<ll,ll>, char> & m, 
							pair<ll,ll> pos, queue<pair<ll, node>> & q, 
							node n, ll steps, map<pair<ll,ll>,set<uint32_t>> & states);

string pos_str(pair<ll,ll> pos){
	string str = "[" + to_string(pos.aa) + ", " + to_string(pos.bb) + "]";
	return str;
}


//----------------------------------------------------------------------------
bool checkPos2(map<pair<ll,ll>, char> & m, 
							pair<ll,ll> pos, queue<pair<ll, node>> & q, 
							node n, ll steps, map<pair<ll,ll>,set<uint32_t>> & states, 
							uint32_t & hasKeys, ll & foundKeys, ll & total, pair<ll,ll> & start){

	bool flag = false;
	if(states[pos].find(hasKeys) != states[pos].end()) return flag;

	if(m[pos] == '.' || m[pos] == '@') {
		n.pos = pos;
		// cout << "Going to pos " << pos_str(pos) << endl;
		q.push({steps+1, n});
	}
	else if('A' <= m[pos] && m[pos] <= 'Z'){ // doors
		if(!(hasKeys & 1 << (m[pos] - 'A'))) {
			// cout << "Can't unlock the door (" << m[pos] << ") at pos " << pos_str(pos) << endl;	
			return flag;
		}
		n.pos = pos;
		// cout << "Unlocking the door (" << m[pos] << ") at pos " << pos_str(pos) << endl;
		q.push({steps+1, n}); 
	}
	else if('a' <= m[pos] && m[pos] <= 'z'){
		ll bit = 1 << (m[pos] - 'a');
		if(!(hasKeys & bit)) {
			// cout << "-- Picking the key (" << m[pos] << ") at pos " << pos_str(pos) << endl;
			hasKeys |= bit; 
			total --;
			foundKeys = steps+1;
			start = pos;
			flag = true;
		}
		n.pos = pos;
		q.push({steps+1, n});
	}
	states[pos].insert(hasKeys);
	return flag;
}


void unlock2(map<pair<ll,ll>, char> & m, ll total, vector<pair<ll,ll>> & starts){
	
	uint32_t hasKeys = 0;
	map<pair<ll,ll>,set<uint32_t>> state;
	ll count[4] = {0,0,0,0};
	while(total > 0){
		FOR(robot, 0, 4){
			// cout << "QUEUE for ROBOT #" << robot << endl;
			queue<pair<ll, node>> q;
			node n;
			n.pos = starts[robot];
			n.total = total;
			n.hasKeys = 0;
			q.push({count[robot],n});
			while(!q.empty()){
				pair<ll,node> top = q.front(); q.pop();
				// cout << "AT node " << pos_str(top.bb.pos) << endl;
				ll x,y; tie(x,y) = top.bb.pos;
				if(checkPos2(m, {x+1,y}, q, top.bb, top.aa, state, hasKeys, count[robot], total, starts[robot])) break;
				if(checkPos2(m, {x-1,y}, q, top.bb, top.aa, state, hasKeys, count[robot], total, starts[robot])) break;
				if(checkPos2(m, {x,y+1}, q, top.bb, top.aa, state, hasKeys, count[robot], total, starts[robot])) break;
				if(checkPos2(m, {x,y-1}, q, top.bb, top.aa, state, hasKeys, count[robot], total, starts[robot])) break;
			}
		}	
	}
	ll res = 0;
	F(4) res+= count[i];
	cout << res << endl;
}

int main(){
	ios::sync_with_stdio(0);cin.tie(0);
	map<pair<ll,ll>, char> m;
	ll y = 0;
	ll width = 0, height = 0;
	pair<ll,ll> start;
	char c;
	ll total = 0;
	string str;
	while(getline(cin, str)){
		width = str.size();
		stringstream ss(str);
		ll x = 0;
		while(ss >> c){
			if(c == '@'){ start.aa = x; start.bb = y; }
			else if('a' <= c && c <= 'z') total++;
			m[{x++,y}] = c;
		}
		y ++;
		height ++;
	}
	// PART 1
	// unlockMaze(m, total, start);

	redraw(m,start);
	drawMap(m, width, height);
	cout << "Total keys: " << total << endl;
	vector<pair<ll,ll>> starts = {{start.aa-1,start.bb-1}, 
															{start.aa+1, start.bb-1},
															{start.aa+1, start.bb+1},
															{start.aa-1, start.bb+1}};

	unlock2(m, total, starts);


	return 0;
}

void drawMap(map<pair<ll,ll>, char> & m, ll width, ll height){
	FOR(y,0,height){
		FOR(x,0,width){
			cout << m[{x,y}];
		}
		cout << endl;
	}
}

void redraw(map<pair<ll,ll>, char> & m, pair<ll,ll> start){
	string str = "@#@###@#@";
	ll idx = 0;
	FOR(y,-1,2){
		FOR(x,-1,2){
			m[{start.aa+x,start.bb+y}] = str[idx++];
		}
	}
}

void unlockMaze(map<pair<ll,ll>, char> & m, ll total, pair<ll,ll> start){
	queue<pair<ll, node>> q;
	map<pair<ll,ll>,set<uint32_t>> state;
	node n;
	n.pos = start;
	n.total = total;
	n.hasKeys = 0;
	q.push({0,n});
	ll res = 0;
	// ll delim = 0;
	while(!q.empty()){
		//if(delim++ > 20) break;
		pair<ll,node> top = q.front(); q.pop();
		ll x,y; tie(x,y) = top.bb.pos;
		// cerr << "AT THE NODE " << x << ", " << y << endl;
		res = top.aa;
		if(checkPos(m, {x+1,y}, q, top.bb, top.aa, state)) break;
		if(checkPos(m, {x-1,y}, q, top.bb, top.aa, state)) break;
		if(checkPos(m, {x,y+1}, q, top.bb, top.aa, state)) break;
		if(checkPos(m, {x,y-1}, q, top.bb, top.aa, state)) break;
		//cerr <<endl;
	}
	cout << res+1 << endl;
}

bool checkPos(map<pair<ll,ll>, char> & m, 
							pair<ll,ll> pos, queue<pair<ll, node>> & q, 
							node n, ll steps, map<pair<ll,ll>,set<uint32_t>> & states){
	n.pos = pos;
	if(states[pos].find(n.hasKeys) != states[pos].end()) return false;

	if(m[pos] == '.' || m[pos] == '@') q.push({steps+1, n});
	else if('A' <= m[pos] && m[pos] <= 'Z'){ // doors
		if(!(n.hasKeys & 1 << (m[pos] - 'A'))) return false;
		q.push({steps+1, n}); 
	}
	else if('a' <= m[pos] && m[pos] <= 'z'){
		ll bit = 1 << (m[pos] - 'a');
		if(!(n.hasKeys & bit)) {
			n.hasKeys |= bit; n.total --;
		}
		q.push({steps+1, n});
	}
	states[pos].insert(n.hasKeys);
	return n.total == 0;
}