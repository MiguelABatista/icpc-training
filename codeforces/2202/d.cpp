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

void solve(){
    ll n, k; cin >> n >> k;
    if(k < n || k > 2*n-1){
        cout << "NO" << ln;
        return;
    }

    ll x = k - n + 1;

    v64 vec(2*n);
    forn(i,0,x){
        vec[2*i] = i+2;
        vec[2*i+1] = i+1;
    }
    vec[2*x-2] = x;
    vec[2*x-1] = 1;

    forn(i,2*x, 2*n){
        vec[i] = i/2 + 1;
    }
    cout << "YES" << ln;
    forn(i,0,2*n) cout << vec[i] << " \n"[i==2*n-1];
    debugv(vec);
}

int main() {
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}
