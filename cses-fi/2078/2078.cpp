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
const ll MOD = 1'000'000'007;

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
    ll n, m;
    cin >> n >> m;
    vll pot2(m+1);
    pot2[0] = 1;
    forn(i,1,m+1){
        pot2[i] = (2*pot2[i-1])%MOD;
    }

    vector<pll> v;
    dsu sdu(n);
    forn(i,0,m){
        ll a, b;
        cin >> a >> b;
        v.push_back({a,b});
        sdu.uni(a,b);
    }

    map<ll,ll> mp;
    for(auto [a,b] : v){
        if(sdu.find(a) == sdu.find(b)){
            mp[sdu.find(a)]++;
        }
    }
    ll resp = 1;
    for(auto [p, ed] : mp){
        ll np = sdu.len[p];
        debug(pot2[ed-np+1]);
        resp = (resp*pot2[ed-np+1])%MOD; 
    }
    cout << resp << ln;
    return 0;
}
