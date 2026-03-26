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

// Modular Arithmetic Helpers
//
// Provides fast modular mul, fast exponentiation.
//
// complexity: O(log E) for power/inverse

typedef unsigned long long ull;
const ll MOD = 1'000'000'007;

ull modmul(ull a, ull b, ull M){ 
    ll ret = a*b - M * ull(1.L / M*a*b);    
    return ret + M * (ret < 0) - M * (ret >= (ll)M);
};

ull modpow(ull b, ull e, ull mod){
    ull ans = 1;
    for(; e; b = modmul(b, b, mod), e /= 2)
        if(e & 1) ans = modmul(ans, b, mod);
    return ans;
}

ll generator(ll p){
    v64 fact;
    ll phi = p-1,  n = phi;
    for (ll i=2; i*i<=n; i++)
        if (n % i == 0) {
            fact.push_back (i);
            while (n % i == 0)
                n /= i;
        }
    if (n > 1)
        fact.push_back(n);

    forn(res,2, p+1) {
        bool ok = true;
        for (ll i=0; i<fact.size() && ok; ++i)
            ok &= modpow (res, phi / fact[i], p) != 1;
        if (ok)  return res;
    }
    return -1;
}


int main() {
    _;
    ll p; cin >> p;
    cout << generator(p) << ln;

    return 0;
}
