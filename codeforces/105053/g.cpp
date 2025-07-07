#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
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
const ll MAXN = 200010;

v64 primes;
vector<bool> is_comp(MAXN, false);
vector<v64> divisors(MAXN);
vector<ll> first_prime(MAXN);
vector<map<ll,ll>> fatoracao;

void sieve(ll n){
    first_prime[1] = 1;

    forn(i, 2, n){
        if(!is_comp[i]){
            primes.push_back(i);
            first_prime[i] = i;
        }

        forn(j, 0, primes.size()){
            if(i*primes[j]>n) break;
            is_comp[i*primes[j]] = true;
            first_prime[i*primes[j]] = primes[j];

            if(i%primes[j] == 0) break;
        }
    }
}

void get_div(ll n){
    forn(i,1,n){
        for(ll j = i; j <= n; j += i){
            divisors[j].push_back(i);
        }
    }
}

ld calc_prob_div(vector<ld> &prob, ll target){
    ld p = 0;

    for(ll d: divisors[target]){
        p += prob[d];
    }

    return p;
}

ll get_rep(ll a, ll k){
    ll ans = 1;
    for(auto& [p,e]: fatoracao[a]){
        if(k % p == 0) continue;
        forn(i,0,e) ans *= p;
    }
    return ans;
}

int main(){
    _; ll n, sum = 0; cin >> n;
    sieve(n+10);
    get_div(n+10);

    vector<ll> w(n+1);
    vector<ld> prob(n+1), prob_div(n+1);
    fatoracao.resize(n+1);

    forn(i, 1, n+1){
        cin >> w[i];
        sum += w[i];
    }

    forn(i, 1, n+1) prob[i] = (ld)w[i]/(ld)sum;
    debug(1);
    forn(i, 1, n+1) prob_div[i] = calc_prob_div(prob, i); // nlog(n) cnst boa
    forn(i, 2, n+1){
        fatoracao[i] = fatoracao[i/first_prime[i]];
        fatoracao[i][first_prime[i]]++;
    }

    // forn(i, 1, n+1){
    //     debug(i);
    //     for(auto [p,e] : fatoracao[i]){
    //         cout << "(" << p << ", "<< e << ") ";
    //     }
    //     cout << ln;
    // }

    vector<ld> dp(n+1);
    
    for(ll i = n; i >= 1; i--){
        ld ans = 0;
        forn(k,2,n+1){
            if(i*k > n) break;
            ll rep = get_rep(i,k);
            ll fixo = i*k/rep;
            ld p = 0;
            for(ll d: divisors[rep]){
                p += prob[d*fixo];
            }
            ans += p*(dp[i*k]+1);
        }   
        ans+= prob_div[i];
        dp[i] = ans/(1- prob_div[i]);

    }

    cout << fixed << setprecision(18) << dp[1] << ln;
    // forn(i,0,n+1) cout << fixed << setprecision(18) << dp[i] << ln ;
    // cout << ln;
    // forn(i,0,n+1) cout << fixed << setprecision(18) << prob[i] << ln ;
    // cout << ln;
    // forn(i,0,n+1) cout << fixed << setprecision(18) << prob_div[i] << ln ;

    return 0;
}