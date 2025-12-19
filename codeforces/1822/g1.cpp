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
const ll MAXA = 1'000'000'001;
v64 freq(MAXA);

ll bound(ll val){
    return (ll)sqrt(MAXA/val)+1;
}

void solve(){
    ll n; cin >> n;
    v64 vec(n);
    forn(i,0,n) cin >> vec[i];
    set<ll> s;
    forn(i,0,n) s.insert(vec[i]);
    forn(i,0,n) freq[vec[i]]++;

    ll resp = 0;

    for(ll k: s){
        ll v = freq[k];
        if(v == 0) continue;
        resp += (v*(v-1)*(v-2));
        forn(b,2,bound(k)) resp += v*freq[k*b]*freq[k*b*b];
    }

    for(ll k: s) freq[k] = 0;
    cout << resp << ln;
}

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}