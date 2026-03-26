#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> p64;
typedef vector<ll> v64;

#define forn(i, s, e) for (ll i = (s); i < (e); i++)
#define sz(u) ((ll) u.size())
#define ln "\n"

#ifdef DEBUG
#define trace(u) u
#define _
#else
#define trace(u)
#define _ ios::sync_with_stdio(0); cin.tie(0)
#endif

#define debug(u) trace(cout << #u " = " << u << ln)
#define debugv(v) trace(cout << #v ": "; for (auto xx : v) cout << xx << " "; cout << ln)

int main() {
    int n;
    ld velo;
    if (!(cin >> n >> velo)) return 0;

    vector<ld> prio, nprio;
    for (int i = 0; i < n; i++) {
        char c; ld x;
        cin >> c >> x;
        if (c == 'P') prio.push_back(x);
        else nprio.push_back(x);
    }

    // Ordenar crescente para facilitar o acesso ao menor (que termina antes)
    sort(prio.begin(), prio.end());
    sort(nprio.begin(), nprio.end());

    ld tot = 0;
    while (!prio.empty() || !nprio.empty()) {
        ld v_p_total = 0, v_n_total = 0;

        // Distribuição de banda
        if (!prio.empty() && !nprio.empty()) {
            v_p_total = velo * 0.75;
            v_n_total = velo * 0.25;
        } else {
            v_p_total = velo; // Se um grupo acabar, o outro pega 100%
            v_n_total = velo;
        }

        ld tp = 1e18, tn = 1e18;
        if (!prio.empty()) tp = prio[0] / (v_p_total / prio.size());
        if (!nprio.empty()) tn = nprio[0] / (v_n_total / nprio.size());

        ld t = min(tp, tn);
        tot += t;
        debug(t);
        // Atualiza e remove quem terminou
        ld vp = v_p_total / (prio.empty() ? 1 : prio.size());
        ld vn = v_n_total / (nprio.empty() ? 1 : nprio.size());

        vector<ld> next_prio, next_nprio;
        for (auto x : prio) if (x - vp * t > 1e-9) next_prio.push_back(x - vp * t);
        for (auto x : nprio) if (x - vn * t > 1e-9) next_nprio.push_back(x - vn * t);
        
        prio = next_prio;
        nprio = next_nprio;
        
        sort(prio.begin(), prio.end());
        sort(nprio.begin(), nprio.end()); 

        debugv(prio);
        debugv(nprio);
        debug(sz(prio));
        debug(sz(nprio));
    } 
 
    cout << fixed << setprecision(10) << (double)tot << endl;
    return 0;
}