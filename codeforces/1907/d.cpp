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

bool testa(vector<p64>& vec, ll n, ll k){
    v64 dpl(n+1);
    v64 dpr(n+1);

    forn(i,1,n+1){
        ll currl = dpl[i-1] - k;
        ll currr = dpr[i-1] + k;
        if(vec[i-1].second < currl) return false;
        if(vec[i-1].first > currr) return false;
        dpl[i] = max(currl, vec[i-1].first);
        dpr[i] = min(currr, vec[i-1].second);
    }

    return true;
}

void solve(){
    ll n; cin >> n;
    vector<p64> vec(n);
    forn(i,0,n) cin >> vec[i].first >> vec[i].second;

    ll r = 1'000'000'000;
    ll l = 0;
    ll ans = r;
    while(l <= r){
        ll mid = (l+r)/2;
        if(testa(vec, n, mid)){
            ans = mid;
            r = mid-1;
        }else{
            l = mid+1;
        }
    }
    cout << ans << ln;
}

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}