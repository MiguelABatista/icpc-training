#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64; 
typedef vector<ll> v64;

#define forn(i, s, e) for(ll i = (s); i < (e); i++)
#define ln "\n"

#if defined(DEBUG)
    #define _ (void)0
    #define debug(x) cout << __LINE__ << ": " << #x << " = " << x << ln
#else
    #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
    #define debug(x) (void)0
#endif

const ll INF = 1'000'000'000;

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

template<typename T> struct mcmf {
	struct edge {
		int to, rev, flow, cap; // para, id da reversa, fluxo, capacidade
		bool res; // se eh reversa
		T cost; // custo da unidade de fluxo
		edge() : to(0), rev(0), flow(0), cap(0), cost(0), res(false) {}
		edge(int to_, int rev_, int flow_, int cap_, T cost_, bool res_)
			: to(to_), rev(rev_), flow(flow_), cap(cap_), res(res_), cost(cost_) {}
	};

	vector<vector<edge>> g;
	vector<int> par_idx, par;
	T inf;
	vector<T> dist;

	mcmf(int n) : g(n), par_idx(n), par(n), inf(numeric_limits<T>::max()/3) {}

	void add(int u, int v, int w, T cost) { // de u pra v com cap w e custo cost
		edge a = edge(v, g[v].size(), 0, w, cost, false);
		edge b = edge(u, g[u].size(), 0, 0, -cost, true);

		g[u].push_back(a);
		g[v].push_back(b);
	}

	vector<T> spfa(int s) { // nao precisa se nao tiver custo negativo
        deque<int> q;
		vector<bool> is_inside(g.size(), 0);
		dist = vector<T>(g.size(), inf);

		dist[s] = 0;
		q.push_back(s);
		is_inside[s] = true;

		while (!q.empty()) {
			int v = q.front();
			q.pop_front();
			is_inside[v] = false;

			for (int i = 0; i < g[v].size(); i++) {
				auto [to, rev, flow, cap, res, cost] = g[v][i];
				if (flow < cap and dist[v] + cost < dist[to]) {
					dist[to] = dist[v] + cost;

					if (is_inside[to]) continue;
					if (!q.empty() and dist[to] > dist[q.front()]) q.push_back(to);
					else q.push_front(to);
					is_inside[to] = true;
				}
			}
		}
		return dist;
	}
	bool dijkstra(int s, int t, vector<T>& pot) {
		priority_queue<pair<T, int>, vector<pair<T, int>>, greater<>> q;
		dist = vector<T>(g.size(), inf);
		dist[s] = 0;
		q.emplace(0, s);
		while (q.size()) {
			auto [d, v] = q.top();
			q.pop();
			if (dist[v] < d) continue;
			for (int i = 0; i < g[v].size(); i++) {
				auto [to, rev, flow, cap, res, cost] = g[v][i];
				cost += pot[v] - pot[to];
				if (flow < cap and dist[v] + cost < dist[to]) {
					dist[to] = dist[v] + cost;
					q.emplace(dist[to], to);
					par_idx[to] = i, par[to] = v;
				}
			}
		}
		return dist[t] < inf;
	}

	pair<int, T> min_cost_flow(int s, int t, int flow = INF) {
		vector<T> pot(g.size(), 0);
		pot = spfa(s); // mudar algoritmo de caminho minimo aqui

		int f = 0;
		T ret = 0;
        debug("A");
		while (f < flow and dijkstra(s, t, pot)) {
			for (int i = 0; i < g.size(); i++)
				if (dist[i] < inf) pot[i] += dist[i];

			int mn_flow = flow - f, u = t;
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
            debug(f);
		}

		return make_pair(f, ret);
	}

	// Opcional: retorna as arestas originais por onde passa flow = cap
	vector<pair<int,int>> recover() {
		vector<pair<int,int>> used;
		for (int i = 0; i < g.size(); i++) for (edge e : g[i])
			if(e.flow == e.cap && !e.res) used.push_back({i, e.to});
		return used;
	}
};

int main(){
    _;
    ll n; cin >> n;
    v64 freq(21,0);
    ll resp = 0;

    forn(i,0,n){
        ll aux; cin >> aux;
        freq[aux]++;
    }

    v64 valid;
    forn(x,1,21){
        if(freq[x] == 0) continue;
        valid.push_back(x);    
    }

    ll t = valid.size();

    mcmf<ll> flow(2*t+3);
    ll tink = 2*t;
    ll source = 2*t+1;

    // i in = 2*i
    // i out = 2*i + 1 

    forn(i,0,t){
        flow.add(source, 2*i, 1, 0);
        flow.add(2*i+1,tink , 1, 0);
        flow.add(2*i,2*i+1 , 1, 0);
        
    }

    forn(i,0,t){
        forn(j,0,t){
            if(i == j) continue;
            flow.add(2*i+1, 2*j, 1, -gcd(valid[i], valid[j]));
        }
    }

    debug(1);
    resp -= flow.min_cost_flow(source, tink , 1).second;
    debug(1);
    
    forn(i,1,21){
        if(freq[i] == 0) continue;
        
        resp += i*(freq[i]-1);
    }
    
    cout << resp << ln;
    return 0;
}