#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64; 
typedef vector<ll> v64;

#define forn(i, s, e) for(ll i = (s); i < (e); i++)
#define sz(x) ((ll) x.size())
#define ln "\n"

#ifdef DEBUG
    #define trace(x) x
    #define _ (void)0
#else
    #define trace(x) (void)0
    #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
#endif

#define debugv(v) trace({cout << #v": "; for (auto x : v) cout<< x << " "; cout << ln;})
#define debug(x) trace(cout << __LINE__ << ": " #x " = " << x << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;

bool testa(ll h, v64& vec, ll n){
    vector<bool> bom(n, 0);

    forn(i,0,n){
        if(vec[i] <= h){
            bom[i] = 1;
        }
        if(i > 0 && bom[i-1] && abs(vec[i-1] - vec[i]) <= h) bom[i] = 1;
    }

    for(ll i = n-1; i>=0 ;i--){
        if(i < n-1 && bom[i+1] && abs(vec[i+1] - vec[i]) <= h) bom[i] = 1;
    }

    bool tudo_bom = true;
    forn(i,0,n) if(!bom[i]) tudo_bom = false;
    return tudo_bom;
}

void solve(ll c){
    ll n; cin >> n;
    v64 vec(n);
    forn(i,0,n) cin >> vec[i];

    ll l = 0;
    ll r = 1'000'000'000;
    ll ans = r;
    while(l <= r){
        ll mid = (r+l)/2;
        debug(mid);
        if(testa(mid, vec, n)){ 
            debug("bom"); 
            r = mid-1;
            ans = mid;
        }else{
            debug("ruim"); 
            l = mid+1;
        }
    }
    
    cout << "Case #" << c << ": " << ans << ln; 
}

int main(){
    _;
    ll t; cin >> t;
    forn(c,1,t+1) solve(c);
    return 0;
}