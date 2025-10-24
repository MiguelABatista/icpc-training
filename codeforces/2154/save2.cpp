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

bool factor(ll n, set<ll>& primos, set<ll>& pa){
    if(n == 0) return;
    if(n == 1) return;
    ll p = lp[n];
    pa.insert(p);
    
    if(primos.count(p)) return true;
    else primos.insert(p);
    
    while(n%p == 0) n /= p;
    if(factor(n, primos, pa)) return true;
    return false;
}

bool process(ll ni, ll n_, ll cost, 
    map<ll,ll>& new_cost, set<ll>& primos, set<ll>& avoid){
    ll n = n_;
    if(n == 0) return false;
    if(n == 1) return false;
    
    
    while(n > 1){
        ll p = lp[n];
        if(primos.count(p) && avoid.count(p) == 0){
            ll amount = p - ni%p;
            auto it = new_cost.find(p);
            if(it == new_cost.end()) new_cost[p] = cost*amount;
            else new_cost[p] = min(it->second, cost*amount);
            return true;
        }
        while (n%p == 0) n/=p;
    }

    return process(ni, n_+1, cost, new_cost, primos, avoid);    
}

void solve(){
    ll n; cin >> n;
    v64 a(n), b(n);
    vector<set<ll>> pa(n);
    set<ll> primos;

    forn(i,0,n) cin >> a[i];
    forn(i,0,n) cin >> b[i];
    forn(i,0,n){
        if(factor(a[i], primos, pa[i])){
            cout << 0 << ln;
            return;
        }
    }


    ll ans = INF;

    map<ll, ll> new_cost;
    forn(i,0,n){
        while(process(a[i], a[i], new_cost, primos, pa[i]));
    }
    
    ll min1 = INF;
    ll min2 = INF;
    forn(i,0,n){
        if(b[i] <= min1){
            min2 = min1;
            min1 = b[i];
        }else if(b[i] < min2){
            min2 = b[i];
        }
    }
    debug(min1);
    debug(min2);
    ans = min(ans, min1+min2);
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