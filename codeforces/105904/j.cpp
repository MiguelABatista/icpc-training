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

const ll INF = 0x3f3f3f3f3f3f3f3fll;
const ll MOD = 998244353;
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
	int v;
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

// FFT
//
// Chamar convolution com vector<complex<double>> para FFT
// Precisa do mint para NTT
//
// O(n log(n))

typedef mod_int<MOD> mint;

// Para NTT
void get_roots(bool f, int n, vector<mint>& roots) {
	mint r;
	int ord;
    int p = 998244353;
	if (p == 998244353) {
		r = 102292;
		ord = (1 << 23);
	} else if (p == 754974721) {
		r = 739831874;
		ord = (1 << 24);
	} else if (p == 167772161) {
		r = 243;
		ord = (1 << 25);
	} else assert(false);

	if (f) r = r^(p - 1 -ord/n);
	else r = r^(ord/n);
	roots[0] = 1;
	for (int i = 1; i < n/2; i++) roots[i] = roots[i-1]*r;
}

void fft(vector<mint>& a, bool f, int N, vector<int>& rev) {
	for (int i = 0; i < N; i++) if (i < rev[i]) swap(a[i], a[rev[i]]);
	int l, r, m;
	vector<mint> roots(N);
	for (int n = 2; n <= N; n *= 2) {
		get_roots(f, n, roots);
		for (int pos = 0; pos < N; pos += n) {
			l = pos + 0, r = pos + n/2, m = 0;
			while (m < n/2) {
				auto t = roots[m] * a[r];
				a[r] = a[l] - t;
				a[l] = a[l] + t;
				l++, r++, m++;
			}
		}
	}
	if (f) {
		auto invN = mint(1) / mint(N);
		for (int i = 0; i < N; i++) a[i] = a[i] * invN;
	}
}

vector<mint> convolution(vector<mint>& a, vector<mint>& b) {
	vector<mint> l(a.begin(), a.end()), r(b.begin(), b.end());
	int N = l.size()+r.size()-1;
	int n = 1, log_n = 0;
	while (n <= N) n *= 2, log_n++;
	vector<int> rev(n);
	for (int i = 0; i < n; i++) {
		rev[i] = 0;
		for (int j = 0; j < log_n; j++) if (i>>j&1)
			rev[i] |= 1 << (log_n-1-j);
	}
	assert(N <= n);
	l.resize(n);
	r.resize(n);
	fft(l, false, n, rev);
	fft(r, false, n, rev);

	for (int i = 0; i < n; i++) l[i] *= r[i];
	
    fft(l, true, n, rev);
	l.resize(N);
	return l;
}

mint aplica(mint a, vector<mint>& q) {
    mint pot = 1;
    mint resp = 0;

    forn(i,0,q.size()){
        resp += pot*q[i];
        pot *= a;
    }

    return resp;
}

vector<mint> comp(vector<mint>& a, vector<mint>& b) {
	vector<mint> l(a.begin(), a.end());
	int N = (l.size()-1)*(b.size()-1)+1;
	int n = 1, log_n = 0;
	while (n <= N) n *= 2, log_n++;
	vector<int> rev(n);
	for (int i = 0; i < n; i++) {
		rev[i] = 0;
		for (int j = 0; j < log_n; j++) if (i>>j&1)
			rev[i] |= 1 << (log_n-1-j);
	}
	assert(N <= n);
	l.resize(n);
	fft(l, false, n, rev);

    forn(i,0,l.size()){
        l[i] = aplica(l[i], b);
    }     
    
    fft(l, true, n, rev);
	l.resize(N);
	return l;
}


// NTT
vector<mint> ntt(vector<mint>& a, vector<mint>& b) {
	vector<mint> A(a.begin(), a.end()), B(b.begin(), b.end());
	return convolution(A, B);
}


int main(){
    _;

    ll n1; cin >> n1;
    vector<mint> p(n1+1);
    forn(i,0,n1+1) cin >> p[i];

    ll n2; cin >> n2;
    vector<mint> q(n2+1);
    forn(i,0,n2+1) cin >> q[i];

    auto resp = comp(q,p);
    
    for(auto x : resp) cout << x << " ";
    return 0;
}