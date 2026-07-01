#include <bits/stdc++.h>
using namespace std;

// #pragma GCC optimize ("Ofast")
// #pragma GCC optimize ("unroll-loops")
// #pragma GCC target ("avx,avx2,tune=native")

#ifdef LOCAL
#include "misc/debug.h"
#else
#define debug(...) 42
#endif

using ll = long long;
using db = double;  // or db, if TL is tight
#define int ll

// pairs
#define mp make_pair
#define f first
#define s second

// vectors
#define sz(v) (int)((v).size())
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()

const int MX = 505, MK = 20;

bool vis[MX][MK][MK][MX];
db memo[MX][MK][MK][MX];

int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, k, h, s; cin >> n >> k >> s >> h;

	vector<db> b(n + 1), c(n + 1), v(n + 1), q(n + 1);
	for (int i = 1; i <= n; i++) {
		string _b, _c, _v, _q; cin >> _b >> _c >> _v >> _q;
		b[i] = stold(_b);
		c[i] = stold(_c);
		v[i] = stold(_v);
		q[i] = stold(_q);
	}
	
	auto dp = [&](auto &&self, int i, int j, int y, int x) -> db {
		// debug(i, j, y, x);
		if (y >= h) return 0.0;
		if (i > n) return 1.0;
		
		auto &res = memo[i][j][y][x];
		
		if (vis[i][j][y][x]) return res;
		db p = db(x + 1) / db(i + 1);
		
		// debug(p, self(self, i + 1, j, y + 1, x + 1), self(self, i + 1, j, y + 1, x));

		res = 0.0;
		res = max(res, p * self(self, i + 1, j, y + 1, x + 1) 
						+ (1.0 - p) * self(self, i + 1, j, y + 1, x));
	
		if (p < 1.0) {
			auto get = [&](int cur) {
				db ret = 0.0;
				if (cur >= 2) {
					db opt1 = b[i] * self(self, i + 1, min(k, cur - 1), y + 1, x);
					db opt2 = (1.0 - b[i]) * self(self, i + 1, cur - 2, y + 1, x);
					ret += q[i] * (opt1 + opt2);
				}
				
				db opt1 = b[i] * self(self, i + 1, min(k, cur + 1), y + 1, x);
				db opt2 = (1.0 - b[i]) * self(self, i + 1, cur, y + 1, x);
					
				ret += (1.0L - q[i]) * (opt1 + opt2);
				return ret;
			};

			res = max(res, (1.0 - p) * get(j));
		}

		if (p < 1.0) {
			auto get = [&](int cur) {
				db ret = 0.0;
				if (cur >= 2) {
					db opt1 = c[i] * (1.0L - v[i]) * self(self, i + 1, cur - 2, 0, x);;
					db opt2 = (1.0L - c[i]) * self(self, i + 1, cur - 2, y + 1, x);
					ret += q[i] * (opt1 + opt2);
				}

				{
					db opt1 = c[i] * (1.0L - v[i]) * self(self, i + 1, cur, 0, x);;
					db opt2 = (1.0L - c[i]) * self(self, i + 1, cur, y + 1, x);
					ret += (1.0L - q[i]) * (opt1 + opt2);
				}

				return ret;
			};

			res = max(res, (1.0 - p) * get(j));
		}

		vis[i][j][y][x] = true;
		return res;
	};

	cout << setprecision(12) << fixed << dp(dp, 1, s, 0, 0) << "\n";
}