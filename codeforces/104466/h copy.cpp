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
#define debug(x) trace(cout << __LINE__ << ": " #x " = " << x << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;
const ll MOD = 1'000'000'007;

mt19937_64 rng((ll) 67);

ll uniform(ll l, ll r){
	uniform_int_distribution<ll> uid(l, r);
	return uid(rng);
}

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
	m operator -() const { return m(-v); }
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
	bool operator <(const m& a) const { return v < a.v; }
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


int main(){
    _;
    vector<mint> fib(2012);
    fib[0] = 0;
    fib[1] = 1;
    forn(i,2,202) fib[i] = fib[i-1] + fib[i-2];

    ll target; cin >> target;

    vector<v64> sol;
    
    map<mint, ll> mp;
    ll idx = 0;

    p64 idxs_sol;
    debug(1);
    forn(aa,0,1'000'000){    
        ll max_sum = 100 - uniform(0,95);
        ll curr_sum = 0;
        v64 vec;
        mint ans = 1;

        while(3 < max_sum - curr_sum){
            ll val = uniform(3,max_sum - curr_sum);
            vec.push_back(val);
            curr_sum += val;
            ans = (ans*fib[val]);
        }

        mp[ans] = idx++;
        sol.push_back(vec);
    }

    string s;
    string r;
    
    forn(bb,0,500'000){    
        ll max_sum = 100 - uniform(0,95);
        ll curr_sum = 0;
        v64 vec;
        mint ans = 1;

        while(3 < max_sum - curr_sum){
            ll val = uniform(3,max_sum - curr_sum);
            vec.push_back(val);
            curr_sum += val;
            ans = (ans*fib[val]);
        }

        auto it = mp.find(target/ans);

        if(it == mp.end()) continue;
        debug(it->first);
        debug(ans);

        for(ll x : vec){
            forn(i,0,x-1) s.push_back('.');
            s.push_back('#'); 
        }
        for(ll x : sol[it->second]){
            forn(i,0,x-1) r.push_back('.');
            r.push_back('#'); 
        }
        break; 
    }


    cout << s << r << ln;
    cout << s << r << ln;
    return 0;
}