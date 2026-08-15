#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pll;
typedef vector<ll> vll;

#define forn(i,s,e) for (ll i=(s); i<(e); i++)
#define sz(u) ((ll) u.size())
#define ln "\n"

#ifdef DEBUG
#define trace(u) u
const ll INF = 99;
#define _
#else
#define trace(u)
#define _ ios::sync_with_stdio(0); cin.tie(0)
const ll INF = 0x3f3f3f3f3f3f3f3fll;
#endif

#define debug(u) trace(cout << #u " = " << u << ln)
#define debugv(v) trace(cout << #v ": "; for(auto xx : v) cout << setw(4) << xx << " "; cout << ln)


void solve(){
    ll n; cin >> n;
    string s; cin >> s;
    vll vec(n, 1);
    forn(i,0,n) if(s[i] == ')') vec[i]  = -1;

    vector<vll> dp(n, vll(n, +INF));

    function<ll (ll, ll)> rec = [&](ll l, ll r){
        if(dp[l][r] != +INF) return dp[l][r];
        
        if(l == r) return dp[l][r] = min(0ll,vec[l]);
        if(l+1 == r) return dp[l][r] = min({vec[l], vec[r], 0ll});
 
        ll ansl = vec[l] + max(rec(l+2, r), rec(l+1,r-1));  
        ll ansr = vec[r] + max(rec(l, r-2), rec(l+1,r-1));  

        return dp[l][r] = min({ansl, ansr, 0ll});
    };
 
    rec(0,n-1);

    trace( 
        cout << "    "; debugv(vec);
        forn(i,0,n){debugv(dp[i]);}
    )
    
    bool grande_esq = false;
    bool grande_dir = false;
    if(vec[0] == 1){
        ll lo = rec(1,n-2);
        bool dir = lo <= -1;
        lo = rec(2,n-1);
        bool esq = lo <= -1;
        grande_esq = esq&&dir;
    }
    if(vec[n-1] == 1){
        ll lo = rec(1,n-2);
        bool esq = lo <= -1 ;
        lo = rec(0,n-3);
        bool dir = lo <= -1;
        grande_dir = esq&&dir;
    }

    if(grande_esq || grande_dir) cout << "Monocarp" << ln;
    else cout << "Polycarp" << ln; 
    trace(cout << "------------------------------\n\n";)
} 

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}