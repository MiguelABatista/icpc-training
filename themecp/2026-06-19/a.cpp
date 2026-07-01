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
    ll n; cin >> n;
    vector<vll> g(n);
    forn(i,0,n-1){
        ll a, b; cin >> a >> b;
        a--, b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    vll down(n);
    ll diam = 0;

    function<void (ll, ll)> dfs = [&](ll u, ll p){
        ll m1 = 0;
        ll m2 = 0;
        for(ll v : g[u]){
            if(v == p) continue;
            dfs(v,u);
            ll d = down[v]+1;
            if(d > m1){
                m2 = m1;
                m1 = d;
            }else if(d > m2){
                m2 = d;
            }
        }
        down[u] = m1;
        diam = max(diam, m1 + m2);
    };
    
    dfs(0,-1);
    
    cout << diam << ln;

    return 0;
}
