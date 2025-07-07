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

    ll n; cin >> n;
    if(n == 1){
        ll g, r; cin >> g >> r;
        cout << "N" << ln;
        return 0;
    }

    ll delta = 0;
    ll sum = 0;
    bool haszero = false;
    map<ll,ll> mp;

    forn(i,0,n){
        ll g,r;
        cin >> g >> r;
        if(g == 0) haszero = true;
        
        mp[g]++;
        sum += g;
        delta = gcd(delta, r);
    }

    vector<bool> dp(sum+1, 0);
    vector<ll> aux(sum+1, 0);
    
    dp[0] = 1;

    for(auto& [v, c]: mp){
        forn(i,0,sum+1-v){
            if(!dp[i]) continue;
            if(aux[i] == c) continue;
            if(dp[i+v] == 1) continue;
            dp[i+v] = 1;
            aux[i+v] = aux[i] + 1;
        }
        aux.assign(sum+1,0);
    }

    ll l = 1;
    ll r = sum;

    if(haszero){
        l = 0;
        r = sum+1;
    }

    forn(i,l,r){
        if(!dp[i]) continue;
        if(abs(sum-2*i) % delta == 0){
            cout << "Y" << ln;
            return 0;
        }
    }
    cout << "N" << ln;
    return 0;
}