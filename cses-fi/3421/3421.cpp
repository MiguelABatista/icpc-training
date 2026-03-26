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
const ll MOD = 1'000'000'007;

int main() {
    _;
    ll n; cin >> n;
    map<ll, ll> freq;

    forn(i,0,n){
        ll x; cin >> x;
        freq[x]++;
    }

    ll resp = 1;
    for(auto [k, v] : freq){
        resp = (resp*(v+1))%MOD;
    }
    resp = (resp + MOD-1)%MOD;
    cout << resp << ln;
    return 0;
}
