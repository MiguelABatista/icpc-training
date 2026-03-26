#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64;
typedef vector<ll> v64;

#define forn(i, s, e) for (ll i = (s); i < (e); i++)
#define sz(u) ((ll) u.size())
#define ln "\n"

#ifdef DEBUG
#define trace(u) u
#define _
#else
#define trace(u)
#define _ ios::sync_with_stdio(0); cin.tie(0)
#endif

#define debug(u) trace(cout << #u " = " << u << ln)
#define debugv(v) trace(cout << #v ": "; for (auto xx : v) cout << xx << " "; cout << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;

const vector<p64> moves = {
    { 1, 2},
    { 1,-2},
    {-1, 2},
    {-1,-2},
    {-2, 1},
    { 2, 1},
    { 2,-1},
    {-2,-1}
};
ll n = 8;

bool solve(ll x, ll y, ll curr, vector<v64>& path){
	assert(path[x][y] == -1);
	path[x][y] = curr;
	if(curr == 63) return true;

	trace(
		cout << curr << ln;
		forn(i,0,n){
			forn(j,0,n){
				cout << setw(2) << path[i][j] << " ";
			}
			cout << ln;
		}
		cout << ln;
	)

	vector<v64> prio(n, v64(n, INF));
	forn(i,0,n){
		forn(j,0,n){
			if(path[i][j] != -1)continue;

			ll v = 0;
			for(auto [a,b] : moves){
				if(a+i < 0 || a+i >= n) continue;
				if(b+j < 0 || b+j >= n) continue;
				if(path[i+a][j+b] != -1) continue;
				v++;
			}
			prio[i][j] = v;
		}
	}
	set<tuple<ll,ll,ll>> s;
	for(auto [a,b] : moves){
		if(a+x < 0 || a+x >= n) continue;
		if(b+y < 0 || b+y >= n) continue;
		if(path[a+x][b+y] != -1) continue;
		s.insert({prio[a+x][b+y], a+x,b+y});
	}

	for(auto [p, a, b] : s){
		if(solve(a,b,curr+1, path)) return true;
	}

	path[x][y] = -1;
	return false;
}

int main() {
    _;
    ll x, y; cin >> x >> y;
	x--; y--;
    map<ll, p64> conv;
    vector<v64> mat(n, v64(n));
    vector<v64> prio(n, v64(n));
	
	ll idx = 0;
	forn(i,0,n){
		forn(j,0,n){
			mat[i][j] = idx;
            conv[idx] = {i,j};
            idx++;
        }
    }
	
	vector<v64> path(n, v64(n, -1));
	
	solve(y,x,0,path);

	forn(i,0,n){
		forn(j,0,n){
			cout << setw(2) << path[i][j] + 1 << " ";
		}
		cout << ln;
	}
    return 0;
}
