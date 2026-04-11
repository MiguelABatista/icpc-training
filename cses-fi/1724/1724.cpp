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
const ll INF = 100;
#define _
#else
#define trace(u)
const ll INF = 0x3f3f3f3f3f3f3f3fll;
#define _ ios::sync_with_stdio(0); cin.tie(0)
#endif

#define debug(u) trace(cout << #u " = " << u << ln)
#define debugv(v) trace(cout << #v ": "; for (auto xx : v) cout << xx << " "; cout << ln)

const ll MOD = 1'000'000'007;

// Matrix template
//
// - operator*: multiplicacao (O(n*m*r))
//   opcional modo modular (#define MODULAR true)
// - operator^: exponenciacao rapida (O(log e))
// - apply_transform(): aplica transformacao M^e * v

#define MODULAR false
template<typename T> struct matrix : vector<vector<T>> {
    ll n, m;
    void print() {
        forn(i,0,n) {
            forn(j,0,m) cout << setw(4) <<  (*this)[i][j] << " ";
            cout << endl;
        }
    }

    matrix(ll n_, ll m_, bool ident = false) :
            vector<vector<T>>(n_, vector<T>(m_, INF)), n(n_), m(m_) {
        if (ident) {
            assert(n == m);
            forn(i,0,n) forn(j,0,n){
                (*this)[i][j] = INF*(1-(i==j));
            }
        }
    }
    matrix(const vector<vector<T>>& c) : vector<vector<T>>(c),
        n(sz(c)), m(sz(c[0])) {}
    matrix(const initializer_list<initializer_list<T>>& c) {
        vector<vector<T>> val;
        for (auto& i : c) val.push_back(i);
        *this = matrix(val);
    }

    matrix<T> operator*(matrix<T>& r) {
        assert(m == r.n);
        matrix<T> M(n, r.m);
        M = vector(n,vector(n,INF));;
        forn(i,0,n) forn(k,0,m) forn(j, 0, r.m){
            T add = (*this)[i][k] + r[k][j];
#if MODULAR
#warning Usar matrix<ll> e soh colocar valores em [0, MOD) na matriz!
            M[i][j] += add%MOD;
            if (M[i][j] >= MOD) M[i][j] -= MOD;
#else
            M[i][j] = min(M[i][j],add);
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


int main() {
    _;
    ll n, m, k; cin >> n >> m >> k;
    matrix<ll> mat(n,n, true);
    forn(i,0,n) mat[i][i] = INF;
    forn(i,0,m){
        ll a, b, c; cin >> a >> b >> c;
        a--, b--;
        mat[a][b] = min(mat[a][b], c);
    }

    trace(
        mat.print();
        cout << ln;
    )
    auto mat2 = mat^3;
    trace(
        mat2.print();
        cout << ln;
    )
    mat = mat^k;
    
    // mat.print();
    cout << (mat[0][n-1]==INF ? -1 : mat[0][n-1]) << ln;
    return 0;
}
