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
    vll vec(n);
    forn(i,0,n) cin >> vec[i];
    vec.push_back(1);
    vll prox(n);
    prox[n-1] = n;
    for(ll i = n-2; i>= 0; i--){
        ll j = i+1;
        while(j < n && vec[j]%vec[i] == 0) j = prox[j];
        prox[i] = j;
    }

    ll resp = 0;    
    forn(l,0,n-1){
        ll curr = vec[l];
        ll nxt = vec[prox[l]];
        resp += min(curr - (nxt%curr), nxt%curr)*(n-prox[l]);
    }

    cout << resp << ln;
}

int main() {
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}
