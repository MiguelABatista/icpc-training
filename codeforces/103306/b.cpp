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
const ll MOD = 998244353;
const ll MAXS = 200004;

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
        if (v_ >= p || v_ <= -p) v_ %= p;
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

vector<mint> prep(ll m, mint p){
    vector<mint> fact(m+1);

    fact[0] = 1;
    forn(i, 1, m+1) fact[i] = i*fact[i-1];

    function<mint (ll , ll)> binom = [&](ll a, ll b){
        return fact[a]/(fact[b]*fact[a-b]);
    };

    vector<mint> dist(m+1);

    forn(i, 0, m+1){
        dist[i] = binom(m, i)*(p^i)*((1-p)^(m-i));
    }

    trace(
        forn(i, 0, m+1) cout << dist[i] << " ";
        cout << ln;
    );
    
    vector<mint> acc(m+1);
    forn(i, 0, m+1) acc[i] = dist[i] + (i == 0 ? 0 : acc[i-1]);

    trace(
        forn(i, 0, m+1) cout << acc[i] << " ";
        cout << ln;
    );

    return acc;
}

int main() {
    _;ll n, m; cin >> n >> m;
    vll a(n);
    forn(i, 0, n) cin >> a[i];

    auto acc = prep(m, (mint)1/n);

    auto querry = [&](ll x, ll y){
        y = min(y, m+1);
        x = min(x, m+1);
        mint resp = (y <= 0 ? 0 : acc[y-1]) - (x <= 0 ? 0 : acc[x-1]);
        debug(resp);
        return resp;
    };

    vector<mint> exp(9);

    forn(i, 0, n){
        ll pow = 1;
        ll d = 1;
        ll curr = 2;
        ll last = 1;
        while(last < MAXS){
            debug(last);
            debug(curr);
            exp[d] += querry(last - a[i], curr - a[i]);
            last = curr;
            curr += pow;
            d = (d+1)%9;
            if(d == 0) pow = 10*pow;
        }
    }

    forn(i, 1, 10){
        cout << exp[i%9] << ln;
    }

    return 0;
}
