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
    ll n, m, k; cin >> n >> m >> k;
    vector<p64> vec(k);
    ll x, y;
    cin >> x >> y;
    ll p = (x+y)%2;
    bool ruim = false;
    forn(i,0,k){
        cin >> vec[i].first;
        cin >> vec[i].second;
        if((vec[i].first+vec[i].second)%2 == p) ruim = true;
    }

    if(ruim){
        cout << "NO" << ln;  
    }else{
        cout << "YES" << ln;
    }
}

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}