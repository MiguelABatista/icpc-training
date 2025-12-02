#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64; 
typedef vector<ll> v64;

#define forn(i, s, e) for(ll i = (s); i < (e); i++)
#define sz(x) ((ll) x.size())
#define ln "\n"

#ifdef DEBUG
    #define trace(x) x
    #define _ (void)0
#else
    #define trace(x) (void)0
    #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
#endif

#define debugv(v) trace({cout << #v": "; for (auto x : v) cout<< x << " "; cout << ln;})
#define debug(x) trace(cout << __LINE__ << ": " #x " = " << x << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;

// Hungaro
//
// Resolve o problema de assignment (matriz n x n)
// Colocar os valores da matriz em 'a' (pode < 0)
// assignment() retorna um par com o valor do
// assignment minimo, e a coluna escolhida por cada linha
//
// O(n^3)

template<typename T> struct hungarian {
	int n;
	vector<vector<T>> a;
	vector<T> u, v;
	vector<int> p, way;
	T inf;

	hungarian(int n_) : n(n_), u(n+1), v(n+1), p(n+1), way(n+1) {
		a = vector<vector<T>>(n, vector<T>(n));
		inf = numeric_limits<T>::max();
	}
	pair<T, vector<int>> assignment() {
		for (int i = 1; i <= n; i++) {
			p[0] = i;
			int j0 = 0;
			vector<T> minv(n+1, inf);
			vector<int> used(n+1, 0);
			do {
				used[j0] = true;
				int i0 = p[j0], j1 = -1;
				T delta = inf;
				for (int j = 1; j <= n; j++) if (!used[j]) {
					T cur = a[i0-1][j-1] - u[i0] - v[j];
					if (cur < minv[j]) minv[j] = cur, way[j] = j0;
					if (minv[j] < delta) delta = minv[j], j1 = j;
				}
				for (int j = 0; j <= n; j++)
					if (used[j]) u[p[j]] += delta, v[j] -= delta;
					else minv[j] -= delta;
				j0 = j1;
			} while (p[j0] != 0);
			do {
				int j1 = way[j0];
				p[j0] = p[j1];
				j0 = j1;
			} while (j0);
		}
		vector<int> ans(n);
		for (int j = 1; j <= n; j++) ans[p[j]-1] = j-1;
		return make_pair(-v[0], ans);
	}
};

int main(){
    _;
    ll n; cin >> n;
    hungarian<ll> hun(n);

    forn(i,0,n)
    forn(j,0,n)
        cin >> hun.a[i][j];

    auto [val, ans] = hun.assignment();

    cout << val << ln;
    forn(i,0,n){
        cout << i+1 << " " << ans[i]+1 << ln;
    }
    return 0;
}