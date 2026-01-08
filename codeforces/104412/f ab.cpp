#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define double long double
#define int long long
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int mod = 1e9 + 7;

int fact[200005], inv[200005], invfact[200005];

template <int mod = (int)1e9 + 7> struct modint {
    int x;
    modint(int y = 0) : x((y % mod + mod) % mod) { }
    friend modint operator ^ (modint a, long long b) {
        modint r = 1;
        for(; b; b >>= 1, a *= a) {
            if(b & 1) {
                r *= a;
            } 
        }
        return r;
    }
    friend modint operator - (modint a) {
        return modint(0) - a;
    }
    friend modint operator ! (modint a) {
        return a ^ (mod - 2);
    }
    modint& operator /= (modint const& b) {
        return *this *= !b;
    }
    friend modint operator + (modint a, modint const& b) {
        return a += b;
    }
    friend modint operator - (modint a, modint const& b) {
        return a -= b;
    }
    friend modint operator * (modint a, modint const& b) {
        return a *= b;
    }
    friend modint operator / (modint a, modint const& b) {
        return a /= b;
    }
    friend bool operator != (const modint &a, const modint b) {
        return a.x != b.x;
    }
    friend bool operator == (const modint &a, const modint b) {
        return a.x == b.x;
    }
    modint& operator *= (modint const& b) {
        x = 1ll * x * b.x % mod;
        return *this;
    }
    friend ostream& operator << (ostream& os, modint const& a) {
        return os << a.x;
    }
    modint& operator += (modint const& b) {
        x += b.x;
        x = (x >= mod) ? x - mod : x;
        return *this;
    }
    modint& operator -= (modint const& b) {
        x = x >= b.x ? x - b.x : x - b.x + mod;
        return *this;
    }
};

int binexp(int a, int b) {
    int r = 1;
    a %= mod;
    while(b) {
        if(b & 1) r = r * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return r;
}

using mint = modint <>;

struct NQ {
    mint a, b, root;
    NQ(mint a = 0, mint b = 0, mint root = 0) : a(a), b(b), root(root) { }
    friend NQ operator+(NQ const& x, NQ const& y) {
        return NQ(x.a + y.a, x.b + y.b, x.root);
    }
    friend NQ operator-(NQ const& x, NQ const& y) {
        return NQ(x.a - y.a, x.b - y.b, x.root);
    }
    friend NQ operator*(NQ const& x, NQ const& y) {
        return NQ(x.a * y.a + x.b * y.b * x.root, x.a * y.b + x.b * y.a, x.root);
    }
    friend NQ operator/(NQ const& x, NQ const& y) {
        int r = binexp((y.a * y.a - y.b * y.b * y.root).x, mod - 2);
        return x * NQ(r * y.a, r * (-y.b), y.root);
    }
    friend bool operator==(NQ const& x, NQ const& y) {
        return x.a == y.a && x.b == y.b;
    }
    friend bool operator!=(NQ const& x, NQ const& y) {
        return !(x == y);
    }
    friend ostream& operator<<(ostream& os, NQ const& x) {
        return os << x.a << " + " << x.b << " * sqrt(" << x.root << ")";
    }
    friend istream& operator>>(istream& is, NQ& x) {
        return is >> x.a.x >> x.b.x >> x.root.x;
    }
    friend NQ conj(NQ const& x) {
        return NQ(x.a, -x.b, x.root);
    }
    friend NQ operator*(NQ const& x, mint const& y) {
        return NQ(x.a * y, x.b * y, x.root);
    }
};

NQ binexp(NQ a, int b) {
    NQ r = NQ(1, 0, a.root);
    while(b) {
        if(b & 1) r = r * a;
        a = a * a;
        b >>= 1;
    }
    return r;
}

int choose(int n, int k) {
    if(k > n) return 0;
    return (fact[n] * invfact[k] % mod) * invfact[n - k] % mod;
}

// sum of kth powers of first n fibonacci numbers
int sum_fib_powers(int n, int k) {
    // sum_{i = 0}^{n - 1} F_i^k
    mint half = mint(1) / 2;
    NQ mult = binexp(NQ(0, mint(1) / 5, 5), k);
    NQ sum = NQ(0, 0, 5);
    for(int i = 0; i <= k; i++) {
        NQ ch = NQ(i & 1 ? -1 : 1, 0, 5) * mint(choose(k, i)); 

        NQ r = binexp(NQ(half, half, 5), k - i) * binexp(NQ(half, -half, 5), i);
        if(r == NQ(1, 0, 5)) {
            sum = sum + ch * (n + 1);
        } else {
            NQ pow = (binexp(r, n + 1) - NQ(1, 0, 5)) / (r - NQ(1, 0, 5));
            sum = sum + ch * pow; 
        }
    }
    return (sum * mult).a.x;
}

main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    mint one = mint(1);
    NQ phi = NQ(one / 2, one / 2, 5);
    NQ phi_inv = NQ(one / 2, -one / 2, 5);


    fact[0] = 1, inv[0] = 1, invfact[0] = 1;
    fact[1] = 1, inv[1] = 1, invfact[1] = 1;
    for(int i = 2; i < 200003; i++) {
        fact[i] = (fact[i - 1] * i) % mod;
        inv[i] = (inv[mod % i] * (mod - mod / i)) % mod;
        invfact[i] = (invfact[i - 1] * inv[i]) % mod;
    }

    int n, k;
    cin >> n >> k;
    mint ans = 0;
    // for(int i = 1; i <= k + 1; i++) {
    ans += sum_fib_powers(n, k);
        // ans -= sum_fib_powers(l + 1, i);
    // }
    // ans *= invfact[k];
    cout << ans << endl;
    return 0;
}