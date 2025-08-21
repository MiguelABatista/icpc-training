#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
typedef pair<ll, ll> p64; 
typedef vector<ll> v64;
 
#define forn(i, s, e) for(ll i = (s); i < (e); i++)
#define ln "\n"
 
#if defined(DEBUG)
    #define _ (void)0
    #define debug(x) cout << __LINE__ << ": " << #x << " = " << x << ln
#else
    #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
    #define debug(x) (void)0
#endif
 
const ll MOD = 1'000'000'007;
 
// Aritmetica Modular
//
// O mod tem q ser primo
 
template<int p> struct mod_int {
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
		v = v * ll(a.v) % p;
		return *this;
	}
	m& operator /=(const m& a) {
		v = v * inv(a.v) % p;
		return *this;
	}
	m operator -(){ return m(-v); }
	m& operator ^=(ll e) {
		if (e < 0) {
			v = inv(v);
			e = -e;
		}
		v = expo(v, e);
		// possivel otimizacao:
		// cuidado com 0^0
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
 
const ll INF = 0x3f3f3f3f3f3f3f3fll;
const ll POTMAX = 1<<20;
vector<vector<mint>> dp;
vector<vector<bool>> calc;
vector<v64> g;
 
mint rec(ll u, ll mask){
    if(calc[u][mask]) return dp[u][mask];
    if(((1<<u) & mask) == 0) return 0;
    mint ans  = 0;
 
    for(ll v: g[u]) {
        if(((1<<v) & mask) == 0) continue;
 
        ans += rec(v, mask^(1<<u)); 
    }
 
    calc[u][mask] = true; 
    dp[u][mask] = ans;
    return ans;
}
 
int main(){
    _;
    ll n, m; cin >> n >> m;
    dp.resize(n, vector<mint>(1<<n, 0));
    calc.resize(n, vector<bool>(1<<n, 0));
    g.resize(n);
 
    forn(i,0,m){
        ll a, b; cin >> a >> b;
        a--; b--;
        // g[a].push_back(b);
        g[b].push_back(a);
    }
 
    dp[0][1] = 1;
    calc[0][1] = true;
    cout << rec(n-1, (1<<n)-1) << ln;
    return 0;
}