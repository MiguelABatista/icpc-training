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
#define _
#else
#define trace(u)
#define _ ios::sync_with_stdio(0); cin.tie(0)
#endif

#define debug(u) trace(cout << #u " = " << u << ln)
#define debugv(v) trace(cout << #v ": "; for(auto xx : v) cout << xx << " "; cout << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;

void solve(){
    ll la, ra, lb, rb;
    cin >> la >> ra >> lb >> rb;
    ll l = 0;
    ll r = min(ra-la+1, (rb-lb+1)/2);

    ll ans = 0;

    while(l <= r){
        ll m = (l+r)/2;
        ll k = m;
        if(k*(la+ra) - ((k-1)*k)/2 >= 2*k*lb + k*(2*k-1)){
            ans = m;
            l = m+1;
        }else{
            r = m-1;
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