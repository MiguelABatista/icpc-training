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
const ll MAX = 1'000'005ll;

// Linear Sieve (prime precomputation)
//
// Computes primes up to N in O(N) using the smallest prime factor (lp).
// pr will contain all primes <= N.
// lp[x] stores the smallest prime dividing x.
//
// complexity: O(N)


pair<v64, v64> sieve(ll n){
    v64 lp(n+1);
    v64 pr;
    forn(i, 2, n+1) {
        if (lp[i] == 0) {
            lp[i] = i;
            pr.push_back(i);
        }
        for (ll j = 0; i * pr[j] <= n; ++j) {
            lp[i * pr[j]] = pr[j];
            if (pr[j] == lp[i]) {
                break;
            }
        }
    }
    return {pr, lp};
}

int main() {
    _;
    auto [pr, pl] = sieve(MAX);
    ll t; cin >> t;
    set<ll> s;
    forn(i,0,2*MAX) s.insert((i*(i+1))/2);

    while(t--){
        ll n; cin >> n;
        if(s.count(n)){
            cout << 1 << ln;
            continue;
        }
        // n = a(a+1)/2 + b(b+1)/2
        // 2n = a2 + a + b2 + b
        // 8n + 2 = (2a+1)^2 + (2b+1)^2

        ll val = 8*n + 2;
        bool b = false;

        for(ll p: pr){
            if(p > val) break;
            ll a = 0;
            if(val%p) continue;
            while(val%p == 0){
                a++;
                val /= p;
            }
            if(p%4 == 3 && a%2 == 1){
                cout << 3 << ln;
                b = true;
                break;
            }
        }
        if(b) continue;
        cout << 2 << ln;
    }
    return 0;
}
