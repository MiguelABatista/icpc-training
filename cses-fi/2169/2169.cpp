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
 
// Fenwick Tree (Binary Indexed Tree)
//
// Supports point updates and prefix/range sum queries in logarithmic time using a 1-indexed BIT.
//
// complexity: O(log N) per op, O(N)

struct Bit {
    ll n;
    v64 bit;
    Bit(ll _n = 0) : n(_n), bit(n + 1) {}
    Bit(v64& v) : n(sz(v)), bit(n + 1) {
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
            if (p + (1<<i) <= n and bit[p + (1<<i)] <= x)
                x -= bit[p += (1 << i)];
        return p;
    }
};

 
 
int main() {
    _;
    ll n; cin >> n;
    vector<p64> vec(n);
    v64 vals;

    forn(i,0,n){
        cin >> vec[i].first >> vec[i].second;
        vals.push_back(vec[i].first);
        vals.push_back(vec[i].second);
    }

    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());

    auto compress = [&](ll x) {
        return (ll)(lower_bound(vals.begin(), vals.end(), x) - vals.begin());
    };

    vector<tuple<ll,ll,ll>> v(n);
    vector<tuple<ll,ll,ll>> vout(n);
    forn(i,0,n) v[i] = {compress(vec[i].second), -compress(vec[i].first), i};
    forn(i,0,n) vout[i] = {compress(vec[i].first), -compress(vec[i].second), i};
 
    sort(v.begin(), v.end());
    sort(vout.begin(), vout.end());
  
    v64 respin(n);
    v64 respout(n);
    Bit bitin(2*n+1);
    Bit bitout(2*n+1);
 
    forn(i,0,n){
        auto [b,a, idx] = v[i];
        a *= -1;
        respin[idx] = bitin.query(a,b);
        bitin.update(a,1);
    }
 
    forn(i,0,n){
        auto [a,b, idx] = vout[i];
        b *= -1;
        respout[idx] = bitout.query(b, 2*n);
        bitout.update(b,{1});
    }
 
    forn(i,0,n) cout << respin[i] << " \n"[i==n-1];
    forn(i,0,n) cout << respout[i] << " \n"[i==n-1];
    return 0; 
}