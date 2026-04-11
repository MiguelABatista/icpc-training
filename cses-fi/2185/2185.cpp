#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64;
typedef vector<ll> v64;

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

const ll INF = 0x3f3f3f3f3f3f3f3fll;

int main() {
    _;
    ll n, k; 
    cin >> n >> k;
    v64 p(k);
    forn(i,0,k) cin >> p[i];
    ll lim = 1<<k;
    v64 prod(lim);
    v64 sig(lim);
    prod[0] = 1;
    sig[0] = 1;
    
    ll resp = 0;
    forn(mask, 1, lim){
        ll i = 63 - __builtin_clzll(mask);
        ll pot = 1<<i;
        debug(mask);
        debug(i);
        debug(pot);
        sig[mask] = -1 * sig[mask^pot];
        if(prod[mask^pot] > n/p[i] + 1){
            prod[mask] = INF;
        }else{
            prod[mask] = prod[mask^pot]*p[i]; 
        }
        debug(sig[mask]);
        debug(prod[mask]);
        resp += sig[mask]*(n/prod[mask]);
    }
    cout << -resp << ln;
    return 0;
}
