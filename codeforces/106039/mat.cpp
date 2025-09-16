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
const ll MOD = 2;

template<typename T> struct matrix : vector<vector<T>> {
    ll n, m;
    void print() {
        forn(i, 0, n) {
            forn(j, 0, m) cout << (*this)[i][j] << " ";
            cout << ln;
        }
    }

    matrix(ll n_, ll m_, bool ident = false) : 
            vector<vector<t>>(n_, vector<T>(m_,0)), n(n_),m(m_){}
    matrix<T> operator*(matrix<T> & r) {
        assert(m == r.n);
        matrix<T> M(n, r.m);
        forn(i, 0, n) forn(k, 0, m) forn(j, 0, r.m){
            T add = (*this)[i][k] * r[k][j];
            M[i][j] +=add%MOD;
            if(M[i][j] >= MOD) M[i][j] -= MOD;
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
        while(e){
            if (e&1) v = M*v;
            e >>= 1;
            M = M*M;
        }
    }
};

int main() {
    _;
    return 0;
}