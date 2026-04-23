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

    cout << "? ";
    forn(i, 2, n+1) cout << i << " ";
    cout << 1 << ln;
    
    vll v(n), cycle;
    forn(i, 0, n){
        cin >> v[i];
        v[i]--;
    }

    cycle.push_back(0);
    forn(i, 0, n-1) cycle.push_back(v[cycle.back()]);

}

int main() {
    _; ll t; cin >> t;
    forn(i, 0, t) solve();
    return 0;
}
