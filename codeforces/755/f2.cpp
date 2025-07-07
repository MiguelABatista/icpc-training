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

int main(){
    _;
    ll n; ll k;
    cin >> n >> k;
    v64 perm(n);
    vector<bool> visitados(n, false);
    vector<ll> dp(n+1,0);

    forn(i,0,n){
        cin >> perm[i];
        perm[i]--;
    }

    map<ll,ll> mp;
    ll cap = 0;
    forn(i,0,n){
        if(visitados[i]) continue;
        ll curr = i;
        ll sz = 0;
        while(visitados[curr] == false){
            sz++;
            visitados[curr] = true;
            curr = perm[curr];

        }
        mp[sz]++;
        cap += sz / 2;              
    }

    v64 aux(n+1,0);
    dp[0] = 1;
    
    for(auto& [v, c]: mp){
        forn(i,0,n+1-v){
            if(!dp[i]) continue;
            if(aux[i] == c) continue;
            if(dp[i+v] == 1) continue;
            dp[i+v] = 1;
            aux[i+v] = aux[i] + 1;
        }
        aux.assign(n+1,0);
    }

    // forn(i,0,n+1){ cout << dp[i] << " ";} cout << ln;
    ll ans = k;
    if(!dp[k]) ans++;
    ll ans_max;
    if (k <= cap) ans_max = 2 * k;
    else ans_max = min(n, k + cap);

    cout << ans << " " << ans_max << ln; 
    return 0;
}