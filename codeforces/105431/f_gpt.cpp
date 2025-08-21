#include <bits/stdc++.h>
using namespace std;

struct Pt { int x, y; };

static inline long long pack(int a, int b) { return (1LL << 32) * a + b; }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int F;                           // number of fence segments
    if (!(cin >> F)) return 0;

    vector<array<int,4>> seg(F);
    for (auto& s : seg) cin >> s[0] >> s[1] >> s[2] >> s[3];

    unordered_map<long long,int> id;
    vector<Pt>                      pt;
    vector<vector<int>>             adj;

    auto vid = [&](int x,int y) {
        long long k = (1LL*x<<20)|y;          // x,y ≤ 1000
        auto it = id.find(k);
        if (it != id.end()) return it->second;
        int idx = pt.size();
        id[k] = idx;
        pt.push_back({x,y});
        adj.emplace_back();
        return idx;
    };

    for (auto s : seg) {
        int a = vid(s[0],s[1]), b = vid(s[2],s[3]);
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    const int n = pt.size();
    vector<vector<int>> around(n);

    for (int v = 0; v < n; ++v) {
        vector<pair<double,int>> tmp;
        for (int u : adj[v]) {
            int dx = pt[u].x - pt[v].x, dy = pt[u].y - pt[v].y;
            tmp.push_back({atan2((double)dy, (double)dx), u});
        }
        sort(tmp.begin(), tmp.end(),
             [](const auto& p, const auto& q){ return p.first < q.first; });
        for (auto& p : tmp) around[v].push_back(p.second);
    }

    unordered_set<long long> used;
    vector<long long> area2;

    for (int u = 0; u < n; ++u) {
        for (int v : around[u]) {
            if (used.count(pack(u,v))) continue;

            vector<int> face;
            int a = u, b = v;
            while (true) {
                used.insert(pack(a,b));
                face.push_back(a);

                auto& neigh = around[b];
                int m = neigh.size();
                int pos = find(neigh.begin(), neigh.end(), a) - neigh.begin();
                int w   = neigh[(pos - 1 + m) % m];   // left turn

                a = b;  b = w;
                if (a == u && b == v) break;
            }

            long long s = 0;
            for (size_t i = 0; i < face.size(); ++i) {
                auto &p = pt[face[i]], &q = pt[face[(i+1)%face.size()]];
                s += 1LL*p.x*q.y - 1LL*p.y*q.x;
            }
            if (s > 0) area2.push_back(s);            // bounded → CCW
        }
    }

    if (area2.empty()) { cout << "0\n"; return 0; }

    sort(area2.begin(), area2.end());                 // last = outer
    area2.pop_back();

    long double ans = 0;
    for (long long a2 : area2)
        ans += (long double)a2 * (long double)a2 / 4.0L;

    cout << fixed << setprecision(10) << ans << '\n';
    return 0;
}
