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

const vector<p64> mov = {
    {0,0},
    {0,1},
    {0,-1},
    {1,1},
    {1,0},
    {1,-1},
    {-1,1},
    {-1,0},
    {-1,-1}
};

ll n;
inline ll conv(ll a, ll b){
    if(a < 0 || a >= n) return -1;
    if(b < 0 || b >= n) return -1;
    return a*n+b;
}

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
            vector<vector<T>>(n_, vector<T>(m_,0)), n(n_),m(m_){}

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
    _; ll k; cin >> n >> k;
    vector<string> board(n);
    matrix<ll> vec(n*n, 1), mat(n*n, n*n);

    forn(i, 0, n){
        cin >> board[i];
        forn(j, 0, n){
            if(board[i][j] == '1') vec[conv(i, j)][0] = 1;
        }
    }

    forn(i, 0, n){
        forn(j, 0, n){
            if(board[i][j] == '#') continue;
            ll init = conv(i,j);
            for(auto [x,y] : mov){
                ll idx = conv(i+x, j+y);
                if(idx == -1) continue;
                mat[init][idx] = 1;
            }
        }
    }

    // mat.print();
    // cout << ln;
    // vec.print();

    vec.apply_transform(mat, k);

    forn(i, 0, n){
        forn(j, 0, n){
            if(board[i][j] == '#'){
                cout << '#';
            } else {
                cout << vec[conv(i, j)][0];
            }
        }
        cout << ln;
    }

    return 0;
}