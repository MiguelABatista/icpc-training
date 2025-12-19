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
#define debugp(v) trace({cout << #v": "; for (auto x : v) cout<< x.first << ":" << x.second << " "; cout << ln;})
#define debug(x) trace(cout << __LINE__ << ": " #x " = " << x << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;

void solve(){
    ll n, c; cin >> n >> c;

    v64 vec(n);
    v64 inv(n);
    forn(i,0,n) cin >> vec[i];
    
    set<p64> ord; 
    
    forn(i,0,n) ord.insert({-vec[i], i});


    v64 resp(n);
    ll idxaux = -1;
    p64 p = *ord.begin();
    
    if(p < (p64){-(vec[0]+c), 0}){
        idxaux = p.second;
    }
    
    forn(i,0,n){
        c += vec[i];
        auto[ bval, bidx] = *ord.begin();
        bval *= -1;
        
        if(c >= bval) resp[i] = i;
        else resp[i] = i+1;
        
        ord.erase({-vec[i], i});        
    }
    if(idxaux != -1) resp[idxaux] = 0;
    
    forn(i,0,n) cout << resp[i] << " ";; cout << ln;
    trace(cout << "--------\n\n");
}

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}