#include<bits/stdc++.h>

using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'

typedef long long ll;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;

const int MAX = 1e5 + 10;

bool dead[MAX];
ll d[MAX];
vector<pair<int, int>> g[MAX];

void dijkstra(int v) {
	d[v] = 0;
	priority_queue<pair<ll, int>> pq;
	pq.emplace(0, v);

	while (pq.size()) {
		auto [ndist, u] = pq.top(); pq.pop();
		if (-ndist > d[u]) continue;

		for (auto [idx, w] : g[u]) if (!dead[idx] and d[idx] > d[u] + w) {
			d[idx] = d[u] + w;
			pq.emplace(-d[idx], idx);
		}
	}
}

ll ans[MAX];
int qv[MAX], qu[MAX];

vector<int> q_now[MAX];

pair<int, int> mid(int l, int r) {
	int m = (l + r)/2;
	return {max(l, m - 5), min(r, m + 4)};
}

bool now(int u, int v, int l, int r) {
	return l <= u and u <= r and l <= v and v <= r;
}

int main() { _
	memset(ans, INF, sizeof ans);

	int n, m, q; cin >> n >> m >> q;
	for (int i = 0; i < m; i++) {
		int u, v, w; cin >> u >> v >> w; u--, v--;
		g[u].emplace_back(v, w);
		g[v].emplace_back(u, w);
	}

	for (int i = 0; i < q; i++) {
		cin >> qv[i] >> qu[i]; qv[i]--, qu[i]--;
		if (qv[i] > qu[i]) swap(qv[i], qu[i]);
	}

	vector<pair<int, int>> ranges = {{0, n - 1}};

	while (not ranges.empty()) {

		for (int i = 0; i < q; i++) {
			int j = upper_bound(ranges.begin(), ranges.end(), pair(qv[i], INF)) - ranges.begin();
			j--;
			if (j < 0) continue;
			if (now(qv[i], qu[i], ranges[j].first, ranges[j].second)) {
				q_now[j].push_back(i);
			}
		}

		for (int r_i = 0; r_i < ranges.size(); r_i++) {
			auto [l, r] = ranges[r_i];
			auto [L, R] = mid(l, r);

			for (int v = L; v <= R; v++) {
				for (int i = l; i <= r; i++) d[i] = LINF;
				
				dijkstra(v);

				for (int qid : q_now[r_i])
					ans[qid] = min(ans[qid], d[qv[qid]] + d[qu[qid]]);
			}

			for (int i = L; i <= R; i++) dead[i] = true;
			q_now[r_i].clear();
		}

		vector<pair<int, int>> n_ranges;
		for (auto [l, r] : ranges) {
			auto [L, R] = mid(l, r);
			
			if (l < L) n_ranges.emplace_back(l, L - 1);
			if (R < r) n_ranges.emplace_back(R + 1, r);
		}

		swap(ranges, n_ranges);
	}

	for (int i = 0; i < q; i++) cout << (ans[i] != LINF ? ans[i] : -1) << endl;

	exit(0);
}

