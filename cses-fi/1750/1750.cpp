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
const ll LOG = 33;

int main() {
    _;
    
    ll n, q; cin >> n >> q;
    vector<v64> nxt(LOG, v64(n));
    forn(i,0,n){
        cin >> nxt[0][i];
        nxt[0][i]--;
    }

    forn(j,1,LOG){
        forn(i,0,n){
            nxt[j][i] = nxt[j-1][nxt[j-1][i]]; 
        }
    }

    while(q--){
        ll x, k; cin >> x >> k;
        x--;
        ll resp = x;

        ll j = 0;
        while(k){
            if(k&1) resp = nxt[j][resp];
            k >>= 1;
            j++;
        }
        cout << resp + 1 << ln;
    }
    return 0;
}
