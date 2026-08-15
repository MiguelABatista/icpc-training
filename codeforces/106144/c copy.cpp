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
const ll INF = 999;
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

    vector<vll> dpup(n, vll(n, -INF));
    vector<vll> dplo(n, vll(n, +INF));
    vector<vector<pll>> dp(n, vector<pll>(n, {+INF, -INF}));

    function<pll (ll, ll)> rec = [&](ll l, ll r){
        if(dp[l][r] != (pll){+INF, -INF}) return dp[l][r];
        
        if(l == r) return dp[l][r] = {vec[l], vec[l]};
        if(l+1 == r) return dp[l][r] = {min(vec[l], vec[r]), max(vec[l], vec[r])};

        pll dpl2r0 = rec(l+2, r);
        pll dpl1r1 = rec(l+1, r-1);
        pll dpl0r2 = rec(l, r-2);


        ll ansl_upp = vec[l] + ;
        ll ansl_low = 0;


        ll ansr_upp = 0;
        ll ansr_low = 0;
        ll ans_low = min(ansl_low, ansr_low);
        ll ans_upp = max(ansl_upp, ansr_upp);
        return dp[l][r] = {ans_low, ans_upp};
    };


    function<ll (ll, ll)> rec_low = [&](ll l, ll r){
        if(dplo[l][r] != +INF) return dplo[l][r];
        
        if(l == r) return dplo[l][r] = vec[l];
        if(l+1 == r) return dplo[l][r] = min(vec[l], vec[r]);
 
        ll ansl = vec[l] + max(rec_low(l+2, r), rec_low(l+1,r-1));  
        ll ansr = vec[r] + max(rec_low(l, r-2), rec_low(l+1,r-1));  

        return dplo[l][r] = min(ansl, ansr);
    };
 
    ll lo = rec_low(0,n-1);
    ll up = rec_upp(0,n-1); 
    trace( 
        cout << "    "; debugv(vec);
        forn(i,0,n){debugv(dpup[i]);}
        cout << "    "; debugv(vec);
        forn(i,0,n){debugv(dplo[i]);}
    )
    if(lo <= 0 && 0 <= up) cout << "Monocarp" << ln;
    else cout << "Polycarp" << ln;

    trace(cout << "------------------------------\n\n";)
}

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}