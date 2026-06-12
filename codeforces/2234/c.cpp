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

void solve(){
    ll n; cin >> n;
    vll vec(2*n);
    forn(i,0,n){
        cin >> vec[i];
        vec[n+i] = vec[i];
    }
    debugv(vec);
    forn(i,0,n){
        vll up(2*n,INF);
        up[i] = 0;
        up[i+n] = 0;
        // v[i] = 0
        forn(j,i,i+n){
            if(up[j] > vec[j]){
                up[j+1] = min(up[j], up[j+1]);
            }else{
                up[j+1] = min(vec[j], up[j+1]);
            }
        }
        
        for(ll j = i+n; j > i; j--){
            if(up[j] > vec[j-1]){
                up[j-1] = min(up[j], up[j-1]);
            }else{
                up[j-1] = min(vec[j-1], up[j-1]);
            }
        }
        ll resp = 0;
        forn(j,i+1, i+n) resp += up[j];
        cout << resp << " \n"[i==n-1];
    }
}

int main() {
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}
