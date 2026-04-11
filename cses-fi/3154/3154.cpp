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
#define _
#else
#define trace(u)
#define _ ios::sync_with_stdio(0); cin.tie(0)
#endif

#define debug(u) trace(cout << #u " = " << u << ln)
#define debugv(v) trace(cout << #v ": "; for (auto xx : v) cout << xx << " "; cout << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;

// Modular Integer
//
// Fixed-modulus integer type with +, -, *, /, and exponentiation; modulo should be prime for division via Fermat.
//
// complexity: O(1) per arithmetic op (O(log E) for exponentiation), O(1)

const ll MOD = 1'000'000'007;

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
        if (v_ >= p || v_ <= -p) v_ %= p;
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
        // possible optimization:
        // careful with 0^0
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


// Gauss
//
// Resolve sistema linear
// Retornar um par com o numero de solucoes
// e alguma solucao, caso exista
//
// O(n^2 * m)
// escrito pelo gpt, cuidado

template<typename T>
pair<ll, vector<T>> gauss(vector<vector<T>> a, vector<T> b) {
    ll n = sz(a), m = sz(a[0]);
    forn(i, 0, n) a[i].push_back(b[i]);

    v64 where(m, -1);
    for (ll col = 0, row = 0; col < m && row < n; col++) {
        ll sel = row;
        forn(i, row, n){
            if(a[i][col] != 0){
                sel = i;
                break;
            }
        }
        if(a[sel][col] == 0) continue;
        forn(i, col, m+1)
            swap(a[sel][i], a[row][i]);
        where[col] = row;

        forn(i, 0, n) if (i != row) {
            T c = a[i][col] / a[row][col];
            forn(j, col, m+1)
                a[i][j] -= a[row][j] * c;
        }
        row++;
    }

    vector<T> ans(m, 0);
    forn(i, 0, m) if (where[i] != -1)
        ans[i] = a[where[i]][m]/a[where[i]][i];
    forn(i, 0, n) {
        T sum = 0;
        forn(j, 0, m)
            sum += ans[j]*a[i][j];
        if(sum != a[i][m])
            return pair(0, vector<T>());
    }

    forn(i, 0, m) if (where[i] == -1)
        return pair(INF, ans);
    return pair(1, ans);
}

int main() {
    _;
    ll n, m; cin >> n >> m;

    vector<vector<mint>> mat(n, vector<mint>(m));
    vector<mint> b(n);
    forn(i,0,n){
        forn(j,0,m){
            cin >> mat[i][j];
        }
        cin >> b[i];
    }

    auto [k, v] = gauss(mat, b);
    if(!k){
        cout << -1 << ln;
        return 0;
    }
    forn(i,0,m) cout << v[i] << " \n"[i==m-1];
    return 0;
}
