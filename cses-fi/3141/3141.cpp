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
const ll pot2 = 262144;


// Modular Integer
//
// Fixed-modulus integer type with +, -, *, /, and exponentiation; modulo should be prime for division via Fermat.
//
// complexity: O(1) per arithmetic op (O(log E) for exponentiation), O(1)

const ll MOD = 1'000'000'007;

template<ll p> struct mod_int {
    ll expo(ll b, ll e) {
        ll ret = 1;
        while (e) {
            if (e % 2) ret = ret * b % p;
            e /= 2, b = b * b % p;
        }
        return ret;
    }
    ll inv(ll b) { return expo(b, p-2); }

    using m = mod_int;
    ll v;
    mod_int() : v(0) {}
    mod_int(ll v_) {
        if (v_ >= p or v_ <= -p) v_ %= p;
        if (v_ < 0) v_ += p;
        v = v_;
    }
    m& operator +=(const m& a) {
        v += a.v;
        if (v >= p) v -= p;
        return *this;
    }
    m& operator -=(const m& a) {
        v -= a.v;
        if (v < 0) v += p;
        return *this;
    }
    m& operator *=(const m& a) {
        v = v * a.v % p;
        return *this;
    }
    m& operator /=(const m& a) {
        v = v * inv(a.v) % p;
        return *this;
    }
    m operator -() const { return m(-v); }
    m& operator ^=(ll e) {
        if (e < 0) {
            v = inv(v);
            e = -e;
        }
        v = expo(v, e);
        // possible optimization:
        // careful with 0^0
        // v = expo(v, e%(p-1)); 
        return *this;
    }
    bool operator ==(const m& a) { return v == a.v; }
    bool operator !=(const m& a) { return v != a.v; }

    friend istream& operator >>(istream& in, m& a) {
        ll val; in >> val;
        a = m(val);
        return in;
    }
    friend ostream& operator <<(ostream& out, m a) {
        return out << a.v;
    }
    friend m operator +(m a, m b) { return a += b; }
    friend m operator -(m a, m b) { return a -= b; }
    friend m operator *(m a, m b) { return a *= b; }
    friend m operator /(m a, m b) { return a /= b; }
    friend m operator ^(m a, ll e) { return a ^= e; }
};
typedef mod_int<MOD> mint;


// Sum over Subsets DP (SOS DP)
//
// sos_dp_sub: for each mask, computes the sum of f[s] over all
// subsets s of mask (i.e., f'[mask] = sum of f[s] for s in mask).
//
// sos_dp_super: for each mask, computes the sum of f[s] over all
// supersets s of mask (i.e., f'[mask] = sum of f[s] for mask in s).
//
// input size must be a power of two (2^n).
//
// complexity: O(n * 2^n), O(2^n) mem

vector<mint> sos_dp_sub(vector<mint> f) {
    ll n = __builtin_ctzll(sz(f));
    assert((1ll<<n) == sz(f));

    forn(i,0,n) forn(mask, 0, (1<<n))
        if (mask>>i&1) f[mask] += f[mask^(1<<i)];
        // -= for inverse
    return f;
}

vector<mint> sos_dp_super(vector<mint> f) {
    ll n = __builtin_ctzll(sz(f));
    assert((1ll<<n) == sz(f));

    forn(i,0,n) forn(mask, 0, (1<<n))    
        if (~mask>>i&1) f[mask] += f[mask^(1<<i)];
        // -= for inverse
    return f;
}

vector<mint> inv_sos_dp_super(vector<mint> f) {
    ll n = __builtin_ctzll(sz(f));
    assert((1ll<<n) == sz(f));

    forn(i,0,n) forn(mask, 0, (1<<n))    
        if (~mask>>i&1) f[mask] -= f[mask^(1<<i)];
        // -= for inverse
    return f;
}

int main() {
    _;
    ll n; cin >> n;
    vector<mint> pot(n+1);
    pot[0] = 1;
    forn(i,1,n+1) pot[i] = pot[i-1] + pot[i-1];

    vector<mint> freq(pot2);

    forn(i,0,n){
        ll x; cin >> x;
        freq[x] += 1;
    }

    auto f2 = sos_dp_super(freq); // f2[mask] = #{elements x st mask \in x}
    forn(i,0,pot2) f2[i] = pot[f2[i].v] -1;  // f2[mask] = #{subsets s st mask \in and_{x in s}(x)}
    auto f3 = inv_sos_dp_super(f2);  // f2[mask] = #{subsets s st mask = and_{x in s}(x)}
    forn(i,0,n+1) cout << f3[i].v << " \n"[i==n];
    return 0;
}
