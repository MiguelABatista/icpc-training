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

struct pile{
    ll a,b,c,d;
};

void solve(){
    ll n; cin >> n;
    vector<pile> vec(n);
    ll resp = 0;
    forn(i,0,n) cin >> vec[i].a >> vec[i].b >> vec[i].c >> vec[i].d;

    forn(i,0,n){
        auto& p = vec[i];
        if(p.d >= p.b) continue;

        if(p.a > p.c){
            resp += p.a - p.c;
            p.a = p.c;
        }

        resp += p.a;
        resp += p.b-p.d;    
    }    

    forn(i,0,n){
        auto& p = vec[i];
        if(p.c >= p.a) continue;
        resp += p.a - p.c;
    }    
    cout << resp << ln;
}

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}