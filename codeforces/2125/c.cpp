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

inline ll func(ll l, ll r, ll d){
    ll lb, rb;
    lb = ((l+d-1)/d)*d;
    rb = (r/d)*d;
    return (rb-lb)/d+1;
}

void solve(){
    ll l, r;
    cin >> l >> r;
    ll ans = r-l+1;
    ans -= func(l,r,2);
    ans -= func(l,r,3);
    ans -= func(l,r,5);
    ans -= func(l,r,7);

    ans += func(l,r,6);
    ans += func(l,r,10);
    ans += func(l,r,14);
    ans += func(l,r,15);
    ans += func(l,r,21);
    ans += func(l,r,35);

    ans -= func(l,r, 30);
    ans -= func(l,r, 42);
    ans -= func(l,r, 70);
    ans -= func(l,r, 105);

    ans += func(l,r, 210);

    cout << ans << ln;
}

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}