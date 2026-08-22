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

void dfs (ll n , vector<vll>& adj , vector<bool> visited  , ll k) {
    for (ll neighbor : adj[n]) {

    }

}

int main() {
    _;
    ll n , m ; 
    cin >> n >> m;
    vll vnode (n)
    forn(i,0,n)
    vector<vll> adj (n);
    vector<bool> visited (n);
    forn(i,0,m) {
        ll a , b;
        --a ; --b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }


    return 0;
}
