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

int main() {
    _;
    ll n, m, k;
    cin >> k >> n >> m;
    vll a(k+1);
    vll b(k+1);

    forn(i,0,n){
        ll x; cin >> x;
        a[x]++;
    }
    forn(i,0,m){
        ll x; cin >> x;
        b[x]++;
    }

    vector<complex<double>> aa(a.begin(), a.end());
    vector<complex<double>> bb(b.begin(), b.end());

    auto resp = convolution<complex<double>>(aa,bb);

    vll ans(sz(resp));
    forn(i,0,sz(ans)){
        ans[i] = (ll)(resp[i].real()+0.5);
    }

    forn(i,2,sz(ans)) cout << ans[i] << " \n"[i==sz(ans)-1];
    return 0;
}
