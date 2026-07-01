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
#define debugm(v) trace(cout << #v ": "; for (auto xx : v) cout << xx.first << ":" << xx.second << " "; cout << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;
const ll MOD = 1'000'000'007;
const ll MAX = 500'005;

// Linear Sieve (prime precomputation)
//
// Computes primes up to N in O(N) using the smallest prime factor (lp).
// pr will contain all primes <= N.
// lp[x] stores the smallest prime dividing x.
//
// complexity: O(N)

vll lp, pr;

pair<vll, vll> sieve(ll n){
    vll llp(n+1);
    vll lpr;
    forn(i, 2, n+1) {
        if (llp[i] == 0) {
            llp[i] = i;
            lpr.push_back(i);
        }
        for (ll j = 0; i * lpr[j] <= n; ++j) {
            llp[i * lpr[j]] = lpr[j];
            if (lpr[j] == llp[i]) {
                break;
            }
        }
    }
    return {lpr, llp};
}

map<ll, ll> factor(ll n){
    debug(n);
    map<ll, ll> mp;
    while(n > 1){
        ll p = lp[n];
        ll alpha = 0;
        while(n%p == 0){
            alpha++;
            n /= p;
        }
        mp[p] = alpha; 
    }
    debugm(mp);
    return mp;
}

void solve(){
    ll n, x; cin >> n >> x;
    vll vec(n);
    forn(i,0,n) cin >> vec[i];
    map<ll,ll> vpsum;
    
    forn(i,0,n){
        auto mp = factor(vec[i]);
        for(auto [k,v] : mp){
            vpsum[k] += v;
        }
    }
    debugm(vpsum);
    ll resp = 1;
    for(auto [k,v] : vpsum){
        resp = (resp*(1+v))%MOD;
    }
    cout << resp << ln;
}

int main() {
    _;
    auto p = sieve(MAX);
    pr = p.first;
    lp = p.second;

    ll t; cin >> t;
    while(t--) solve();
    return 0;
}
