#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const ll MAXA = 100'000;
const ll MOD  = 998244353;
const ll INV2 = 499122177;

ll addmod(ll a, ll b) { a += b; if (a >= MOD) a -= MOD; return a; }
ll submod(ll a, ll b) { a -= b; if (a < 0)  a += MOD; return a; }
ll mulmod(ll a, ll b) { return static_cast<ll>((1LL * a * b) % MOD); }

vector<vector<ll>> divisores(MAXA + 1);
vector<ll> primes;
vector<char> is_comp(MAXA + 1, 0);
vector<ll> mu(MAXA + 1, 0);
vector<ll> pot2(MAXA + 1, 1), g(MAXA + 1, 0), f(MAXA + 1, 0), cnt(MAXA + 1, 0);
vector<vector<pair<ll,ll>>> mobius_contrib(MAXA + 1);

void build_contrib() {
    for (ll d = 1; d <= MAXA; ++d)
        for (ll x : divisores[d]) {
            ll m = mu[d / x];
            if (m) mobius_contrib[d].emplace_back(m, x);
        }
}

ll pot(ll a, ll b) {
    ll res = 1, base = a;
    while (b) {
        if (b & 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        b >>= 1;
    }
    return static_cast<ll>(res);
}

void calc_divisores() {
    for (ll i = 1; i <= MAXA; ++i)
        for (ll j = i; j <= MAXA; j += i)
            divisores[j].push_back(i);
}

void sieve(ll n) {
    mu[1] = 1;
    for (ll i = 2; i < n; ++i) {
        if (!is_comp[i]) {
            mu[i] = -1;
            primes.push_back(i);
        }
        for (ll j = 0; j < primes.size(); ++j) {
            ll prod = 1LL * i * primes[j];
            if (prod >= n) break;
            ll idx = static_cast<ll>(prod);
            is_comp[idx] = 1;
            if (i % primes[j] == 0) {
                mu[idx] = 0;
                break;
            }
            mu[idx] = mu[i] * mu[primes[j]];
        }
    }
}

void update_f2(ll v, bool add) {
    add ? ++cnt[v] : --cnt[v];
    ll old_f = f[v];
    f[v] = submod(pot2[cnt[v]], 1);
    ll delta = submod(f[v], old_f);
    for (ll d : divisores[v]) {
        ll m = mu[v / d];
        if (m == 0) continue;
        if (m == 1)
            g[d] = addmod(g[d], delta);
        else
            g[d] = submod(g[d], delta);
    }
}

inline void update_f(ll d, bool add)
{
    add ? ++cnt[d] : --cnt[d];
    ll old = f[d];
    f[d]   = submod(pot2[cnt[d]], 1);
    ll delta = submod(f[d], old);

    for (auto [sgn, x] : mobius_contrib[d]) {
        g[x] = (sgn == 1 ? addmod(g[x], delta)
                         : submod(g[x], delta));
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    for (ll i = 1; i <= MAXA; ++i) pot2[i] = addmod(pot2[i - 1], pot2[i - 1]);

    sieve(MAXA);
    calc_divisores();
    build_contrib();

    ll n; cin >> n;
    ll dem = pot(submod(pot2[n], 1), MOD - 2);

    vector<ll> vec(n);
    for (ll i = 0; i < n; ++i) {
        cin >> vec[i];
        for (ll d : divisores[vec[i]]) ++cnt[d];
    }
    for (ll i = 0; i <= MAXA; ++i) f[i] = submod(pot2[cnt[i]], 1);

    for (ll d = MAXA; d >= 1; --d) {
        ll s = f[d];
        for (ll m = d + d; m <= MAXA; m += d) s = submod(s, g[m]);
        g[d] = s;
    }

    ll q; cin >> q; 
    while (q--) {
        ll t, x; cin >> t >> x;
        if (t == 1) {
            cout << mulmod(g[x], dem) << '\n';
        } else {
            ll y; cin >> y;
            --x;
            for (ll d : divisores[vec[x]]) update_f(d, false);
            for (ll d : divisores[y])     update_f(d, true);
            vec[x] = y;
        }
    }
    return 0;
}
