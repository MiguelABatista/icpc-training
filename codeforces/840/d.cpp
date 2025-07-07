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

const ll INF = 1'000'000'000;
const ll MAX = 3e5+30;
const ll SQ = 550; // 540

mt19937_64 rng((ll) chrono::steady_clock::now().time_since_epoch().count());

ll uniform(ll l, ll r){
	uniform_int_distribution<ll> uid(l, r);
	return uid(rng);
}

int fast_random_int(int l, int r) {
    return l + rand() % (r - l + 1);
}

vector<ll> freq(MAX);
vector<ll> v;

// MO
//
// Para ter o bound abaixo, escolher
// SQ = n / sqrt(q)
// 
// O(n * sqrt(q))


inline void insert(ll p) {
    freq[v[p]]++;
}

inline void erase(ll p) {
    freq[v[p]]--;
}

inline ll hilbert(ll x, ll y) {
	static ll N = 1 << (sizeof(ll) * 8 - __builtin_clzll(MAX));
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

#define HILBERT true
vector<ll> MO(vector<pair<p64, ll>> &q) {
	ll m = q.size();
	vector<ll> ord(m);
	iota(ord.begin(), ord.end(), 0);
#if HILBERT
	vector<ll> h(m);
	for (ll i = 0; i < m; i++) h[i] = hilbert(q[i].first.first, q[i].first.second);
	sort(ord.begin(), ord.end(), [&](ll l, ll r) { return h[l] < h[r]; });
#else
	sort(ord.begin(), ord.end(), [&](ll l, ll r) {
		if (q[l].first.first / SQ != q[r].first.first / SQ) return q[l].first.first < q[r].first.first;
		if ((q[l].first.first / SQ) % 2) return q[l].first.second > q[r].first.second;
		return q[l].first.second < q[r].first.second;
	});
#endif
	vector<ll> ret(m);
	ll l = 0, r = -1;

	for (ll i : ord) {
		ll ql, qr;
		tie(ql, qr) = q[i].first;
		while (r < qr) insert(++r);
		while (l > ql) insert(--l);
		while (l < ql) erase(l++);
		while (r > qr) erase(r--);
        
        ll best = INF;
        ll k = q[i].second;
        
        forn(j, 0, 80){
            ll val = v[uniform(ql,qr)];
            ll f = freq[val];
            if(f*k <= qr-ql+1) continue;
            best = min(best, val);
        }

        if(best == INF) ret[i] = -1;
        else ret[i] = best;
	}
	return ret;
}


int main(){
    _; ll n, m; cin >> n >> m;

    v.resize(n);

    forn(i, 0, n) cin >> v[i];

    vector<pair<p64, ll>> querrie(m);
    forn(i, 0, m){
        ll a, b, c; cin >> a >> b >> c;
        a--; b--;
        querrie[i] = {{a, b}, c};
    }

    vector<ll> resp = MO(querrie);

    for(auto x : resp) cout << x << ln;
 
    return 0;
}