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

mt19937_64 rng((ll) chrono::steady_clock::now().time_since_epoch().count());

ll uniform(ll l, ll r){
    uniform_int_distribution<ll> uid(l, r);
    return uid(rng);
}

int main() {
    _;
    ll n = 10;
    ll q = 10;
    cout << 1 << ln;
    cout << n << " " << 1 << ln;
    forn(i,0,n) cout << uniform(0,1);; cout << ln;
    forn(i,0,n) cout << uniform(0,1);; cout << ln;
    
    forn(i,0,q){
        ll a = uniform(1,n);
        ll b = uniform(1,n);
        cout <<  min(a,b) << " " << max(a,b) << ln;
    }

    return 0;
}
