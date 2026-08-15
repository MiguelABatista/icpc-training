#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;
typedef vector<ll> vll;

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

// Centroid Decomposition - pares a distancia k
//
// Objetivo: contar #pares (u,v) com dist(u,v)=k na arvore.
// Ideia: em cada centroide c, para cada subarvore j:
//   - path = profundidades d partindo de j (sem nos removidos)
//   - somar cnt[k-d-1] ANTES de atualizar (evita dupla contagem entre subarvores)
//   - depois, cnt[d+1]++ (a aresta (c,j) soma 1)
//
// Funcoes: dfs_sz (tamanhos), centroid (acha centroide), dfs (coleta depths), decomp (divide e combina).
// Complexidade: O(n log n) tempo; O(n) memoria.
// Cuidados: limites de cnt, k==0 trata a parte se quiser contar (u,u); rem[c] permanece marcado.
// escrito pelo gpt, cuidado

// Modular Integer
//
// Fixed-modulus integer type with +, -, *, /, and exponentiation; modulo should be prime for division via Fermat.
//
// complexity: O(1) per arithmetic op (O(log E) for exponentiation), O(1)

const ll MOD = 998244353;

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


// FFT/NTT Convolution
//
// Implements iterative FFT over complex numbers and NTT over supported primes; provides convolution utility.
//
// complexity: O(N log N), O(N)

// Para FFT
void get_roots(bool f, ll n, vector<complex<double>>& roots) {
    const static double PI = acosl(-1);
    forn(i,0,n/2){
        double alpha = i*((2*PI)/n);
        if (f) alpha = -alpha;
        roots[i] = {cos(alpha), sin(alpha)};
    }
}

// Para NTT
template<ll p>
void get_roots(bool f, ll n, vector<mod_int<p>>& roots) {
    mod_int<p> r;
    ll ord;
    if(p == 998244353){
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
    forn(i,1,n/2) roots[i] = roots[i-1]*r;
}

template<typename T> void fft(vector<T>& a, bool f, ll N, vector<ll>& rev) {
    forn(i,0,N) if (i < rev[i]) swap(a[i], a[rev[i]]);
    ll l, r, m;
    vector<T> roots(N);
    for (ll n = 2; n <= N; n *= 2) {
        get_roots(f, n, roots);
        for (ll pos = 0; pos < N; pos += n) {
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
        auto invN = T(1) / T(N);
        for (ll i = 0; i < N; i++) a[i] = a[i] * invN;
    }
}

template<typename T> vector<T> convolution(vector<T>& a, vector<T>& b) {
    vector<T> l(a.begin(), a.end()), r(b.begin(), b.end());
    ll N = sz(l)+sz(r)-1;
    ll n = 1, log_n = 0;
    while (n < N) n *= 2, log_n++;
    vector<ll> rev(n);
    forn(i,0,n) {
        rev[i] = 0;
        forn(j,0,log_n) if (i>>j&1)
            rev[i] |= 1 << (log_n-1-j);
    }

    assert(N <= n);
    l.resize(n);
    r.resize(n);
    fft(l, false, n, rev);
    fft(r, false, n, rev);
    for (ll i = 0; i < n; i++) l[i] *= r[i];
    fft(l, true, n, rev);
    l.resize(N);
    return l;
}

// NTT
template<ll p, typename T> // to cast vll to vector<mint>
vector<mod_int<p>> ntt(vector<T>& a, vector<T>& b) { 
    vector<mod_int<p>> A(a.begin(), a.end()), B(b.begin(), b.end());
    return convolution(A, B);
}


const ll MAX = 100'005;
vll g[MAX];
ll x[MAX];

ll siz[MAX], rem[MAX];

void dfs(vector<pll>& path, ll i, ll l=-1, ll d=0) {
    path.push_back({d,x[i]});
    for (ll j : g[i]) if (j != l && !rem[j]) dfs(path, j, i, d+1);
}

ll dfs_sz(ll i, ll l=-1) {
    siz[i] = 1;
    for (ll j : g[i]) if (j != l && !rem[j]) siz[i] += dfs_sz(j, i);
    return siz[i];
}

ll centroid(ll i, ll l, ll size) {
    for (ll j : g[i]) if (j != l && !rem[j] && siz[j] > size / 2)
        return centroid(j, i, size);
    return i;
}

vector<mint> decomp(ll xxx) {
    ll c = centroid(xxx, xxx, dfs_sz(xxx));
    rem[c] = 1;

    // gasta O(n) aqui - dfs sem ir pros caras removidos
    vector<vll> fs;
    vector<vll> fc;
    
    ll gmaxd = 0;
    vll gs;
    vll gc;
    for (ll j : g[c]) if (!rem[j]) {
        vector<pll> path;
        dfs(path, j);

        ll maxd = 0;
        for (auto [d, vx] : path) maxd = max(maxd, d);
        vll ls(maxd+1);
        vll lc(maxd+1);
        
        for (auto [d, vx] : path) {
            ls[d] += vx;
            lc[d] += 1;
        }
        fs.push_back(ls);
        fc.push_back(lc);
        gmaxd = max(gmaxd, maxd);
    }
    
    gs.resize(gmaxd+2);
    gc.resize(gmaxd+2);
    gs[0] += x[c];
    gc[0] += 1;
    forn(i,0,sz(fs)){
        forn(j,0, sz(fc[i])) gc[j+1] += fc[i][j];
        forn(j,0, sz(fs[i])) gs[j+1] += fs[i][j];
    }
    
    auto ans = ntt<MOD, ll>(gs, gc);
    
    forn(i,0,sz(fs)){
        auto aux = ntt<MOD, ll>(fs[i], fc[i]);
        if(sz(aux) > sz(ans)) ans.resize(sz(aux)+2);
        forn(j,0,sz(aux)) ans[j+2] -= aux[j];
    }

    for (ll j : g[c]) if (!rem[j]){
        auto aux = decomp(j);
        forn(i,0,sz(aux)) ans[i] += aux[i];
    }
    rem[c] = 0;
    return ans;
}


int main() {
    _;
    ll n; cin >> n;
    forn(i,0,n) cin >> x[i];
    forn(i,0,n-1){
        ll a, b; cin >> a >> b;
        a--, b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    vector<mint> ans = decomp(0);

    debugv(ans);
    mint resp = 0;

    forn(k,0,sz(ans)) resp += ans[k]/(k+1);
    cout << resp << ln;
    return 0;   
}
