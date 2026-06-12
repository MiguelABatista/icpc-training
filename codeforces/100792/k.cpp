#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;
typedef vector<ll> vll;

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

const ll INF = 0x3f3f3f3f3f3f3f3fll;

int main() {
    _;
    ll n, m; cin >> n >> m;

    vector<vll> g(n);
    vll indeg(n);
    set<ll> s;
    vll resp;

    forn(i,0,m){
        ll a,b; cin >> a >> b;
        a--, b--;
        g[b].push_back(a);
        indeg[a]++;
    }

    forn(i,0,n) if(indeg[i] == 0) s.insert(i);

    while(!s.empty()){
        auto it = prev(s.end());
        ll nxt = *it;
        resp.push_back(nxt);
        s.erase(it);
        for(ll u : g[nxt]){
            indeg[u]--;
            if(indeg[u] == 0) s.insert(u);
        }
    }

    reverse(resp.begin(), resp.end());

    forn(i,0,n) cout << resp[i]+1 << " \n"[i==n-1];

    return 0;
}
