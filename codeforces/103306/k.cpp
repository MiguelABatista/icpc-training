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
const ll MOD = 1'000'000'007;
const ll MAX = 1'000'005;

vll pot2(MAX);
void prep(){
    pot2[0] = 1;
    forn(i,1,MAX) pot2[i] = 2*(pot2[i-1])%MOD;
}

// Linear Sieve (prime precomputation)
//
// Computes primes up to N in O(N) using the smallest prime factor (lp).
// pr will contain all primes <= N.
// lp[x] stores the smallest prime dividing x.
//
// complexity: O(N)


pair<vll, vll> sieve(ll n){
    vll lp(n+1);
    vll pr;
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

vll calc_mu(vll& lp) {
    ll n = sz(lp) - 1;
    vll ans(n);
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
    prep();
    auto [pr, lp] = sieve(MAX);
    auto mu = calc_mu(lp);

    ll t; cin >> t;
    vll mem(MAX, -1);

    while(t--){
        ll n; cin >> n;
        if(mem[n] != -1){
            cout << mem[n] << ln;
            continue;
        }

        ll resp = 0;

        for(ll d = 1; d*d <= n; d++){
            if(n%d != 0) continue;            
            resp = (resp+mu[n/d]*pot2[d])%MOD;
            if(d*d != n) resp = (resp+mu[d]*pot2[n/d])%MOD;
        }
        debug(resp);
        resp = (MOD + pot2[n] - resp)%MOD;
        // resp = (resp + MOD - pot2[n])%MOD;
        mem[n] = resp;
        cout << resp << ln;   
    }
    return 0;
}
