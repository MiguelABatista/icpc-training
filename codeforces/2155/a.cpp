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
    ll l = 0;
    ll w = n;
    ll cnt = 0;
    while(l > 1 || w > 1){
        ll nl = (l+1)/2 + w/2;
        ll nw = (w+1)/2;
        cnt += w/2 + l/2;
        l = nl;
        w = nw;
    }
    cnt++;
    cout << cnt << ln;
}

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}