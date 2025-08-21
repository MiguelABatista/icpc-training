#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64; 
typedef vector<ll> v64;

#define forn(i, s, e) for(ll i = (s); i < (e); i++)
#define ln "\n"

#if defined(DEBUG)
    #define _ (void)0
    #define debug(x) cout << __LINE__ << ": " << #x << " = " << x << ln
#else
    #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
    #define debug(x) (void)0
#endif

const ll INF = 0x3f3f3f3f3f3f3f3fll;
const ll MAXN = 1000000;

v64 primes;
vector<bool> is_comp(MAXN, false);

void sieve(ll n){
    forn(i, 2, n){
        if(!is_comp[i]){
            primes.push_back(i);
        }

        forn(j, 0, primes.size()){
            if(i*primes[j]>=n) break;
            is_comp[i*primes[j]] = true;

            if(i%primes[j] == 0) break; 
        }
    }
}

vector<ll> dp(MAXN, 0);

ll take_dig(ll n, ll pot){
    return (n/(10*pot))*pot + (n%pot);
}

ll resp(ll n){
    if(n < MAXN) return dp[n];

    ll p = 0;
    while(primes[p]*primes[p] <= n){
        if(n%primes[p] == 0) return 0;
        p++;
    }

    ll pot = 1, aux = 0;
    while(pot <= n){
        aux = max(aux, 1+resp(take_dig(n, pot)));
        pot *= 10;
    }

    return aux;
}

int main(){
    _; sieve(MAXN);
    ll n; cin >> n;

    forn(i, 2, MAXN){
        if(is_comp[i]) continue;
        ll pot = 1;
        while(pot <= i){
            dp[i] = max(dp[i], 1+dp[take_dig(i, pot)]);
            pot *= 10;
        }
    }

    cout << resp(n) << ln;

    return 0;
}