#include <bits/stdc++.h>

using namespace std;

#ifdef ONLINE_JUDGE
#pragma GCC optimize("Ofast","unroll-loops","omit-frame-pointer","inline","O3")
#endif // ONLINE_JUDGE

#define all(x) (x).begin(), (x).end()

typedef long double ld;
typedef long long ll;
typedef __int128 LL;

mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

static int rnd(int lo, int hi) {
    return uniform_int_distribution<int>(lo, hi)(rng);
}

const ll oo = 1e18;

const ll MAX = 2e5 + 5;
const ll mod = 1e9 + 7;

typedef struct Edge {
    int y, i;
    ll w;
    Edge(int y, ll w, int i) : y(y), w(w), i(i) {}
} i3;

struct Cactus {
    static constexpr int LN = 20;
    using i2 = pair<int, ll>;

    int N, n, m, blocks;
    vector<vector<i3>> ady;
    vector<vector<i2>> G;
    vector<array<int, LN>> lca;
    vector<int> root, pos, lvl;
    vector<ll> sum, d0, d1;
    vector<bool> bridge;
    vector<i2> s;

    void dfs(int x, int p, vector<int> &col) {
        col[x] = 1;
        for (auto [y, i, w]: ady[x]) {
            if (y == p)continue;
            if (col[y] == 1) {
                bridge[i] = false;
                sum[++blocks] = d0[x] - d0[y] + w;
                G[y].emplace_back(blocks, 0);
                int k = s.size() - 1;
                while (s[k].first != y) {
                    auto [z, j] = s[k--];
                    bridge[j] = false;
                    if (pos[y] < pos[root[z]])
                        root[z] = y;
                    ll d2 = d0[z] - d0[y];
                    G[blocks].emplace_back(z, min(d2, sum[blocks] - d2));
                }
            } else if (!col[y]) {
                s.emplace_back(y, i);
                pos[y] = pos[x] + 1;
                d0[y] = d0[x] + w;
                dfs(y, x, col);
                s.pop_back();
            }
        }
        col[x] = 2;
    }

    ll Path(ll x, ll y) {
        if (x == y)
            return 0;
        if (pos[x] < pos[y])
            swap(x, y);
        return min(d0[x] - d0[y], sum[lca[x][0]] - (d0[x] - d0[y]));
    }

    void dfs2(int x, int p) {
        for (auto [y, w]: G[x])
            if (y != p) {
                lvl[y] = lvl[x] + 1;
                lca[y][0] = x;
                for (int i = 1; i < LN; i++)
                    lca[y][i] = lca[lca[y][i - 1]][i - 1];
                d1[y] = d1[x] + w;
                dfs2(y, x);
            }
    }

    Cactus(int _n, int _m, vector<vector<i3>> &_ady) {
        n = _n;
        m = _m;
        ady.swap(_ady); // cambiar por ady = _ady si hiciera falta
        N = n + n / 2 + 1;

        bridge.resize(m + 1, 1);
        root.resize(n + 1);
        pos.resize(n + 1);
        d0.resize(n + 1);
        sum.resize(N + 1);
        lvl.resize(N, 0);

        iota(all(root), 0);

        ady[0].emplace_back(1, 0, 0);

        vector<int> col(n + 1);
        blocks = n;

        G.resize(N);
        s.reserve(n + 1);

        dfs(0, 0, col);

        N = blocks + 1;
        G.resize(N);

        for (int i = 0; i <= n; i++)
            for (auto [y, p, w]: ady[i])
                if (bridge[p])
                    G[i].emplace_back(y, w);

        d1.resize(N);
        lca.resize(N);

        dfs2(0, 0);
    }

    i2 anc(ll x, ll y) {
        // asume lvl[x] >= lvl[y]
        for (int i = LN - 1; i >= 0; i--)
            if (lvl[x] - (1 << i) >= lvl[y])
                x = lca[x][i];
        if (x == y)
            return {x, x};
        for (int i = LN - 1; i >= 0; i--)
            if (lca[x][i] != lca[y][i]) {
                x = lca[x][i];
                y = lca[y][i];
            }
        return {x, y};
    }

    ll query(ll x, ll y) {
        if (lvl[x] < lvl[y])
            swap(x, y);

        auto [a1, a2] = anc(x, y);

        if (a1 == a2)
            return d1[x] - d1[y];

        ll z = lca[a1][0];

        if (z > n) {
            return d1[x] - d1[a1] + d1[y] - d1[a2] + Path(a1, a2);
        } else {
            return d1[x] + d1[y] - d1[z] * 2;
        }
    }
};

void solve() {
    int n, m, q;
    cin >> n >> m >> q;

    vector<vector<i3>> ady(n + 1);

    for (int i = 1; i <= m; i++) {
        ll x, y, w;
        cin >> x >> y >> w;
        ady[x].emplace_back(y, w, i);
        ady[y].emplace_back(x, w, i);
    }

    Cactus G(n, m, ady);

    while (q--) {
        int x, y;
        cin >> x >> y;
        cout << G.query(x, y) << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int tc = 1;
//    cin >> tc;

    while (tc--)
        solve();
}