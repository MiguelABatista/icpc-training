#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef __int128_t ll128;
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
#define debug(x) trace(cout << __LINE__ << ": " #x " = " << x << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;
const ll MAXP = 1'000'005;
// const ll MAXP = 1005;

inline ll128 modmul(ll128 a, ll128 b, ll128 M){ 
    return a*b%M;
};

ll128 modpow(ll128 b, ll128 e, ll128 mod){
    ll128 ans = 1;
    for(; e; b = modmul(b, b, mod), e /= 2)
        if(e & 1) ans = modmul(ans, b, mod);
    return ans;
}

bool isPrime(ll128 n){
    if(n < 2 || n % 6 % 4 != 1) return (n | 1) == 3;
    ll128 A[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022}, s = __builtin_ctzll(n-1), d = n >> s;
    for (ll128 a : A) {
        ll128 p = modpow(a%n, d, n), i = s;
        while(p != 1 && p != n-1 && a % n && i--)
            p = modmul(p, p, n);
        if(p != n-1 && i != s) return 0;
    } 
    return 1;
}

// Linear Sieve (prime precomputation)
//
// Computes primes up to N in O(N) using the smallest prime factor (lp).
// pr will contain all primes <= N.
// lp[x] stores the smallest prime dividing x.
//
// complexity: O(N)
// escrito pelo gpt, cuidado

const ll N = MAXP;
v64 lp(N+1), pr;

void sieve(){
    forn(i, 2, N+1) {
        if (lp[i] == 0) {
            lp[i] = i;
            pr.push_back(i);
        }
        for (ll j = 0; i * pr[j] <= N; ++j) {
            lp[i * pr[j]] = pr[j];
            if (pr[j] == lp[i]) {
                break;
            }
        }
    }
}

int main(){
    _; 
    sieve();
    v64 pmag;
    debugv(pr);
    for(ll p : pr){
        ll guess = p*p + 4;
        debug(guess);
        if(isPrime(guess)) pmag.push_back(guess);
    }
    
    ll q; cin >> q;

    debugv(pmag);
    forn(i,0,q){
        ll l; ll r;
        cin >> l >> r;

        if(l % 2 == 1) l--;
        if(r % 2 == 1) r++;
        
        auto itl = lower_bound(pmag.begin(), pmag.end(), l); 
        auto itr = lower_bound(pmag.begin(), pmag.end(), r); 
        cout << (ll)(itr-itl) << ln;
    }
    return 0;
}