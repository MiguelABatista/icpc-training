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
    v64 a(n);
    v64 b(n);
    
    multiset<pair<ll,ll>> s;
    
    forn(i,0,n){
        cin >> a[i];
    }
    forn(i,0,n){
        cin >> b[i];
    } 

    forn(i,0,n){
        s.insert({a[i]+b[i], i});
    }

    string quem = "ab";
    ll resp = 0;
    forn(i,0,n){
        auto it = prev(s.end());
        auto aux = *it;
        s.erase(it);
        ll idx = aux.second;
        
        if(i%2 == 0){ // vez do a
            resp += a[idx]-1;
        }else {//vez do b
            resp -= b[idx]-1;
        }
    }
    cout << resp << ln;
}

int main(){ 
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}