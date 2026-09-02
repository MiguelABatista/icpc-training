#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pll;
typedef vector<ll> vll;

#define forn(i,s,e) for(ll i=s; i<e; i++)
#define sz(u) ((ll) u.size())
#define ln "\n"

#ifdef DEBUG
#define trace(u) u
#define _
#else
#define trace(u)
#define _ ios::sync_with_stdio(0); cin.tie(0)
#endif

#define debug(u) trace(cout << #u " = " << u << ln);
#define debugv(v) trace(cout << #v ": " ;for(auto xx : v) cout << xx << " ";cout << ln);
#define debugm(v) trace(cout << #v ": " ;for(auto xx : v) cout << xx.first << ":" << xx.second << " ";cout << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;

int main(){
    _;
    ll f, n; cin >> f >> n;
    
    vll vals;

    auto compress = [&](ll& x){
        x = (ll)(lower_bound(vals.begin(), vals.end(), x) - vals.begin());
    };

    vll amigo(n);
    vll qnt(n);

    forn(i,0,n){
        cin >> amigo[i] >> qnt[i];
        vals.push_back(amigo[i]);
    }

    vector<tuple<char,ll,ll>> respostas(n);

    forn(i,0,n){
        char c; cin >> c;
        if(c == 'A'){
            ll a, t; cin >> a >> t;
            respostas[i] = {c,a,t};
        }
        if(c == 'D'){
            respostas[i] = {c, -1, -1};
        }
        if(c == 'T'){
            ll x; cin >> x;
            vals.push_back(x);
            respostas[i] = {c, x, -1};
        }
    }

    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());

    forn(i,0,n) compress(amigo[i]);    
    
    forn(i,0,n){
        auto [c,a,b] = respostas[i];
        if(c == 'T') compress(a);
        respostas[i] = {c,a,b};
    }
    
    ll gn = sz(vals)+5;

    vector<vll> g(gn);

    forn(i,0,n){
        auto [c,a,b] = respostas[i];
        if(c == 'T'){
            g[a].push_back(amigo[i]);   
        }
    }

    vll pai(gn, -1);

    function<void (ll, ll)> dfs = [&](ll u, ll p){
        pai[u] = (p != -1 ? pai[p] : u);

        for(ll v : g[u]) if(v != p) dfs(v,u);
    };

    forn(i,0,n){
        auto [c,a,b] = respostas[i];
        if(c == 'A') dfs(amigo[i],-1);
    }


    debugv(amigo);
    debugv(pai);

    map<ll, ll> mp;

    forn(i,0,n){
        if(pai[amigo[i]] != -1){
            debug(i);
            debug(qnt[i]);
            mp[pai[amigo[i]]] += qnt[i];
        }
    }

    debugm(mp);
    
    map<ll, ll> sweep;
    forn(i,0,n){
        auto [c,a,b] = respostas[i];
        if(c == 'A'){
            ll tini = a;
            ll tfim = a+b;
            sweep[tini] += mp[amigo[i]];
            sweep[tfim] -= mp[amigo[i]];
        }
    }    
    ll curr = 0;
    ll resp = 0;

    for(auto [k, v] : sweep){
        curr += v;
        resp = max(resp, curr); 
    }

    cout << resp << ln;
    return 0;
}  