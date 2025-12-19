#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64; 
typedef vector<ll> v64;

#define forn(i, s, e) for(ll i = (s); i < (e); i++)
#define sz(x) ((ll) x.size())
#define ln "\n"

#ifdef DEBUG
    #define trace(x) x
    #define _ (void)0
#else
    #define trace(x) (void)0
    #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
#endif

#define debugv(v) trace({cout << #v": "; for (auto x : v) cout<< x << " "; cout << ln;})
#define debugp(v) trace({cout << #v": "; for (auto f : v) cout<< f.first << ":" << f.second << " "; cout << ln;})
#define debug(x) trace(cout << __LINE__ << ": " #x " = " << x << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;
const ll MOD = 998244353;
const ll LOG = 60;

// Modular Integer
//
// Fixed-modulus integer type with +, -, *, /, and exponentiation; modulo should be prime for division via Fermat.
//
// complexity: O(1) per arithmetic op (O(log E) for exponentiation), O(1)


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


void solve(){
    ll n, m; cin >> n >> m;
    v64 vec(n);
    vector<bool> vis(n, false);

    set<p64> ver;
    
    forn(i,0,n){
        cin >> vec[i];
        ver.insert({vec[i], i});
    }

    vector<v64> gindo(n), gvindo(n);
    
    forn(i,0,m){
        ll a, b; cin >> a >> b;
        a--, b--;
        gindo[a].push_back(b); 
        gvindo[b].push_back(a);
    }

    vector<map<ll,ll>> mapa(n);

    for(auto [x, v] : ver){
        ll sum = 0;
        for(ll u: gvindo[v]){
            ll y = vec[u];
            if(x == y) sum += 1;
        }

        mapa[v][x] = sum;
        
        for(ll u: gindo[v]){
            ll y = vec[u];
            if(x == y) continue;
            mapa[u][x] += mapa[v][y-x]+1;
        }
		forn(i,0,n){
    	    debug(i);
        	debugp(mapa[i]);
	    }
		cout << ln << ln;
    }

    ll resp = 0;
    forn(i,0,n){
        debug(i);
        debugp(mapa[i]);
        for(auto [k,v] : mapa[i]) resp += v;
    }
    cout << resp << ln;
    trace(cout << "--------------\n\n";);

}

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
    cout << "MOD " << ln;
}