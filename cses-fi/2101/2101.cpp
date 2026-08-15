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

// Disjoint Set Union (Union-Find)
//
// Supports find with path compression and union by size to maintain dynamic connectivity of disjoint sets.
//
// complexity: O(alpha(N)) amortized per op, O(N)

struct dsu {
    vll id, len;

    dsu(ll n) : id(n), len(n, 1) { iota(id.begin(), id.end(), 0); }

    ll find(ll a) { return a == id[a] ? a : id[a] = find(id[a]); }

    bool uni(ll a, ll b) {
        a = find(a), b = find(b);
        if (a == b) return false;
        if (len[a] < len[b]) swap(a, b);
        len[a] += len[b], id[b] = a;
        return true;
    }
};

int main() {
    _;
    ll n, m, q; cin >> n >> m >> q;
    vector<pll> edges(m);
    forn(i,0,m){
        ll a, b; cin >> a >> b;
        a--, b--;
        edges[i] = {a,b};
    }

    vll l(q);
    vll r(q, m-1);
    vll ans(q,-2);

    vector<pll> queries(q);
    forn(i,0,q){
        ll a, b; cin >> a >> b;
        a--, b--;
        queries[i] = {a,b};
    }

    while (true){
        debugv(l);
        debugv(r);
        vector<vll> mid(m);
        ll cnt = 0;
        forn(i,0,q){
            if(l[i] <= r[i]){
                mid[(l[i]+r[i])/2].push_back(i);
                cnt++;
            }
        }
        if(cnt == 0) break;

        dsu sdu(n);
        forn(i,0,m){
            sdu.uni(edges[i].first, edges[i].second);

            for(ll x: mid[i]){
                if(sdu.find(queries[x].first) == sdu.find(queries[x].second)){
                    ans[x] = i;
                    r[x] = i-1;
                }else{
                    l[x] = i+1;
                }
                if((l[x]+r[x])/2 > i) mid[(l[x]+r[x])/2].push_back(x);
            }
        }
    }

    forn(i,0,q){
        if(queries[i].first == queries[i].second) ans[i] = -1;
    }
    forn(i,0,q) cout << ans[i]+1 << ln; 
    return 0;
}
