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
    ll n, k; cin >> n >> k;
    vll vec(n);

    forn(i,0,n){
        ll x; cin >> x;
        x--;
        vec[x]++;
    }

    vll acc(n);
    forn(i,0,n) acc[i] = vec[i] + (i == 0 ? 0 : acc[i-1]);
    auto sum = [&](ll l, ll r){
        return acc[r] - (l == 0 ? 0 : acc[l-1]);
    };

    for(ll i = n-1; i >= 0; i--){
        if(vec[i] == 0) continue;
        if(vec[i]%2 == 0){
            cout << "YES" << ln;
            return;
        }
        if(i == 0){
            cout << "NO" << ln;
            return;
        }
        ll j = max(0ll,i-k);
        ll q = sum(j,i-1);
        if(q >= 1){
            cout << "YES" << ln;
            return;
        }
    }
    cout << "NO" << ln;
}

int main() {
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}
