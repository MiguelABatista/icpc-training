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
    _;
    ll n, k, a, b, c;
    cin >> n >> k;
    vll vec(n);
    cin >> vec[0] >> a >> b >> c;
    forn(i,1,n) vec[i] = (a* vec[i-1] + b)%c;
    debugv(vec);
    ll resp = 0;
    ll w = 0;
    forn(i,0,k) w ^= vec[i];

    resp = w;
    
    forn(i,k,n){
        debug(w);
        w ^= vec[i-k];
        w ^= vec[i];
        resp ^= w;
    }
    debug(w);
    cout << resp << ln;
    return 0;
} 
