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

void solve(){
    ll n; cin >> n;
    v64 vec(n);
    forn(i,0,n) cin >> vec[i];
    set<pair<ll,ll>> s;   

    forn(i,0,n-1){
        s.insert({vec[i+1]-vec[i], i});
    }

    v64 ub(n,INF);
    v64 lb(n);
    
    forn(i,0,n){
        if(i > 0) ub[i] = min(ub[i], vec[i]-vec[i-1]);
        if(i < n-1) ub[i] = min(ub[i], vec[i+1]-vec[i]);
    }

    ll resp = 0;
    for(auto [l, a]: s){
        ll b = a+1;
        debugv(ub);
        debugv(lb);
        if(ub[b] + ub[a] <= l) continue;
        if(lb[b] + lb[a] > l) assert(false);
        resp++;
        debug(a);
        debug(b);
        ll upb = min(ub[b], l-lb[a]);
        ll upa = min(ub[a], l-lb[b]);
        
        ll lbb = max(lb[b], l-ub[a]);
        ll lba = max(lb[a], l-ub[b]);

        ub[b] = upb;
        ub[a] = upa;

        lb[b] = lbb;
        lb[a] = lba;
        trace(cout << ln;);
    }
    cout << resp << ln;
    trace(cout << "----------\n\n");
}

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}