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

ll aux(ll s, ll k){
    function<ll (ll)> f = [&](ll t){
        return s*k + t*(20*k-4*s)-80*t*t;
    };
    ll ans = -INF;
    ll ver = (5*k-s)/40;

    forn(i,-3,4){
        ans = max(ans, f(ver+i));
    }
    return ans;
}

void solve(){
    ll s, k; cin >> s >> k;
    ll ans = s*k;

    if(s%10 == 0){
        cout << ans << ln;
        return;
    }
    if(s%10 == 5){
        s += 5;
        k--;
        ans = max(ans, s*k);
        cout << ans << ln;
        return;
    }
    if(s%2 == 1){
        s += s%10;
        k--;
        ans = max(ans, s*k);
    }

    forn(i,0,6){
        ans = max(ans, aux(s,k));
        s += s%10;
        k--;
        ans = max(ans, s*k);

        if(k == 0) break;
    }
    cout << ans << ln;
}

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}