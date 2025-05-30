#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64; 
typedef vector<ll> v64;

#define forn(i, s, e) for(ll i = (s); i < (e); i++)
#define ln "\n"

#if defined(DEBUG) || defined(debug)
    #define _ (void)0
    #define debug(x) cout << __LINE__ << ": " << #x << " = " << x << ln
#else
    #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
    #define debug(x) (void)0
#endif

const ll INF = 0x3f3f3f3f3f3f3f3fll;

ll maior_pot_2(ll l, ll r){
    ll tam = r-l;
    ll resp = 63 - __builtin_clzll(tam);
    return resp;
}

ll get_l(ll l, ll pot2){
    if((l % pot2) == 0) return l;
    
    return l + (pot2 - (l%pot2));
}

ll func(ll l1, ll r1, ll l2, ll r2){
    if(r1 <= l1) return 0;
    if(r2 <= l2) return 0;
    
    if(r1 - l1 == 1) return r2-l2;
    if(r2 - l2 == 1) return r1-l1;
    
    ll v21 = maior_pot_2(l1, r1);
    ll v22 = maior_pot_2(l2, r2);
    ll pot2 = (1<<min(v21, v22));
    
    ll lresp1, rresp1, lresp2, rresp2;
    
    lresp1 = get_l(l1, pot2);
    lresp2 = get_l(l2, pot2);
    
    rresp1 = r1 - (r1%pot2);
    rresp2 = r2 - (r2%pot2);
    
    // cout << pot2 << ln; 
    // cout << l1 << " " << r2 << " " << l2 << " " << r2 << ln;
    // cout << lresp1 << " " << rresp2 << " " << lresp2 << " " << rresp2 << ln;

    ll count = ((rresp1-lresp1)/pot2) * ((rresp2-lresp2)/pot2); 
    count += func(l1, lresp1, l2, lresp2);
    count += func(l1, lresp1, lresp2, rresp2);
    count += func(l1, lresp1, rresp2, r2);
    
    count += func(lresp1, rresp1, rresp2, r2);
    count += func(lresp1, rresp1, l2, lresp2);

    count += func(rresp1, r1, rresp2, r2);
    count += func(rresp1, r1, lresp2, rresp2);
    count += func(rresp1, r1, l2, lresp2);

    return count;
}

void solve(){
    ll l1, r1, l2, r2;
    cin >> l1 >> r1 >> l2 >> r2;

    cout << func(l1, r1, l2, r2) << ln;
}

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}