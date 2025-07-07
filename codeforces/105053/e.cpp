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

const ll INF = 0x3f3f3f3f3f3f3f3fll;

int main(){
    _;
    ll n; cin >> n;
    v64 in(n + 1), out(n + 1);
    forn(i, 0, 2*n) {
        ll aux; cin >> aux;
        if (aux > 0) in[aux-1] = i;
        else out[abs(aux)-1] = i;
    }
    vector<v64> g(n);
    forn(i, 0, n) {
        forn(j, i+1, n) {
            if(out[i] < in[j] || out[j] < in[i]) continue;
            if ((in[i] < in[j] && out[i] < out[j]) || (in[j] < in[i] && out[j] < out[i])) {
                g[i].push_back(j);
                g[j].push_back(i);
            }
        }
    }

    v64 state(n);

    function<void (ll ,ll)> dfs = [&](ll u, ll st) {
        state[u] = st;
        if (st == 1) st = 2;
        else st = 1;

        for (auto v : g[u]) {
            if (state[v] != 0) {
                if (state[v] != st) {
                    cout << "*\n";
                    exit(0);
                } else {
                    continue;
                }
            }
            dfs(v, st);
        }
    };

    forn(i, 0, n) {
        if (state[i] == 0) dfs(i, 1);
    }

    forn(i, 0, n) {
        cout << "AGS"[state[i]];
    }
    cout << ln;
    return 0;
}