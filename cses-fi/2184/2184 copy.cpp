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

// Persistent Segment Tree - O(log n) per query/update
// Supports point updates and range queries across versions

struct Node {
	ll val;
	ll l, r;
};

struct perseg {
	ll n, cnt = 0;
	vector<Node> nd;
	v64 rt;

	perseg(v64& v, ll q = 0) : n(sz(v)) {
		nd.reserve(2*n + 18*(n+q));
		rt.reserve(q + 2);
		rt.push_back(cnt++);
		build(nd.data(), cnt, rt[0], 0, n-1, v);
	}
	static ll build(Node* d, ll& cnt, ll p, ll l, ll r, v64& v) {
		if (l == r) return d[p].val = v[l];
		d[p].l = cnt++; d[p].r = cnt++;
		ll m = (l+r)/2;
		return d[p].val = build(d, cnt, d[p].l, l, m, v) + build(d, cnt, d[p].r, m+1, r, v);
	}
	ll query(ll a, ll b, ll t) {
		return query(nd.data(), a, b, rt[t], 0, n-1);
	}
	static ll query(Node* d, ll a, ll b, ll p, ll l, ll r) {
		if (b < l || r < a) return 0;
		if (a <= l && r <= b) return d[p].val;
		ll m = (l+r)/2;
		return query(d, a, b, d[p].l, l, m) + query(d, a, b, d[p].r, m+1, r);
	}
	ll set(ll a, ll val, ll t) {
		ll nr = cnt++;
		set(nd.data(), cnt, a, val, rt[t], nr, 0, n-1);
		rt.push_back(nr);
		return (ll)rt.size()-1;
	}
	static ll set(Node* d, ll& cnt, ll a, ll val, ll lp, ll p, ll l, ll r) {
		if (l == r) return d[p].val = val;
		ll m = (l+r)/2;
		if (a <= m) {
			d[p].l = cnt++; d[p].r = d[lp].r;
			return d[p].val = set(d, cnt, a, val, d[lp].l, d[p].l, l, m) + d[d[p].r].val;
		}
		d[p].l = d[lp].l; d[p].r = cnt++;
		return d[p].val = d[d[p].l].val + set(d, cnt, a, val, d[lp].r, d[p].r, m+1, r);
	}
};

int main() {
    _;
    ll n, q; cin >> n >> q;
    v64 vaux(n);
    vector<p64> vecp(n);
    ll tot = 0;
    forn(i,0,n){
        cin >> vecp[i].first;
        tot += vecp[i].first;
        vecp[i].second = i;
    }

    sort(vecp.begin(), vecp.end());

    perseg seg(vaux, n);

    forn(i,0,n) seg.set(vecp[i].second, vecp[i].first, i);
	v64 times(n);
	forn(i,0,n) times[i] = vecp[i].first;

	debugv(times);
    
	auto get_time = [&](ll val){
		auto resp = (ll)(upper_bound(times.begin(), times.end(), val) - times.begin()); 
		if(resp == 0) return 0ll;
		return resp-1; 
    };

    while(q--){
        ll a, b; cin >> a >> b;
		a--, b--;
		ll reach = 0;
        ll nreach = seg.query(a,b,get_time(1)+1);
        while (reach < nreach){
			reach = nreach;         
            ll t =  get_time(reach+1);
            nreach = seg.query(a,b, t+1);   
        }
		cout << nreach + 1 << ln;
    }

    return 0;
}
