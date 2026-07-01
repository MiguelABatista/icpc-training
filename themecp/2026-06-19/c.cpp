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
const ll LOG = 20;

int main() {
    _;
    ll n, q; cin >> n >> q;
    vector<vll> bl(LOG, vll(n)); // bl[exp][i] o pai 2 ^exp de i
    bl[0][0] = -2;

    forn(i,1,n){
        ll p; cin >> p;
        p--;
        bl[0][i] = p;
    }

    forn(j,1,LOG){
        forn(i,0,n){
            ll x = bl[j-1][i];
            if(x == -2){
                bl[j][i] = -2;
            }else{
                bl[j][i] = bl[j-1][x];
            }
        }
    }

    while(q--){
        ll k, x; cin >> x >> k;
        x--;
        ll exp = 0;
        ll resp = x;
        while(k >0){
            if(k%2 == 1){
                resp = bl[exp][resp];
            }
            if(resp == -2) break;
            exp++;
            k /= 2;
        }
        cout << resp + 1 << ln;
    }
}
