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
#define debugm(v) trace(cout << #v ": "; for (auto xx : v) cout << xx.first << ":" << xx.second << " "; cout << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;

ll solvepar(ll cent1, ll cent2, vector<vll>& g){
    ll n = sz(g);

    vll d1(n);
    vll d2(n);

    function<void (ll, ll, ll, ll)> dfs = [&](ll u, ll p, ll h, ll t){
        if(t == 1) d1[h]++;
        if(t == 2) d2[h]++;

        for(ll v : g[u]){
            if(v == p) continue;
            dfs(v,u, h+1, t);
        }
    };

    dfs(cent1, cent2, 0, 1);
    dfs(cent2, cent1, 0, 2);

    ll resp = 0;
    forn(i,0,n) resp += d1[i]*d2[i];
    return resp;
}

int main() {
    _;
    ll n; cin >> n;
    vector<vll> g(n);
    forn(i,1,n){
        ll a, b; cin >> a >> b;
        a--, b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    vll sub(n);
    vll pai(n);
    vll h(n);

    function<void (ll, ll, ll)> dfs2 = [&](ll u, ll p, ll hl){
        pai[u] = p;
        h[u] = hl;
        ll resp = 1;
        for(ll v : g[u]){
            if(v == p) continue;
            dfs2(v,u, hl+1);
            resp += sub[v];
        }
        sub[u] = resp;
    };

    dfs2(0,-1, 0);

    
    function<ll (ll, ll)> getcent = [&](ll u, ll p){
        for(ll v : g[u]) if(v != p && sub[v] > n/2) return getcent(v,u);
        return u;    
    };
    
    ll cent = getcent(0,-1);
    ll cent2 = -1;

    for(ll u: g[cent]){
        bool ugood = true;
        for(ll v : g[u]){
            ll siz = sub[v];
            if(v == pai[u]) siz = n-sub[u];
            if(siz > n/2) ugood = false;
        } 
        if(ugood) cent2 = u;
    }
    ll gresp = 0;

    if(cent2 != -1) gresp += solvepar(cent, cent2, g);    

    dfs2(cent, -1,0);
    
    // devolve v, sendo v[i] quantos caras tem dist pra raiz (da sub) = i na subarvore, 
    function<map<ll,ll> (ll, ll)> dfs = [&](ll u, ll p){
        vector<tuple<ll,ll,map<ll,ll>>> vec;

        for(ll v : g[u]) if(v != p){
            vec.push_back({sub[v], v, dfs(v,u)});
        }
        
        sort(vec.begin(), vec.end());
        ll p1 = 0;
        ll p2 = 0;
        while(p2 <= sz(vec)){
            if(p2 < sz(vec)){
                auto& [sv1, v1, mp1] = vec[p1];
                auto& [sv2, v2, mp2] = vec[p2];
                
                if(sv1 == sv2){
                    p2++;
                    continue;
                }
            }
            
            if(p2-p1 == 1){
                p1 = p2;
                p2++;   
                continue;
            }

            // from p1 to p2-1 all sizes are equal
            map<ll, ll> sum;
            ll menos = 0;
            forn(i,p1, p2){
                auto& [sv, v, mp] = vec[i];
                for(auto [key, val] : mp){
                    sum[key] += val;
                    menos += val*val;
                }
            }
            ll lresp = 0;
            for(auto [key, val] : sum) lresp += val*val;
            lresp -= menos;
            lresp /= 2;
            gresp += lresp;

            p1 = p2;
            p2++;
        }

        if(sz(vec) == 0) vec.push_back({-1,-1, map<ll,ll>()});
        
        map<ll,ll>& mp = get<2>(vec.back());
        mp[h[u]]++;
        forn(i,0,sz(vec)-1){
            map<ll,ll>& mpv = get<2>(vec[i]);
            for(auto [k,val] : mpv) mp[k] += val;
        }

        return move(mp);
    };

    dfs(cent, -1);

    cout << gresp << ln;
    return 0;

}
