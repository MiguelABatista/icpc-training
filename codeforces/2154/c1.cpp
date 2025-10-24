#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64; 
typedef vector<ll> v64;

#define forn(i, s, e) for(ll i = (s); i < (e); i++)
#define sz(x) ((ll) x.size())
#define ln "\n"

#ifdef DEBUG
    #define trace(x) x
    #define _ (void)0
#else
    #define trace(x) (void)0
    #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
#endif

#define debugv(v) trace({cout << #v": "; for (auto x : v) cout<< x << " "; cout << ln;})
#define debugm(v) trace({cout << #v": "; for (auto x : v) cout<< x.first << ":" << x.second << " "; cout << ln;})
#define debug(x) trace(cout << __LINE__ << ": " #x " = " << x << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;

// Linear Sieve (prime precomputation)
//
// Computes primes up to N in O(N) using the smallest prime factor (lp).
// pr will contain all primes ≤ N.
// lp[x] stores the smallest prime dividing x.
//
// complexity: O(N)

const ll MAXN = 200'005; 
v64 lp(MAXN+1), pr;

void sieve(){
    forn(i, 2, MAXN+1) {
        if (lp[i] == 0) {
            lp[i] = i;
            pr.push_back(i);
        }
        for (ll j = 0; i * pr[j] <= MAXN; ++j) {
            lp[i * pr[j]] = pr[j];
            if (pr[j] == lp[i]) {
                break;
            }
        }
    }
}

void factor(ll n, map<ll,ll>& pc){
    if(n == 0) return;
    if(n == 1) return;
    ll p = lp[n];
    pc[p]++;
    while(n%p == 0) n /= p;
    factor(n, pc);
}

void solve(){
    ll n; cin >> n;
    v64 a(n), b(n);
    map<ll, ll> pc;
    map<ll, ll> pc2;

    forn(i,0,n) cin >> a[i];
    forn(i,0,n) cin >> b[i];
    forn(i,0,n){
        factor(a[i], pc);
        factor(a[i]+1, pc2);
    }


    ll ans = 2;
    for(auto[p,c]: pc){
        if(c > 1){
            ans = min(ans, 0ll);
        }
        if(c == 1){
            if(pc2[p] >= 1){
                ans = min(ans, 1ll);
            }
        }
    }

    cout << ans << ln;
    return;
}

int main(){
    _;
    sieve();
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}