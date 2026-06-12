#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;
typedef vector<ll> vll;

#define forn(i, s, e) for (ll i = (s); i < (e); i++)
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
#define debugv(v) trace(cout << #v ": "; for (auto xx : v) cout << xx << " "; cout << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;

int main() {
    _;
    ll n, k; cin >> n >> k;
    vll vec(n);
    ll x, a, b, c; 
    cin >> x >> a >> b >> c;
 
    forn(i,0,n){
        vec[i] = x;
        x = (a*x+b)%c;
    }
    vll pref(n);
    vll suff(n);
    
    forn(i,0,n){
        pref[i] = vec[i] | (i%k == 0 ? 0 : pref[i-1]);
    }
    suff[n-1] = vec[n-1];
    for(ll i = n-2; i >= 0; i--){
        suff[i] = vec[i] | (i%k == 0 ? 0 : suff[i+1]);
    }
    
    ll resp = 0;
    forn(i,k-1,n){
        ll aux = pref[i] | suff[i-k+1];
        resp ^= aux;
        trace(
            cout << i << " " << aux << ln;
        )
    }
    cout << resp << ln;
    return 0;
}
