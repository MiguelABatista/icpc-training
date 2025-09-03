// Template Skeleton
//
// Sets up fast I/O, aliases, and basic macros for contests.

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
const ll MOD = 1'000'000'000;
const ll DEG = 401;

// Matriz

struct pol{
	v64 coef = v64(DEG, 0);

	pol(){}
	pol(ll val){coef[0] = val;}

	pol operator*(const pol& r) {
		pol novo;
		forn(i,0,DEG){
			forn(j,0,DEG-i){
				novo.coef[i+j] = (novo.coef[i+j] + coef[i]*r.coef[j])%MOD;
			}
		}
		return novo;
	}
	pol operator+(const pol& r) {
		pol novo;
		forn(i,0,DEG){
			novo.coef[i] = (novo.coef[i] + coef[i] + r.coef[i])%MOD;
		}
		return novo;
	}
	void print(){ cout << "( "; forn(i,0,DEG){cout << coef[i] << " "; } cout << " )" ;}
};

#define MODULAR false
template<typename T> struct matrix : vector<vector<T>> {
	ll n, m;

	void print() {
		forn(i,0,n) {
			forn(j,0,m) {(*this)[i][j].print(); cout << " ";}
			cout << ln;
		}
	}

	matrix(ll n_, ll m_, bool ident = false) :
			vector<vector<T>>(n_, vector<T>(m_)), n(n_), m(m_) {
		if (ident) {
			assert(n == m);
			forn(i,0,n) (*this)[i][i] = pol(1);
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
            M[i][j] = M[i][j] + add;
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
    ll n, m ,k; cin >> n >> m >> k;
	
	matrix<pol> mat(10, 10);


    forn(i,0,9){
        mat[i+1][i].coef[0]++;
    }

	
	forn(i,0,m){
		ll d, p;
        cin >> d >> p;
		d--;
        mat[0][d].coef[p]++;
    }
	
    auto resp = mat^(n-1);
	ll ans = 0;
	// resp.print();
	forn(i,0,k+1) ans = (ans+resp[0][0].coef[i])%MOD; 
	cout << ans << ln;
    return 0;
}
