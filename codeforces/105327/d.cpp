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
const ll MOD = 1'000'000'007;
const ll TAM = 100;

// Matriz

#define MODULAR false
template<typename T> struct matrix : vector<vector<T>> {
	ll n, m;
	void print() {
		forn(i,0,n) {
			forn(j,0,m) cout << (*this)[i][j] << " ";
			cout << endl;
		}
	}

	matrix(ll n_, ll m_, bool ident = false) :
			vector<vector<T>>(n_, vector<T>(m_, 0)), n(n_), m(m_) {
		if (ident) {
			assert(n == m);
			forn(i,0,n) (*this)[i][i] = 1;
		}
	}
	matrix(const vector<vector<T>>& c) : vector<vector<T>>(c),
		n(c.size()), m(c[0].size()) {}
	matrix(const initializer_list<initializer_list<T>>& c) {
		vector<vector<T>> val;
		for (auto& i : c) val.push_back(i);
		*this = matrix(val);
	}

	matrix<T> operator*(matrix<T>& r) {
		assert(m == r.n);
		matrix<T> M(n, r.m);
		forn(i,0,n) forn(k,0,m) forn(j, 0, r.m){
			T add = (*this)[i][k] * r[k][j];
#if MODULAR
#warning Usar matrix<ll> e soh colocar valores em [0, MOD) na matriz!
            M[i][j] += add%MOD;
            if (M[i][j] >= MOD) M[i][j] -= MOD;
#else
            M[i][j] += add;
#endif
        }
		return M;
	}
	matrix<T> operator^(ll e){
		matrix<T> M(n, n, true), at = *this;
		while (e) {
			if (e&1) M = M*at;
			e >>= 1;
			at = at*at;
		}
		return M;
	}
	void apply_transform(matrix M, ll e){
		auto& v = *this;
		while (e) {
			if (e&1) v = M*v;
			e >>= 1;
			M = M*M;
		}
	}
};


int main(){
    _;
    ll n, m;
    cin >> n >> m;
    vector<v64> mag(61, v64(TAM+1,0));

    forn(kasd,0,m){
        ll a, b; cin >> a >> b;
        forn(i,b,61){
            mag[i][a]++;
        }
    }

    vector<matrix<ll>> mats(61, matrix<ll>(TAM,TAM));

    forn(t,0,61){
        forn(i,0,TAM-1) mats[t][i+1][i] = 1;
        forn(i,0,TAM) mats[t][0][i] = mag[t][i+1];
    }

    vector<matrix<ll>> pots(61, matrix<ll>(TAM,TAM, true));
    vector<matrix<ll>> prev(61, matrix<ll>(TAM,TAM, true));
    pots[0] = mats[0];

    forn(i,1,61){
        pots[i] = mats[i]*prev[i-1]*pots[i-1]; 
        prev[i] = prev[i-1]*pots[i-1]; 
    }

    matrix<ll> resp(TAM,TAM, true);
    ll pot2 = (1ll<<60);
    ll i = 60;
    for(; n > 0; pot2 /= 2, i--){
        if(pot2 > n) continue;
        n -= pot2;
        resp = pots[i]*resp;
    }
    vector<ll> vec(TAM, 0);
    vec[0] = 1;

    cout << resp[0][0] << ln;
    return 0;
}