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

struct pt{
    ll s1 = -1, d1 = INF;
    ll s2 = -1, d2 = INF;
    bool att(ll se, ll de){
        if(se == s1 || se == s2) return false;
        if(de < d1){
            s2 = s1;
            d2 = d1;
            s1 = se;
            d1 = de;
            return true;
        }
        if(de < d2){
            s2 = se;
            d2 = de;
            return true;
        }
        return false;
    }
};


v64 bfs(vector<v64>& g, string& s, ll n){
    queue<p64> q;
    vector<ll> resp(n,INF);

    forn(i,0,n) if(s[i] == 'S'){
        q.emplace((p64){i, 0});
        resp[i] = 0;
    }

    while(!q.empty()){
        auto [v, d] = q.front();
        q.pop();
        for(ll u : g[v]) if(d+1 < resp[v]){
            resp[v] = d+1;
            q.emplace((p64){v,d+1});
        }
    }
    return resp;
}

vector<pt> bfs2(vector<v64>& g, string& s, ll n){
    queue<pair<ll,p64>> q;
    vector<pt> resp(n);

    forn(i,0,n) if(s[i] == 'S'){
        q.emplace((pair<ll,p64>){i, (p64){i,0}});
        resp[i].s1 = i;
        resp[i].d1 = 0;
    }

    while(!q.empty()){
        auto xxx = q.front();
        ll v = xxx.first;
        ll s = xxx.second.first;
        ll d = xxx.second.second;
        q.pop();

        for(ll u : g[v]){
            bool b = resp[u].att(s, d+1);
            if(b){
                q.emplace((pair<ll,p64>){u, (p64){s,d+1}});
            }                
        }
    }
    return resp;
}

int main(){
    _;
    ll n, m; cin >> n >> m;
    vector<v64> g(n);
    forn(i,0,m){
        ll a, b; cin >> a >> b;
        a--, b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    string s; cin >> s;

    auto resp = bfs2(g, s, n);

    forn(i,0,n) if(s[i] == 'D'){
        cout << resp[i].d1 + resp[i].d2 << ln; 
    }
    return 0;
}