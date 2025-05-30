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
const ll MAXA = 100'010;
const ll MOD  = 998244353;
ll NADA = 0;
inline ll sum(ll a, ll b) { a += b; if (a >= MOD) a -= MOD; return a; }
inline ll sub(ll a, ll b) { a -= b; if (a < 0)  a += MOD; return a; }
inline ll mult(ll a, ll b) { return (a * b) % MOD; }

inline ll pot(ll base, ll exp) {
    long long res = 1;
    while (exp) {
        if (exp & 1) res = mult(res, base);
        base = mult(base, base);
        exp >>= 1;
    }
    return res;
}

inline ll inv_mod(ll a) {return pot(a, MOD-2);}

vector<ll> primes;
vector<char> is_comp(MAXA + 1, 0);
vector<ll> mu(MAXA + 1, 0);
vector<ll> pot2(MAXA + 1, 1), g(MAXA + 1, 0), f(MAXA + 1, 0), cnt(MAXA + 1, 0);
vector<vector<pair<ll,ll>>> valid_divisors(MAXA + 1);
vector<vector<ll>> divisors(MAXA + 1);

void calc_divisores(){
    forn(i,1,MAXA+1){
        for(ll j = i; j <= MAXA; j += i){
            divisors[j].push_back(i);
        } 
    }
}

void build_contrib() {
    for (ll i = 1; i <= MAXA; ++i){
        for (ll d : divisors[i]) {
            ll m = mu[i / d];
            if (m) valid_divisors[i].emplace_back(d, m);
        }
    }
}

void sieve(ll n) {      
    mu[1] = 1;
    for (ll i = 2; i < n; ++i) {
        if (!is_comp[i]) {
            mu[i] = -1;
            primes.push_back(i);
        }
        for (ll j = 0; j < primes.size(); ++j) {
            ll prod = i * primes[j];
            if (prod >= n) break;
            ll idx = prod;
            is_comp[idx] = 1;
            if (i % primes[j] == 0) {
                mu[idx] = 0;
                break;
            }
            mu[idx] = mu[i] * mu[primes[j]];
        }
    }
}

inline void update_f(ll val, bool grow){
    ll old_v = f[val];
    ll new_v = grow ? pot2[++cnt[val]] : pot2[--cnt[val]]; 
    new_v = sub(new_v,1);
    f[val] = new_v;
    
    for(auto &[d, mu_] : valid_divisors[val]){
        // ll m = mu[val/d];
        ll m = 1;
        NADA += m;
        if(mu_ == 1){
            g[d] = sum(g[d], sub(new_v, old_v));
        }else{
            g[d] = sum(g[d], sub(old_v, new_v));
        }
    }
}

int main() {
    _;

    for (ll i = 1; i <= MAXA; ++i) pot2[i] = sum(pot2[i - 1], pot2[i - 1]);
    
    sieve(MAXA);
    calc_divisores();
    build_contrib();

    ll n; cin >> n;
    ll dem = pot(sub(pot2[n], 1), MOD - 2); 
    v64 vec(n);
    
    forn(i,0,n) cin >> vec[i];
    
    forn(i,0,n){
        for(ll d: divisors[vec[i]]){
            cnt[d]++; 
        }
    }
    
    forn(i,0,MAXA+1){
        f[i] = sub(pot2[cnt[i]],1);
    }
    
    for(ll i = MAXA; i > 0; i--){
        ll ans = f[i];
        for(ll j = 2*i; j<= MAXA; j += i){
            ans = sub(ans, g[j]);
        }
        g[i] = ans;
    }

    ll q;
    cin >> q;
    forn(i,0,q){
        ll t; cin >> t;
        if(t == 1){
            ll x; cin >> x;
            cout << mult(g[x],dem) << ln;
            continue;
        }
        ll idx, x;
        cin >> idx >> x;
        idx--;
        ll old = vec[idx];
        for(ll d : divisors[old]){
            update_f(d, false);
        }
        for(ll d : divisors[x]){
            update_f(d, true);
        }
        vec[idx] = x;
    }
    return 0;
}
