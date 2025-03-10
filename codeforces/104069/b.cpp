#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64; 
typedef vector<ll> v64;

#define forn(i, s, e) for(ll i = (s); i < (e); i++)
#define ln "\n"

#if defined(DEBUG) || defined(debug)
    #define _ (void)0
    #define debug(x) cout << __LINE__ << ": " << #x << " = " << x << ln
#else
    #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
    #define debug(x) (void)0
#endif

const ll INF = 0x3f3f3f3f3f3f3f3fll;
const ll N = 100'008;

vector<ll> lp(N+1);
vector<ll> primes;

void sieve() {
    for (ll i=2; i <= N; ++i) {
        if (lp[i] == 0) {
            lp[i] = i;
            primes.push_back(i);
        }
        for (ll j = 0; i * primes[j] <= N; ++j) {
            lp[i * primes[j]] = primes[j];
            if (primes[j] == lp[i]) {
                break;
            }
        }
    }
}

ll fatora(ll m){
    ll p = 0;
    while(primes[p]*primes[p] <= m){
        while(m%primes[p] == 0) m = m/primes[p];
        p++;
    }

    if(m != 1) return m;
    if(p == 0) return 1;
    return primes[p-1];
}

int main(){
    _; sieve();
    ll n; cin >> n;

    string best_s;
    ll max_p = 0; 
    forn(i, 0, n){
        string s; cin >> s;
        ll m; cin >> m;
        ll p = fatora(m);
        if(p > max_p){
            max_p = p;
            best_s = s;
        }
    }

    cout << best_s << ln;
    return 0;
}