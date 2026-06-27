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


int main() {
    _; ll n, c, k; cin >> n >> c >> k;
    vll v(n);
    forn(i, 0, n) cin >> v[i];

    ll sum = 0;
    forn(i,0, n){
        if(i == 0){
            sum += c+k;
            continue;
        }

        sum += min(c + k, c*(v[i]-v[i-1]));
    }

    cout << sum << ln;

    return 0;
}