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

bool testa(ll tar, ll n, ll k, v64& vec){
    ll curr = 0;
    ll amt = 0;
    forn(i,0,n){
        if(vec[i] > tar) return false;
        if(curr + vec[i] > tar){
            curr = vec[i];
            amt++;
        }else{
            curr += vec[i];
        }
    }
    debug(amt);
    debug(curr);
    return amt < k;
}

int main() {
    _;
    ll n, k; cin >> n >> k;
    v64 vec(n);
    forn(i,0,n) cin >> vec[i];

    ll l = 0;
    ll r = INF;
    ll ans = INF;

    while (l<=r){
        ll m = (l+r)/2;
        debug(m);
        bool b = testa(m, n, k, vec);  
        debug(b);
        trace(cout << ln << ln;);

        if(b){
            r = m-1;
            ans = m;
        }else{
            l = m+1;
        }
    }
    cout << ans << ln;
    return 0;
}
