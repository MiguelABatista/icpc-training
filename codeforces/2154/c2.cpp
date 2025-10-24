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


bool factor(ll n, set<ll>& primos){
    if(n == 0) return false;
    if(n == 1) return false;
    ll p = lp[n];
    
    if(primos.count(p)) return true;
    primos.insert(p);

    while(n%p == 0) n /= p;
    if(factor(n, primos)) return true;
    return false;
}

bool factor_test(ll n, set<ll>& primos){
    if(n == 0) return false;
    if(n == 1) return false;
    ll p = lp[n];
    
    if(primos.count(p)) return true;

    while(n%p == 0) n /= p;
    if(factor_test(n, primos)) return true;
    return false;
}


ll process_all(ll n, ll cost, set<ll>& primos, ll bound){
    ll ans = INF;
    
    for(ll p: primos) if(n % p != 0){
        ans = min(ans , cost*(p-(n%p)) );
    }
    return ans;
}


void solve(){
    ll n; cin >> n;
    vector<p64> ba(n);
    set<ll> primos;

    forn(i,0,n) cin >> ba[i].second;
    forn(i,0,n) cin >> ba[i].first;
    sort(ba.begin(), ba.end());

    forn(i,0,n){
        if(factor(ba[i].second,primos)){
            cout << 0 << ln;
            return;
        }
    }


    ll ans = ba[0].first + ba[1].first;
    forn(i,0,n){
        if(ba[i].first >= ans) break;
        if(factor_test(ba[i].second+1, primos)){
            ans = min(ans, ba[i].first);
        }
    }

    ll aux = process_all(ba[0].second, ba[0].first, primos, ans);
    ans = min(ans, aux);
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