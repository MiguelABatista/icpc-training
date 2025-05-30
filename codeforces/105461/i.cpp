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
ll MOD;
// Matriz

#define MODULAR true
template<typename T> struct matrix : vector<vector<T>> {
	int n, m;

	void print() {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) cout << (*this)[i][j] << " ";
			cout << endl;
		}
	}

	matrix(int n_, int m_, bool ident = false) :
			vector<vector<T>>(n_, vector<T>(m_, 0)), n(n_), m(m_) {
		if (ident) {
			assert(n == m);
			for (int i = 0; i < n; i++) (*this)[i][i] = 1;
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
		for (int i = 0; i < n; i++) for (int k = 0; k < m; k++)
			for (int j = 0; j < r.m; j++) {
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

void solve(){
    ll a0, a1, A, B, M;
    
    cin >> M >> a0 >> a1 >> A >> B;
    MOD = M;
    map<ll, ll> vp;

    ll aux = M;
    ll sqrtM = ceil(sqrt(M))+1;
    ll prime = 2;
    while(aux > 1 && prime  <= sqrtM){
        while(aux%prime  == 0){
            vp[prime]++;
            aux /= prime ;
        }
        prime++;
    }

    if(aux != 1) vp[aux]++;

    map<ll, ll> period;

    for(auto {p, k} : vp){
        ll pk = 1;
        forn(i,0,k) pk *= p;
        pk *= p*p-1;

        ll sqrtpk = ceil(sqrt(pk))+1;
        
        set<ll> divisors;
        
        forn(d, 1, sqrtpk){
            if(pk%d == 0){
                divisors.insert(d);
                divisors.insert(pk/d);
            }
        }
    }
}

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();    
    return 0;
}