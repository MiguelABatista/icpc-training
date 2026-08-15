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

    vector<vll> dpup(n, vll(n, -INF));
    vector<vll> dplo(n, vll(n, +INF));

    function<ll (ll, ll)> rec_upp = [&](ll l, ll r){
        if(dpup[l][r] != -INF) return dpup[l][r];
        
        if(l == r) return dpup[l][r] = vec[l];
        if(l+1 == r) return dpup[l][r] = max(vec[l], vec[r]);

        ll ansl = vec[l] + min(rec_upp(l+2, r), rec_upp(l+1,r-1));  
        ll ansr = vec[r] + min(rec_upp(l, r-2), rec_upp(l+1,r-1));  

        return dpup[l][r] = max(ansl, ansr);
    };


    function<ll (ll, ll)> rec_low = [&](ll l, ll r){
        if(dplo[l][r] != +INF) return dplo[l][r];
        
        // trace(cout << l << " " << r << ln;)
        if(l == r) return dplo[l][r] = vec[l];
        // debug(1);
        if(l+1 == r) return dplo[l][r] = min(vec[l], vec[r]);
 
        ll ansl = vec[l] + max(rec_low(l+2, r), rec_low(l+1,r-1));  
        ll ansr = vec[r] + max(rec_low(l, r-2), rec_low(l+1,r-1));  

        return dplo[l][r] = min(ansl, ansr);
    };
 
    rec_low(0,n-1);
    rec_upp(0,n-1);

    trace( 
        cout << "    "; debugv(vec);
        forn(i,0,n){debugv(dpup[i]);}
        cout << "    "; debugv(vec);
        forn(i,0,n){debugv(dplo[i]);}
    )
    

    bool grande_esq = false;
    bool grande_dir = false;
    if(vec[0] == 1){
        debug(0);
        ll lo = rec_low(1,n-2);
        ll up = rec_upp(1,n-2);
        bool dir = (lo <= -1 && -1 <= up);
        trace(cout << __LINE__ << ": " << lo << " " << up << ln;)
        lo = rec_low(2,n-1);
        up = rec_upp(2,n-1);
        trace(cout << __LINE__ << ": " << lo << " " << up << ln;)
        bool esq = (lo <= -1 && -1 <= up);
        grande_esq = esq&&dir;
    }
    if(vec[n-1] == 1){
        debug(n-1);
        ll lo = rec_low(1,n-2);
        ll up = rec_upp(1,n-2);
        trace(cout << __LINE__ << ": " << lo << " " << up << ln;)
        bool esq = (lo <= -1 && -1 <= up);
        lo = rec_low(0,n-3);
        up = rec_upp(0,n-3);
        trace(cout << __LINE__ << ": " << lo << " " << up << ln;)
        bool dir = (lo <= -1 && -1 <= up);
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