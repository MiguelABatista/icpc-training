#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Line {
    ll m, c;
    // ponto de interseção (fração) com a próxima linha da pilha
    long double x_left;
};

long double intersect(const Line& a, const Line& b) {
    return static_cast<long double>(b.c - a.c) / (a.m - b.m);
}

struct Hull {
    vector<Line> st;
    void add(ll m, ll c) {
        Line ln{m, c, -1e100};
        while (!st.empty()) {
            if (st.back().m == ln.m) {                   // mesmo slope
                if (st.back().c <= ln.c) return;         // já pior
                st.pop_back();
            } else {
                long double x = intersect(st.back(), ln);
                if (st.size() == 1 || x > st.back().x_left) {
                    ln.x_left = x;
                    break;
                }
                st.pop_back();
            }
        }
        st.push_back(ln);
    }
    ll query(ll x) {
        while (st.size() >= 2 && st[1].x_left <= x) st.erase(st.begin());
        return st.front().m * x + st.front().c;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; if (!(cin >> n)) return 0;
    vector<pair<ll,ll>> cat(n);
    for (auto& [a,b] : cat) cin >> a >> b;
    sort(cat.begin(), cat.end(), [](auto& p1, auto& p2){ return p1.first < p2.first; });

    vector<ll> dp(n+1);
    vector<pair<int,ll>> seg;          // (início, maxB)
    Hull cht;
    cht.add(cat[0].second, 0);         // primeira reta
    for (int i = 1; i <= n; ++i) {
        ll Ai  = cat[i-1].first;
        ll Bi  = cat[i-1].second;
        int start = i;
        // funde segmentos enquanto Bi >= B_top
        while (!seg.empty() && Bi >= seg.back().second) {
            start = seg.back().first;
            seg.pop_back();
        }
        seg.emplace_back(start, Bi);
        cht.add(Bi, dp[start-1]);
        dp[i] = cht.query(Ai);
    }
    cout << dp[n] << '\n';
    return 0;
}
