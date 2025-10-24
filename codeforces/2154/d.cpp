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
#define debugm(v) trace({cout << #v": "; for (auto x : v) cout<< x.first << ":" << x.second << " "; cout << ln;})
#define debug(x) trace(cout << __LINE__ << ": " #x " = " << x << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;

void solve(){
    ll n; cin >> n;
    vector<v64> tree(n);
    forn(i,1,n){
        ll a, b; cin >> a >> b;
        a--; b--;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }

    set<p64> s; // profundidade, idx
    
    ll gato = -1;
    function<void (ll, ll, ll)> dfs = [&](ll u, ll p, ll h) {
        s.insert({h,u});
        if(u == 0){
            gato = h%2;
        }

        for(ll v : tree[u]) if(v != p){
            dfs(v,u,h+1);
        }
        return; 
    };
    
    dfs(n-1,-1,0);
    vector<p64> op;
    while(!s.empty()){
        auto it = prev(s.end()); 
        p64 bottom = *it;
        s.erase(it); 
        if(bottom.first == 0) break;
        if(bottom.first % 2 == gato){
            op.push_back({1,0});
            gato ^= 1;
        }
        op.push_back({2, bottom.second+1});
        op.push_back({1,0});
        gato ^= 1;
    }
    cout << op.size() << ln;
    for(p64 p: op){
        if(p.first == 1) cout << 1 << ln;
        else cout << 2 << " " << p.second << ln;
    }
}

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}