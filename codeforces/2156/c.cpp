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
const ll MAXN = 200'005;

v64 divs[MAXN];

void prepro(){
    forn(i,2,MAXN){
        for(ll j = i; j < MAXN; j += i){
            divs[j].push_back(i);
        }
    }
}

void solve(){
    ll n, k; cin >> n >> k;
    v64 vec(n);
    forn(i,0,n) cin >> vec[i];
    sort(vec.begin(), vec.end());
    v64 divcount(n+1, 0);

    ll ans = 1;
    ll d = 2;

    forn(i,0,n){
        for(ll x: divs[vec[i]]){
            divcount[x]++;
        }
        while(4*d < (i == n-1 ? 4*(n+1) : vec[i+1])){
            if(divcount[d] + k >= i+1) ans = max(ans, d);
            d++;
        }        
    }

    forn(i,0,n+1){
        if(divcount[i] + k >= n) ans = max(ans, i);
    }
    cout << ans << ln;
}

int main(){
    _;
    prepro();
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}