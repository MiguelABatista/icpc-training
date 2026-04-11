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

// Linear Sieve (prime precomputation)
//
// Computes primes up to N in O(N) using the smallest prime factor (lp).
// pr will contain all primes <= N.
// lp[x] stores the smallest prime dividing x.
//
// complexity: O(N)


pair<v64, v64> sieve(ll n){
    v64 lp(n+1);
    v64 pr;
    forn(i, 2, n+1) {
        if (lp[i] == 0) {
            lp[i] = i;
            pr.push_back(i);
        }
        for (ll j = 0; i * pr[j] <= n; ++j) {
            lp[i * pr[j]] = pr[j];
            if (pr[j] == lp[i]) {
                break;
            }
        }
    }
    return {pr, lp};
}

v64 calc_mu(v64& lp) {
    ll n = sz(lp) - 1;
    v64 ans(n);
    ans[1] = 1;
    forn(i,2,n) {
        ll p = lp[i], x = i/p;
        if (lp[x] == p) ans[i] = 0;
        else ans[i] = -ans[x];
    }
    return ans;
}

v64 calc_d(v64& lp) {
    ll n = sz(lp) - 1;
    v64 ans(n);
    ans[1] = 1;
    forn(i, 2, n) {
        ll p = lp[i], x = i / p;
        if (lp[x] != p) ans[i] = 1;
        else ans[i] = ans[x] + 1;
    }
    forn(i, 2, n) {
        ll p = lp[i], x = i / p;
        if (ans[i] == 1) ans[i] = ans[x] * 2;
        else ans[i] = (ans[x] / ans[i]) * (ans[i] + 1);
    }
    return ans;
}


int main() {
    _;
    ll n; cin >> n;
    auto [pr, lp] = sieve(1'000'005);
    v64 d = calc_d(lp);

    forn(i,0,n){
        ll x; cin >> x;
        cout << d[x] << ln;
    }
    return 0;
}
