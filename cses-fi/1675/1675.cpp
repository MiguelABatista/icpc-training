#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
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

const ll INF = 0x3f3f3f3f3f3f3f3fll;

// Disjoint Set Union (Union-Find)
//
// Supports find with path compression and union by size to maintain dynamic connectivity of disjoint sets.
//
// complexity: O(alpha(N)) amortized per op, O(N)

struct dsu {
    v64 id, len;

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
    ll n, m;
    cin >> n >> m;
    
    vector<tuple<ll,ll,ll>> ed(m);

    forn(i,0,m){
        ll a, b, c;
        cin >> a >> b >> c;
        a--; b--;
        ed[i] = {c,a,b};
    }

    dsu sdu(n);
    sort(ed.begin(), ed.end());
    ll resp = 0;

    for(auto [c,a,b] : ed){
        bool bo = sdu.uni(a,b);
        resp += c*bo;
    }
    if(sdu.len[sdu.find(0)] != n){
        cout << "IMPOSSIBLE" << ln;
        return 0;
    }
    cout << resp << ln;
    return 0;
}
