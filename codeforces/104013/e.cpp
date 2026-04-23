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
#define debugm(v) trace(cout << #v ": "; for (auto xx : v) cout << xx.first.first << ":" << xx.first.second << " : " << xx.second << " "; cout << ln)
#define debugp(v) trace(cout << #v ": "; for (auto xx : v) cout << xx.first << ":" << xx.second << " "; cout << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;

template<bool directed=false> struct euler{
    ll n; 
    vector<vector<pll>> g;
    vll used;
    
    euler(ll n_) : n(n_), g(n) {}
    void add(ll a, ll b) {
        ll at = sz(used);
        used.push_back(0);
        g[a].emplace_back(b, at);

    }
    pair<bool, vector<pll>> get_path(ll src){
        if(!sz(used)) return {true, {}};
        vll beg(n,0);
        for (ll& i : used) i = 0;

        vector<pair<pll,ll>> ret, st = {{{src,-1}, -1}};
        while(sz(st)){
            ll at = st.back().first.first;
            ll&  it = beg[at];
            while(it < sz(g[at]) && used[g[at][it].second]) it++;
            if(it == sz(g[at])) {
                if(sz(ret) && ret.back().first.second != at)
                    return {false, {}};
                ret.push_back(st.back()), st.pop_back();
            } else {
                st.push_back({{g[at][it].first, at}, g[at][it].second});
                used[g[at][it].second] = 1;
            }
        }
        if (sz(ret) != sz(used) + 1) return {false, {}};
        vector<pll> ans;
        for (auto i : ret) ans.emplace_back(i.first.first, i.second);
        reverse(ans.begin(), ans.end());
        return {true, ans};
    }
};

int main() {
    _; ll m, c; cin >> m >> c;
    vector<tuple<ll,ll,ll>> g_true, g_false;

    vll vals;
    vals.push_back(c);

    forn(i, 0, m){
        ll a, b, w;
        cin >> a >> b >> w;
        if(w == 1) g_true.emplace_back(a,b,i);
        if(w == 0) g_false.emplace_back(a,b,i);

        vals.push_back(a);
        vals.push_back(b);
    }

    sort(vals.begin(), vals.end());
    ll n = sz(vals);
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    auto compress = [&](ll& x){
        x = (ll)(lower_bound(vals.begin(), vals.end(), x)-vals.begin());
    };
    compress(c);
    for(auto& [a,b,i] : g_true){
        compress(a);
        compress(b);
    }    
    for(auto& [a,b,i] : g_false){
        compress(a);
        compress(b);
    } 

    trace(
        for(auto [a,b,i] : g_false) cout << a << " " << b << " " << i << " | ";
        cout << ln;
    )

    euler<true> eu(n);
    vll conv;
    for(auto& [a,b,i] : g_true){
        eu.add(a,b);
        conv.push_back(i);
    }

    auto [ok, path] = eu.get_path(c);
    
    if(!ok){
        cout << "No" << ln;
        return 0;
    }

    vll resp;
    ll idx = 0;
    
    debugp(path);
    
    while (idx+1 < sz(path) && path[idx+1].first == c){
        resp.push_back(conv[path[idx+1].second]);
        idx++;
    }
    
    path.erase(path.begin(), path.begin() + idx);
    
    debugp(path);
    debugv(conv);
    debugv(resp);

    if(sz(path) == 0){
        if(sz(g_true)){
            cout << "No" << ln;
            return 0;
        }
        for(auto& [a,b,i] : g_false){
            if(a == c){ 
                cout << "No" << ln;
                return 0;
            }
        }
        cout << "YES" << ln;
        for(auto& [a,b,i] : g_false) resp.push_back(i);
        forn(i,0,m) cout << resp[i]+1 << " \n"[i==m-1];
        return 0;
    } 

    if(sz(path) == 1){
        for(auto& [a,b,i] : g_false){
            if(a == c){ 
                cout << "No" << ln;
                return 0;
            }
        }
        
        cout << "YES" << ln;
        for(auto& [a,b,i] : g_false) resp.push_back(i);
        forn(i,0,m) cout << resp[i]+1 << " \n"[i==m-1];
        return 0;
    }
    
    cout << "YES" << ln;
    for(auto& [a,b,i] : g_false){
        if(a == c) continue;
        resp.push_back(i);
    }

    resp.push_back(conv[path[1].second]);

    for(auto& [a,b,i] : g_false){
        if(a != c) continue;
        resp.push_back(i);
    }

    forn(i,1,sz(path)-1){
        debug(path[i+1].first);
        debug(path[i+1].second);
        resp.push_back(conv[path[i+1].second]);
    }
    forn(i,0,m) cout << resp[i]+1 << " \n"[i==m-1];
    return 0;
}
