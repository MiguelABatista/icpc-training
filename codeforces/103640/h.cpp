// MinCostMaxFlow
//
// min_cost_flow(s, t, f) computa o par (fluxo, custo)
// com max(fluxo) <= f que tenha min(custo)
// min_cost_flow(s, t) -> Fluxo maximo de custo minimo de s pra t
// Se for um dag, da pra substituir o SPFA por uma DP pra nao
// pagar O(nm) no comeco
// Se nao tiver aresta com custo negativo, nao precisa do SPFA
//
// O(nm + f * m log n)

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64; 
typedef vector<ll> v64;

#define forn(i, s, e) for(ll i = (s); i < (e); i++)
#define ln "\n"
#define sz(x) ((ll)x.size())

#if defined(DEBUG)
    #define _ (void)0
    #define debug(x) cout << __LINE__ << ": " << #x << " = " << x << ln
#else
    #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
    #define debug(x) (void)0
#endif

const ll INF = 0x3f3f3f3f3f3f3f3fll;

template<typename T> struct mcmf {
	struct edge {
		ll to, rev, flow, cap; // para, id da reversa, fluxo, capacidade
		bool res; // se eh reversa
		T cost; // custo da unidade de fluxo
		edge() : to(0), rev(0), flow(0), cap(0), cost(0), res(false) {}
		edge(ll to_, ll rev_, ll flow_, ll cap_, T cost_, bool res_)
			: to(to_), rev(rev_), flow(flow_), cap(cap_), res(res_), cost(cost_) {}
	};

	vector<vector<edge>> g;
	vector<ll> par_idx, par;
	T inf;
	vector<T> dist;

	mcmf(ll n) : g(n), par_idx(n), par(n), inf(numeric_limits<T>::max()/3) {}

	void add(ll u, ll v, ll w, T cost) { // de u pra v com cap w e custo cost
		edge a = edge(v, g[v].size(), 0, w, cost, false);
		edge b = edge(u, g[u].size(), 0, 0, -cost, true);

		g[u].push_back(a);
		g[v].push_back(b);
	}

	vector<T> spfa(ll s) { // nao precisa se nao tiver custo negativo
		deque<ll> q;
		vector<bool> is_inside(g.size(), 0);
		dist = vector<T>(g.size(), inf);

		dist[s] = 0;
		q.push_back(s);
		is_inside[s] = true;

		while (!q.empty()) {
			ll v = q.front();
			q.pop_front();
			is_inside[v] = false;

            forn(i,0,sz(g[v])){
				auto [to, rev, flow, cap, res, cost] = g[v][i];
				if (flow < cap && dist[v] + cost < dist[to]) {
					dist[to] = dist[v] + cost;

					if (is_inside[to]) continue;
					if (!q.empty() && dist[to] > dist[q.front()]) q.push_back(to);
					else q.push_front(to);
					is_inside[to] = true;
				}
			}
		}
		return dist;
	}
	bool dijkstra(ll s, ll t, vector<T>& pot) {
		priority_queue<pair<T, ll>, vector<pair<T, ll>>, greater<>> q;
		dist = vector<T>(g.size(), inf);
		dist[s] = 0;
		q.emplace(0, s);
		while (q.size()) {
			auto [d, v] = q.top();
			q.pop();
			if (dist[v] < d) continue;
            forn(i,0,sz(g[v])) {
				auto [to, rev, flow, cap, res, cost] = g[v][i];
				cost += pot[v] - pot[to];
				if (flow < cap && dist[v] + cost < dist[to]) {
					dist[to] = dist[v] + cost;
					q.emplace(dist[to], to);
					par_idx[to] = i, par[to] = v;
				}
			}
		}
		return dist[t] < inf;
	}

	pair<ll, T> min_cost_flow(ll s, ll t, ll flow = INF) {
		vector<T> pot(g.size(), 0);
		pot = spfa(s); // mudar algoritmo de caminho minimo aqui
        // sem custo negativo não precisa de nada
        // se grafo for um DAG usar
		ll f = 0;
		T ret = 0;
		while (f < flow && dijkstra(s, t, pot)) {
            forn(i,0,sz(g))
				if (dist[i] < inf) pot[i] += dist[i];

			ll mn_flow = flow - f, u = t;
			while (u != s){
				mn_flow = min(mn_flow,
					g[par[u]][par_idx[u]].cap - g[par[u]][par_idx[u]].flow);
				u = par[u];
			}

			ret += pot[t] * mn_flow;

			u = t;
			while (u != s) {
				g[par[u]][par_idx[u]].flow += mn_flow;
				g[u][g[par[u]][par_idx[u]].rev].flow -= mn_flow;
				u = par[u];
			}

			f += mn_flow;
		}

		return make_pair(f, ret);
	}

	// Opcional: retorna as arestas originais por onde passa flow = cap
	vector<pair<ll,ll>> recover() {
		vector<pair<ll,ll>> used;
		forn(i, 0, sz(g)) for (edge e : g[i])
			if(e.flow == e.cap && !e.res) used.push_back({i, e.to});
		return used;
	}
};


int main() {
    _; ll n; cin >> n;

    vector<vector<ll>> mat(n+1, v64(n+1));

    forn(i,1,n+1){
        forn(j,1,n+1){
            cin >> mat[i][j];
        }
    }

    mcmf<ll> flow(n+3);

    // vertice 0 e fantasma pra encodar  primeiro impar -> 2 
    // vertic 2k liga no 2l+1 com d(2k, 2l+1) + d(2k+2, 2l+1)
    // n+1 source
    // n+2 tink
    ll source = n+1;
    ll tink = n+2;

    for(ll imp = 1; imp <= n; imp+=2){
        flow.add(0, imp, 1, mat[imp][2]);
    }

    for(ll imp = 1; imp <= n; imp+=2){
        for(ll par = 2; par <= n-2; par+=2){
            flow.add(par, imp, 1, mat[par][imp] + mat[imp][par+2]);
        }
    }

    if(n%2 == 1){
        // for(ll par = 2; par <= n-2; par+=2){
        for(ll imp = 1; imp <= n; imp+=2){
            flow.add(n-1, imp, 1, mat[n-1][imp]);
        }
    }
    

    for(ll imp = 1; imp <= n; imp+=2){
        flow.add(imp, tink, 1, 0);
    }

    for(ll par = 0; par <= n; par+=2){
        flow.add(source, par, 1, 0);
    }

    cout << flow.min_cost_flow(source, tink).second << ln;
    return 0;
}