#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64; 
typedef vector<ll> v64;

#define forn(i, s, e) for(ll i = (s); i < (e); i++)
#define ln "\n"

#if defined(DEBUG)
    #define _ (void)0
    #define debug(x) cout << __LINE__ << ": " << #x << " = " << x << ln
#else
    #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
    #define debug(x) (void)0
#endif

const ll INF = 0x3f3f3f3f3f3f3f3fll;

// MO
//
// Para ter o bound abaixo, escolher
// SQ = n / sqrt(q)
// 
// O(n * sqrt(q))

const ll MAX = 2e5+10;
const ll SQ = sqrt(MAX);

v64 vec;

v64 freq(MAX); 
ll ans = 0;

inline void insert(ll p) {
    freq[vec[p]]++;
    ans += (freq[vec[p]] == 1);
}

inline void erase(ll p) {
    freq[vec[p]]--;
    ans -= (freq[vec[p]] == 0);
}

inline ll hilbert(ll x, ll y) {
	static ll N = 1 << (__builtin_clzll(0ll) - __builtin_clzll(MAX));
	ll rx, ry, s;
	ll d = 0;
	for (s = N/2; s > 0; s /= 2) {
		rx = (x & s) > 0, ry = (y & s) > 0;
		d += s * ll(s) * ((3 * rx) ^ ry);
		if (ry == 0) {
			if (rx == 1) x = N-1 - x, y = N-1 - y;
			swap(x, y);
		}
	}
	return d;
}

#define HILBERT false
vector<ll> MO(vector<pair<ll, ll>> &q) {
	ll m = q.size();
	vector<ll> ord(m);
	iota(ord.begin(), ord.end(), 0);
    ans = 0;
#if HILBERT
	vector<ll> h(m);
	for (ll i = 0; i < m; i++) h[i] = hilbert(q[i].first, q[i].second);
	sort(ord.begin(), ord.end(), [&](ll l, ll r) { return h[l] < h[r]; });
#else
	sort(ord.begin(), ord.end(), [&](ll l, ll r) {
		if (q[l].first / SQ != q[r].first / SQ) return q[l].first < q[r].first;
		if ((q[l].first / SQ) % 2) return q[l].second > q[r].second;
		return q[l].second < q[r].second;
	});
#endif
	vector<ll> ret(m);
	ll l = 0, r = -1;

	for (ll i : ord) {
		ll ql, qr;
		tie(ql, qr) = q[i];
		while (r < qr) insert(++r);
		while (l > ql) insert(--l);
		while (l < ql) erase(l++);
		while (r > qr) erase(r--);
		ret[i] = ans;
	}
	return ret;
}

int main(){
    _;
    ll n; cin >> n;
    ll q; cin >> q;

    v64 inp(n);
    v64 vecaux;
    vec.resize(n);
    vector<p64> quer(q);


    forn(i,0,n) cin >> inp[i];

    vecaux = inp;

    sort(vecaux.begin(), vecaux.end());
    map<ll,ll> inv;

    forn(i,0,n){
        inv[vecaux[i]] = i;
    }

    forn(i,0,n){
        vec[i] = inv[inp[i]];
    }

    forn(i,0,q){
        ll a,b; cin >> a >> b;
        a--; b--;
        quer[i] = {a,b};
    }
    
    auto resp = MO(quer);
    for(ll x: resp) cout << x << ln;
}