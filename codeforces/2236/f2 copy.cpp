#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;
typedef vector<ll> vll;

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
#define debugm(v) trace(cout << #v ": "; for (auto xx : v) cout << xx.first << ":" << xx.second << " "; cout << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;
const ll MOD = 1'000'000'007;
const ll MAX = 500'005;
const ll MAXVP = 20;

vll fat(MAX);
vll inv(MAX);
vll invfat(MAX);

void prep(){
    fat[0] = invfat[0] = 1;
    inv[1] = 1;
    forn(i,1,MAX){
        fat[i] = (fat[i-1]*i)%MOD;
        if(i > 1) inv[i] = (MOD - (MOD / i) * inv[MOD % i] % MOD) % MOD;
        invfat[i] = (invfat[i-1]*inv[i])%MOD;
    }
}

// Bounded Solutions Counter (Inclusion-Exclusion)
//
// counts non-negative integer solutions of x1 + x2 + ... + xn = y
// subject to 0 <= xi <= u[i], via inclusion-exclusion over overflowing vars.
// requires binom(n, k) and MOD.
//
// complexity: O(2^N * N) per query


ll binom(ll a, ll b){
    if(b > a) return 0;

    return (fat[a]*((invfat[b]*invfat[a-b]%MOD)))%MOD;
}

ll resolve(vll& u, ll y) {
    ll n = sz(u), tot = 0;
    if(n == 0) return 0;
    forn(mask, 0, 1ll << n) {
        ll sum = y;
        forn(i, 0, n) if (mask & (1ll << i)) sum -= u[i] + 1;
        if (sum < 0) continue;
        ll term = binom(sum + n - 1, n - 1);
        if (__builtin_popcountll(mask) & 1) tot = (tot - term + MOD) % MOD;
        else tot = (tot + term) % MOD;
    }
    return tot;
}

// Linear Sieve (prime precomputation)
//
// Computes primes up to N in O(N) using the smallest prime factor (lp).
// pr will contain all primes <= N.
// lp[x] stores the smallest prime dividing x.
//
// complexity: O(N)

vll lp, pr;

pair<vll, vll> sieve(ll n){
    vll llp(n+1);
    vll lpr;
    forn(i, 2, n+1) {
        if (llp[i] == 0) {
            llp[i] = i;
            lpr.push_back(i);
        }
        for (ll j = 0; i * lpr[j] <= n; ++j) {
            llp[i * lpr[j]] = lpr[j];
            if (lpr[j] == llp[i]) {
                break;
            }
        }
    } 
    return {lpr, llp};
}

map<ll, ll> factor(ll n){
    map<ll, ll> mp;
    while(n > 1){
        ll p = lp[n];
        ll alpha = 0;
        while(n%p == 0){
            alpha++;
            n /= p;
        }
        mp[p] = alpha; 
    }
    return mp;
}

void solve(){
    ll n, x; cin >> n >> x;
    vll vec(n);
    forn(i,0,n) cin >> vec[i];
    map<ll,vll> vpsum;
    map<ll,ll> mpx = factor(x);

    forn(i,0,n){
        auto mp = factor(vec[i]);
        for(auto [k,v] : mp){
            vpsum[k].push_back(v);
        }
    }
    ll resp = 1;
    for(auto [p,v] : vpsum){
        ll tot = 0;
        ll vpx = mpx[p];
        mpx.erase(p);
        if(vpx != 0){
            vll freq(MAXVP);
            for(auto val : v) freq[val]++;
            forn(i,0,MAXVP){
                if(freq[i] == 0) continue;
                freq[i]--;
                vll u;
                vll accfreq(MAXVP);
                accfreq[MAXVP-1] = freq[MAXVP-1]; 
                for(ll j = MAXVP-2; j>=0;j--) accfreq[j] = accfreq[j+1] + freq[j];
                
                debugv(freq);
                debugv(accfreq);
                
                forn(j,1,vpx+1){
                    if(accfreq[j] > 0) u.push_back(accfreq[j]);
                }
                
                debug(i);
                debugv(u);
                debug(vpx);
                ll aux = resolve(u, vpx);
                debug(aux);
                tot += aux;
                freq[i]++;
            }
            debug(tot);
        }else{
            for(auto val : v) tot += val;
            tot += 1;
        }
        resp = (resp*tot)%MOD;
        
    }
    if(sz(mpx) > 0) resp = 0;
    cout << resp << ln;
}

int main() {
    _;
    prep();
    auto p = sieve(MAX);
    pr = p.first;
    lp = p.second;

    ll t; cin >> t;
    while(t--) solve();
    return 0;
}
