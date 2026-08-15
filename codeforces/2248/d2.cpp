#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;
typedef vector<ll> vll;

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

// Fenwick Tree (Binary Indexed Tree)
//
// Supports point updates and prefix/range sum queries in logarithmic time using a 1-indexed BIT.
//
// complexity: O(log N) per op, O(N)

struct Bit {
    ll n;
    vll bit;
    Bit(ll _n = 0) : n(_n), bit(n + 1) {}
    Bit(vll& v) : n(sz(v)), bit(n + 1) {
        for (ll i = 1; i <= n; i++) {
            bit[i] += v[i - 1];
            ll j = i + (i & -i);
            if (j <= n) bit[j] += bit[i];
        }
    }
    void update(ll i, ll x) { // soma x na posicao i
        for (i++; i <= n; i += i & -i) bit[i] += x;
    }
    ll pref(ll i) { // soma [0, i]
        ll ret = 0;
        for (i++; i; i -= i & -i) ret += bit[i];
        return ret;
    }
    ll query(ll l, ll r) {  // soma [l, r]
        return pref(r) - pref(l - 1); 
    }
    ll upper_bound(ll x) {
        ll p = 0;
        for (ll i = __lg(n); i+1; i--) 
            if (p + (1<<i) <= n && bit[p + (1<<i)] <= x)
                x -= bit[p += (1 << i)];
        return p;
    }
};


void solve(){
    ll n, q; cin >> n >> q;
    string s, r; cin >> s >> r;
    Bit bit00(n), bit10(n), bit01(n), bit11(n);

    forn(i,0,n){
        if(s[i]  == '0' && r[i] == '0') bit00.update(i,1);
        if(s[i]  == '0' && r[i] == '1') bit01.update(i,1);
        if(s[i]  == '1' && r[i] == '0') bit10.update(i,1);
        if(s[i]  == '1' && r[i] == '1') bit11.update(i,1);
    }

    while(q--){
        ll lef, rig; cin >> lef >> rig;
        lef--, rig--;
        ll a00 = bit00.query(lef,rig);
        ll a01 = bit01.query(lef,rig);
        ll a10 = bit10.query(lef,rig);
        ll a11 = bit11.query(lef,rig);
        ll x = max(a01, a10) - min(a01,a10);
        if(x <= a00 + a11) cout << "YES" << ln;
        else cout << "NO" << ln;
    }
}

int main() {
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}