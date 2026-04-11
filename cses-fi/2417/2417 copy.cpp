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
#define debugv(v) trace(cout <<  #v ": "; for (auto xx : v) cout << setw(2) <<  xx << " "; cout << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;
ll MAX = 1'000'005;

// Linear Sieve (prime precomputation)
//
// Computes primes up to N in O(N) using the smallest prime factor (lp).
// pr will contain all primes <= N.
// lp[x] stores the smallest prime dividing x.
//
// complexity: O(N)


inline ll esc2(ll n){
    return (n*(n-1))/2;
}

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


int main() {
    _;
    trace(MAX = 25;)
    auto [pr, lp] = sieve(MAX);
    v64 mu = calc_mu(lp);
    

    ll n; cin >> n;
    v64 freq1(MAX);
    v64 freq2(MAX);

    forn(i,0,n){
        ll x; cin >> x;
        freq1[x]++;
    }

    forn(i,0,MAX){
        if(freq1[i] == 0) continue;
        for(ll d = 1; d*d <= i; d++){
            if(i%d) continue;
            freq2[d] += freq1[i];
            if(d*d != i) freq2[i/d] += freq1[i];
        }
    }

    ll resp = 0;
    forn(i,0,MAX) freq2[i] = esc2(freq2[i]);
    
    forn(i,1,MAX){
        resp += mu[i]*freq2[i];
    }

    // cout << (n*(n-1))/2 - resp << ln;
    cout << resp << ln;
    return 0;
}
