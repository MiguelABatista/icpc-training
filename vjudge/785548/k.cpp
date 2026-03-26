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
const ll MAXLOG = 32;


map<ll,ll> dp;

ll tenta(ll mask, ll k){
    ll potk = 1ll<<k;
    ll nxt = mask%potk;
    ll aux = mask/potk;
    return nxt|aux;
}

ll rec(ll mask){
    auto it = dp.find(mask);
    if(it != dp.end()) return it->second;
    
    
    set<ll> mext;

    forn(i,0,MAXLOG){
        ll prox = tenta(mask,i);
        if(prox == mask) continue;
        mext.insert(rec(prox));
    }


    ll resp = 0;
    while(mext.count(resp)) resp++;
    dp[mask] = resp;

    return resp;
}

int main() {
    _;

    dp[0] = 0;
    ll n; cin >> n;
    v64 vec(n);
    forn(i,0,n) cin >> vec[i];
    vector<map<ll,ll>> factors(n);
    set<ll> primos;

    forn(i,0,n){
        ll curr = vec[i];

        for(ll p = 2; p*p <= curr; p++){
            while(curr%p == 0){
                primos.insert(p);
                factors[i][p]++;
                curr /= p;
            }
        }
        if(curr == 1) continue;
        primos.insert(curr);
        factors[i][curr]++;
    }

    debugv(primos);
    v64 masks;

    for(ll p: primos){
        ll mask = 0;
        forn(i,0,n) mask |= 1ll<<factors[i][p];
        masks.push_back(mask);
    }
 
    ll ans = 0;

    for(ll mask: masks) ans ^= rec(mask);

    if(ans){
        cout << "Mojtaba" << ln;
    }else{ 
        cout << "Arpa" << ln;
    }
    return 0;
}
