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

const ll MOD = 998244353;
const ll MAXN = 1000;

v64 primes;
vector<bool> is_comp(MAXN,false);
ll phi[MAXN];
ll cum_sum[MAXN];

void sieve(ll n){
  phi[1] = 1;
  forn(i,2,n){
    if(!is_comp[i]){
      phi[i] = i-1;
      primes.push_back(i);
    }
    
    forn(j,0,primes.size()){
      if(i*primes[j] >= n) break;
      is_comp[i*primes[j]] = true;
      
      if(i % primes[j] == 0){
        phi[i*primes[j]] = phi[i]*primes[j]; 
        break;
      }
      phi[i*primes[j]] = phi[i]*phi[primes[j]];    
    }
  }
}

ll expo(ll b, ll e, ll p) {
    ll ret = 1;
    while (e) {
        if (e % 2) ret = ret * b % p;
        e /= 2, b = b * b % p;
    }
    return ret;
}

bool is_res(ll p, ll v){
    return (expo(v,(p-1)/2, p) == 1);
}

bool test(ll p1, ll p2, ll p3){
    bool valid = true;
    
    if(!is_res(p1, p2)) valid = false;
    if(!is_res(p1, p3)) valid = false;
    if(!is_res(p2, p3)) valid = false;
    if(!is_res(p2, p1)) valid = false;
    if(!is_res(p3, p1)) valid = false;
    if(!is_res(p3, p2)) valid = false;

    return valid;
}

int main(){
    _;
    sieve(MAXN);
    forn(i,0,primes.size()-3){
        if(test(primes[i], primes[i+1], primes[i+2])){
            cout << i << ln;
            cout << primes[i] << " " << primes[i+1] << " " << primes[i+2] << ln;
            cout << primes[i+1] - primes[i] << " "  << primes[i+2] - primes[i] << ln;
        }
    }
    return 0;
}