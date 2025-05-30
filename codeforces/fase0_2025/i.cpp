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

struct sol{
    ll c = -INF;
    ll s = -1;
};


typedef pair<sol,sol> psol;

psol melhor(psol antiga, psol nova, ll val, ll s){
    sol concorrente;
    
    if(nova.first.s == s){
        concorrente = nova.second; 
    }else{
        concorrente = nova.first;
    }

    concorrente.s = s;
    concorrente.c += val;
    if(concorrente.c > antiga.first.c){
        antiga.second = antiga.first;
        antiga.first = concorrente;
    }else if(concorrente.c > antiga.second.c){
        antiga.second = concorrente;
    }

    return antiga;
}

int main(){
    _;
    ll n, t; cin >> n >> t;
    vector<v64> v(n, v64(t));
    forn(i, 0, n) {
        forn(j, 0, t) {
            cin >> v[i][j];
        }
    }

    forn(i, 0, n) {
        forn(j, 1, t) {
            v[i][j] += v[i][j-1];
        } 
    }

    ll l, u; cin >> l >> u;
    vector<psol> dp(t+1);

    dp[t].first.c = 0;
    dp[t].second.c = 0;
    dp[t].first.s = -1;
    dp[t].second.s = -1;

    for (ll i = t-1; i >= 0; i--) {
        forn(s,0,n){
            forn(duration, l, u+1) {
                if(i+duration > t) continue;
                ll val = 0;
                val = v[s][i+duration-1] - ( i == 0 ? 0 : v[s][i-1] );
                dp[i] = melhor(dp[i], dp[i+duration], val, s);
            }
        }
    }

    // forn(i,0,t+1) cout << dp[i].first.c << " \n"[i == t] ;
    if(dp[0].first.c <= -INF/2){
        cout << -1 << ln;
    }else{
        cout << dp[0].first.c << ln;
    }
    return 0;
}