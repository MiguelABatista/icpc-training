#include <bits/stdc++.h>

using namespace std;

#ifdef ONLINE_JUDGE
#pragma GCC optimize("Ofast","unroll-loops","omit-frame-pointer","inline","03")
#endif // ONLINE_JUDGE

typedef long double ld;
typedef long long ll;
typedef __int128 LL;

const ll MAX = 3e5 + 5;
const int MAXL = 1.5e7 + 5;
static const int mod = 998244353;

using i2 = pair<ll, ll>;

struct Node {
    int sum{0}, l{0}, r{0}, lz{0};
};

Node STP[MAXL];
int p;

int Inc() {
    STP[p++] = Node();
    return p - 1;
}

int cut;

void Add(int x, int r1, int r2, int lo, int hi, int s1, int s2) {
    if (hi < cut) {
        STP[x] = STP[r1];
        STP[x].sum = (STP[x].sum + 1LL * (hi - lo + 1) * s1) % mod;
        STP[x].lz = (STP[x].lz + s1) % mod;
        return;
    }
    if (cut <= lo) {
        STP[x] = STP[r2];
        STP[x].sum = (STP[x].sum + 1LL * (hi - lo + 1) * s2) % mod;
        STP[x].lz = (STP[x].lz + s2) % mod;
        return;
    }
    int m = (lo + hi) / 2;
    s1 = (s1 + STP[r1].lz) % mod;
    s2 = (s2 + STP[r2].lz) % mod;

    if (!STP[x].l)
        STP[x].l = Inc();
    Add(STP[x].l, STP[r1].l, STP[r2].l, lo, m, s1, s2);

    if (!STP[x].r)
        STP[x].r = Inc();
    Add(STP[x].r, STP[r1].r, STP[r2].r, m + 1, hi, s1, s2);

    STP[x].sum = (STP[STP[x].l].sum + STP[STP[x].r].sum) % mod;
    STP[x].lz = 0;
}

void solve() {
    int n, k;
    cin >> n >> k;

    int r = 0;

    vector<int> a(n + 1), root(n + 2);
    p = 0;

    Inc();

    for (int i = 1; i <= n; i++)
        cin >> a[i];

    for (int i = n; i >= 1; i--) {
        int lo = i + k <= n ? root[i + k] : 0;
        int hi = i < n ? root[i + 1] : 0;
        root[i] = Inc();
        cut = a[i];
        Add(root[i], lo, hi, 1, n, n - i + 1, 0);
        r = (r + STP[root[i]].sum) % mod;
    }

    cout << r << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int tc = 1;
    cin >> tc;

    while (tc--)
        solve();
}
