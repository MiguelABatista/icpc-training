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

// Primitive Root (Generator)
//
// Finds the smallest primitive root modulo a prime P.
// Factorizes P-1 and checks that for every prime factor F
// of P-1, the candidate G satisfies G^((P-1)/F) ≢ 1 (mod P).
//
// complexity: O(time_to_factor(p-1) + ans * |factors(P-1)| * log P)
// can be adapted to p not prime

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

ll primitive_root(ll p){
    v64 fact;
    ll phi = p-1,  n = phi;
    // mudar p-1 para caso nao primo
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
        for (ll i=0; i<sz(fact) && ok; ++i)
            ok &= modpow (res, phi / fact[i], p) != 1;
        if (ok)  return res;
    }
    return -1;
}

ll modLog(ll a, ll b, ll m) {
	ll n = (ll) sqrt(m) + 1, e = 1, f = 1, j = 1;
	map<ll, ll> mp;
	while (j <= n && (e = f = e * a % m) != b % m)
		mp[e * b % m] = j++;
	if (e == b % m) return j;
	if (gcd(m, e) == gcd(m, b)) 
		forn(i,2,n+2) if (mp.count(e = e * f % m))
			return n * i - mp[e];
	return -1;
}

ll calc_phi(ll n){
    ll n_ = n;
    v64 fact;
    for (ll i=2; i*i<=n; i++){
        if (n % i == 0) {
            fact.push_back (i);
            while (n % i == 0)
                n /= i;
        }
    }
    if (n > 1) fact.push_back(n);
    ll phi = n_;
    for(ll p: fact){
        phi /= p;
        phi *= (p-1);
    }
    return phi;
}

int main() {
    _;
    ll p, k, a;
    cin >> p >> k >> a;

    if(a == 0){
        cout << 1 << ln;
        cout << 0 << ln;
        return 0;
    }
    if (p == 2) {
        cout << 1 << ln << 1 << ln;
        return 0;
    }
    ll g = primitive_root(p);
    debug(g);
    ll alpha = modLog(g,a,p);
    debug(alpha);
    ll d = gcd(k, p-1);
    if(alpha%d != 0){
        cout << 0 << ln;
        return 0;
    }
    v64 resp;

    ll m = (p-1)/d;
    ll alpha2 = alpha / d;
    ll k2 = k / d % m;  
    ll y = (__int128)alpha2 % m * modpow(k2, calc_phi(m) - 1, m) % m;

    debug(y);
    forn(t,0,d) resp.push_back(modpow(g, y + t*((p-1)/d), p));

    cout << sz(resp) << ln;
    sort(resp.begin(), resp.end());
    forn(i,0,sz(resp)) cout << resp[i] << " \n"[i==sz(resp)-1];
    
    return 0;
}
