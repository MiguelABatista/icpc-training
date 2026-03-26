#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
typedef pair<ll, ll> p64;
typedef vector<ll> v64;
 
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
    ll n, q; cin >> n >> q;
    v64 inv(n+1);
    inv[n] = n;

    v64 vec(n);
    forn(i,0,n){
        ll x; cin >> x;
        x--;
        vec[i] = x;
        inv[x] = i;
    }
 
    ll resp = 1;
    forn(i,0,n-1){
        if(inv[i] > inv[i+1]) resp++;
    }

    while(q--){
        ll a, b; cin >> a >> b;
        a--, b--;
        ll va = vec[a];
        ll vb = vec[b];
        
        // inv[va] > inv[va+1]
        // inv[va-1] > inv[va]
        // msm pra vb
        
        ll ini = 0;
        if(inv[va] > inv[va+1]) ini++;
        if(inv[vb] > inv[vb+1]) ini++;
        if(va > 0 && va != vb+1 && inv[va-1] > inv[va]) ini++;
        if(vb > 0 && vb != va+1 && inv[vb-1] > inv[vb]) ini++;

        inv[va] = b;
        inv[vb] = a;
        swap(vec[a], vec[b]);

        ll fim = 0;
        if(inv[va] > inv[va+1]) fim++;
        if(inv[vb] > inv[vb+1]) fim++;
        if(va > 0 && va != vb+1 && inv[va-1] > inv[va]) fim++;
        if(vb > 0 && vb != va+1 && inv[vb-1] > inv[vb]) fim++;

        resp -= ini;
        resp += fim;
        debug(ini);
        debug(fim);
        

        cout << resp << ln;
    }
    return 0;
 
}
