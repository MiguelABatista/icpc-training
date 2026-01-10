#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64; 
typedef vector<ll> v64;

#define forn(i, s, e) for(ll i = (s); i < (e); i++)
#define sz(x) ((ll) x.size())
#define ln "\n"

#ifdef DEBUG
    #define trace(x) x
    #define _ (void)0
#else
    #define trace(x) (void)0
    #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
#endif

#define debugv(v) trace({cout << #v": "; for (auto x : v) cout<< x << " "; cout << ln;})
#define debug(x) trace(cout << __LINE__ << ": " #x " = " << x << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;

int main(){
    _;
    ll n, m; cin >> n >> m;
    map<string, ll> mp;
    ll cnt = 0;

    auto id = [&](string s) {
        if (mp.find(s) == mp.end()) {
            mp[s] = cnt++;
        } 
        return mp[s];
    };

    vector<vector<pair<ll, bool>>> g(200);

    forn(i, 0, n) {
        string s; cin >> s;
        ll a = id(s);
        cin >> s >> s >> s >> s;
        ll b = id(s);
        g[a].emplace_back(b, true);
        g[b].emplace_back(a, false);
    }

    function<bool (ll, ll, bool)> dfs = [&](ll u, ll tgt, bool dir) {
        if (u == tgt) return true;

        for (auto v : g[u]) {
            if (v.second != dir) continue;
            if (dfs(v.first, tgt, dir)) return true;
        }

        return false;
    };

    forn(i, 0, m) {
        string s; cin >> s;
        ll a = id(s);
        cin >> s >> s >> s >> s;
        ll b = id(s);
        if (dfs(a, b, true)) {
            cout << "Fact" << ln;
        } else if (dfs(a, b, false)) {
            cout << "Alternative Fact" << ln;
        } else {
            cout << "Pants on Fire" << ln;
        }
    }

    return 0;
}