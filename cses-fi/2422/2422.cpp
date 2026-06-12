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

ll func(ll n, ll k){
    ll resp = 0;
    forn(i,1,n+1) resp += min(n, k/i);
    return resp;
}

int main() {
    _;
    ll n; cin >> n;
    ll l = 1;
    ll r = n*n;
    ll med = (n*n+1)/2;

    while(l <= r){
        ll m = (l+r)/2;
        debug(1);
        ll r1 = func(n,m);
        ll r2 = func(n,m-1);
        debug(m);
        debug(r1);
        debug(r2);
        if(r2 < med && med <= r1){
            cout << m << ln;
            return 0;
        }
        if(med <= r2){
            r = m - 1;
        }
        if(r1 < med){
            l = m+1;
        }
    }
    cout << -1 << ln;
    return 0;
}
