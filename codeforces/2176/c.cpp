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
    v64 pares, imp;
    
    forn(i,0,n){
        if(vec[i]&1) imp.push_back(vec[i]);
        else pares.push_back(vec[i]);
    }
    sort(imp.rbegin(), imp.rend());
    sort(pares.rbegin(), pares.rend());

    v64 resp(n, 0);

    if(sz(imp) == 0){
        forn(i,0,n) cout << resp[i] << " ";; cout << ln;
        return;
    }
    if(sz(pares) == 0){
        forn(i,0,n) resp[i] = (((i+1)&1) ? imp[0] : 0);
        forn(i,0,n) cout << resp[i] << " ";; cout << ln;
        return;
    }

    resp[0] = imp[0];
    ll nimp = sz(imp);
    forn(i,0,sz(pares)){ 
        resp[i+1] = resp[i] + pares[i];
    } 

    debugv(resp);
    ll idx = sz(pares);
    forn(i,idx+1,n){
        ll amt = i-sz(pares)+1;
        if(amt%2 == 1){
            resp[i] = resp[idx];
        }else if(amt+1 <= nimp){
            resp[i] = (idx == 0 ? 0 : resp[idx-1]);
        }else{ 
            resp[i] = 0;
        }
    }
    forn(i,0,n) cout << resp[i] << " ";;cout<<ln;
    trace(cout << "--------------\n\n";);
}

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}