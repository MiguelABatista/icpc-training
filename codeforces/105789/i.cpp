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
const ll MAXVAL = 1'000'010;

v64 prox(MAXVAL, -1);
v64 ant(MAXVAL, -1);

void add(ll val, ll idx){
    ll a = ant[idx];
    prox[val] = idx;
    ant[val] = a;
    
    prox[a] = val;
    ant[idx] = val;
}

void remove(ll val){
    ll a = ant[val];
    ll p = prox[val];
    
    ant[val] = prox[val] = -1;

    prox[a] = p;
    ant[p] = a;
}

ll solve(ll n){
    v64 vec(2*n);
    v64 dp(2*n, 0);
    forn(i,0,n){
        ll aux; cin >> aux;
        vec[i] = vec[i+n] = aux;
    }
    
    if(prox[vec[2*n-1]] != -1) dp[2*n-1] = 1;

    ll best = -1;
    for(ll i = 2*n-2; i >=0; i--){
        if(prox[vec[i]] == vec[i+1]){
            dp[i] = dp[i+1] + 1;
        }else if (prox[vec[i]] != -1){
            dp[i] = 1;
        }else{
            dp[i] = 0;
        }
        best = max(best, dp[i]);
    }

    if(dp[0] == 2*n) return INF;
    return best;
}

int main(){
    _;
    ll n; cin >> n;
    
    v64 ini(n);
    for(ll& v: ini) cin >> v;

    forn(i,0,n){
        prox[ini[i]] = (i != n-1 ? ini[i+1] : ini[0]);
        ant[ini[i]] = (i != 0 ? ini[i-1] : ini[n-1]);
    }

    ll q; cin >> q;
    while(q--){
        char c; cin >> c;
        if(c == '?'){
            ll aux; cin >> aux;
            ll resp = solve(aux);
            if(resp == INF){
                cout << '*' << ln;
            } else{
                cout << resp << ln;
            }
        }
        if(c == '-'){
            ll aux; cin >> aux;
            remove(aux);
        }
        if(c == '+'){
            ll a, b; cin >> a >> b;
            add(a, b);
        }
    }
    return 0;
}