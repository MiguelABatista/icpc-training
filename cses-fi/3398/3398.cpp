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
const ll MOD = 1'000'000'007;

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


int main() {
    _;
    ll n; cin >> n;
    v64 perm(n);
    forn(i,0,n){
        cin >> perm[i];
        perm[i]--;
    }
    auto [pr, lp] = sieve(n+1);

    debugv(perm);
    v64 vis(n,0);
    v64 siz;
    
    forn(i,0,n){
        if(vis[i]) continue;
        ll cic = 0;
        ll start = i;
        ll x = i;
        do{
            cic++;
            vis[x] = 1;
            x = perm[x];
        }while(x != start);
        siz.push_back(cic);
    }
    map<ll,ll> mp;
    for(ll x: siz){
        while (x> 1){            
            ll p = lp[x];
            ll a = 0;
            while(x%p == 0){
                a++;
                x /= p;
            }
            mp[p] = max(mp[p], a);
        }
    }
    ll resp = 1;

    for(auto [p,a] : mp){
        forn(i,0,a) resp = (resp*p)%MOD;
    }

    cout << resp << ln;
    return 0;
}
