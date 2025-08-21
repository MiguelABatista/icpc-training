#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define int ll
#define pb push_back
#define all(v) (v).begin(), (v).end()

void dbg_out() { cerr << endl; }
template<typename H, typename... T>
void dbg_out(H h, T... t) { cerr << ' ' << h; dbg_out(t...); }
#define dbg(...) { cerr << #__VA_ARGS__ << ':'; dbg_out(__VA_ARGS__); }

struct point {
	int x, y;
	point(): x(0), y(0) {}
	point(int _x, int _y): x(_x), y(_y) {}
	friend point operator-(point a, point b) {
		return point(a.x - b.x, a.y - b.y);
	}
	friend int operator^(point a, point b) {
		return a.x * b.y - b.x * a.y;
	}
	friend bool operator==(const point a, const point b) {
		return a.x == b.x && a.y == b.y;
	}
	friend bool operator<(const point a, const point b) {
		using tup = pair<int,int>;
		return tup(a.x, a.y) < tup(b.x, b.y);
	}
};

point zero(0, 0);

int ang_cmp(point a, point b) {
	auto quad = [](point p) -> bool {
		auto [x, y] = p;
		return y < 0 || (y == 0 && x < 0);
	};
	using t = pair<bool, int>;
	return t(quad(a), 0) < t(quad(b), a ^ b);
}

void solve() {
	map<point, int> id;
	vector<point> pts;

	int m; cin >> m;
	vector<pair<point,point>> seg(m);
	for(auto &[a, b]: seg) {
		cin >> a.x >> a.y;
		cin >> b.x >> b.y;
		for(point p: {a, b}) {
			auto it = id.find(p);
			if(it == id.end()) 
				id[p] = id.size(), pts.pb(p);
		}
	}
	int n = id.size();

	vector<vector<point>> g(n);
	vector<vector<bool>> vis(n);

	for(auto [a, b]: seg) {
		int u = id[a], v = id[b];
		g[u].pb(pts[v]);
		vis[u].pb(false);
		g[v].pb(pts[u]);
		vis[v].pb(false);
	}

	double ans = 0;

	for(int u = 0; u < n; u++) {
		auto cmp = [&](point a, point b) { return ang_cmp(a - pts[u], b - pts[u]); };
		sort(all(g[u]), cmp);
	}

	for(int u = 0; u < n; u++) {
		for(int i = 0; i < g[u].size(); i++) {
			if(vis[u][i]) continue;
			int area = 0;

			int cur = u, curi = i;
			do {
				int nxt = id[g[cur][curi]];
				vis[cur][curi] = true;

				area += pts[cur] ^ pts[nxt];

				auto cmp = [&](point a, point b) { return ang_cmp(a - pts[nxt], b - pts[nxt]); };
				int nxti = lower_bound(all(g[nxt]), pts[cur], cmp) - g[nxt].begin();
				nxti--;
				if(nxti == -1) nxti = g[nxt].size() - 1;

				cur = nxt;
				curi = nxti;
			} while(cur != u);

			if(area > 0) {
				double area2 = double(area) / 2.0;
				ans += area2 * area2;
			}
		}
	}

	cout << fixed << setprecision(10);
	cout << ans << '\n';
}

signed main() {
	ios::sync_with_stdio(false); cin.tie(0);
	solve();
}
