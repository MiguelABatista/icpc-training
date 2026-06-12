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

ll ask(ll x, ll k, vll& v){
    cout << "? " << x+1 << " " << k << " ";
    forn(i,0,k) cout << v[i]+1 << " ";
    cout << endl;
    ll r; cin >> r;
    return r;
}

void solve(){
    ll n; cin >> n;
    vector<vll> niv(n+1);
    vll todos(n);
    forn(i,0,n) todos[i] = i;
    forn(i,0,n){
        ll r = ask(i,n,todos);
        niv[r].push_back(i);
    }

    ll k = 0;
    forn(i,1,n+1) if(sz(niv[i])) k = i;
    // forn(i,0,n+1){
    //     debug(i);
    //     debugv(niv[i]);
    // }
    // debug(k);
    vll resp;
    resp.push_back(niv[k][0]);

    for(ll i = k; i >= 1; i--){
        ll x = resp.back();
        for(ll y: niv[i-1]){
            vll vec = {x,y};
            ll r = ask(x,2,vec);
            if(r == 2) {
                resp.push_back(y);   
                break;
            }
        }
    }
    cout << "! " << k << " ";
    for(ll x : resp) cout << x + 1 << " ";
    cout << endl;
}

int main() {
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}

