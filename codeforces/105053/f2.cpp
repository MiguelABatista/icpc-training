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

const ll MAXN = 200'010;

char resp = 'A';

int solve(v64 gs, v64 rs, ll n){
    if(n == 1){
        cout << "N" << ln;
        resp = 'N';
        return 0;
    }

    ll delta = 0;
    ll sum = 0;
    bool haszero = false;
    map<ll,ll> mp;

    forn(i,0,n){
        ll g,r;
        g = gs[i];
        r = rs[i];

        if(g == 0) haszero = true;
        
        mp[g]++;
        sum += g;
        delta = gcd(delta, r);
    }

    vector<bool> dp(MAXN, 0);
    vector<ll> aux(MAXN, 0);
    
    dp[0] = 1;

    for(auto& [v, c]: mp){
        forn(i,0,MAXN-v){
            if(!dp[i]) continue;
            if(aux[i] == c) continue;
            dp[i+v] = 1;
            aux[i+v] = aux[i] + 1;
        }
        aux.assign(MAXN,0);
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
            resp = 'Y';

            return 0;
        }
    }
    cout << "N" << ln;
    resp = 'N';

    return 0;
}

mt19937_64 rng((ll) chrono::steady_clock::now().time_since_epoch().count());

ll uniform(ll l, ll r){
	uniform_int_distribution<ll> uid(l, r);
	return uid(rng);
}

int main(){
    ll cnt = 0;
    while(true){
        cout << cnt << ln;
        ll n = 2;
        v64 gs = {uniform(0,10), uniform(0,10)};
        v64 rs = {uniform(1,10), uniform(1,10)};
        
        solve(gs, rs, n);

        if(abs(gs[0]-gs[1]) % gcd(rs[0], rs[1]) == 0){
            if(resp == 'N'){
                cout << resp << ln;
                cout << gs[0] << " " << gs[1] << ln;
                cout << rs[0] << " " << rs[1] << ln;
                break;
            }
        }else{       
            if(resp == 'Y'){
                cout << resp << ln; 
                cout << gs[0] << " " << gs[1] << ln;
                cout << rs[0] << " " << rs[1] << ln;
                break;
            }
        }
        cnt++;
    }

}