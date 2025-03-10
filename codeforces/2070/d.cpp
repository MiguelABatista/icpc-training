#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64; 
typedef vector<ll> v64;

#define forn(i, s, e) for(ll i = (s); i < (e); i++)
#define ln "\n"

#if defined(DEBUG) || defined(debug)
    #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
    #define debug(x) cout << __LINE__ << ": " << #x << " = " << x << ln
#else
    #define _ (void)0
    #define debug(x) (void)0
#endif

const ll INF = 0x3f3f3f3f3f3f3f3fll;

#define MOD 998'244'353

ll mult(ll a, ll b){
    return ((a%MOD)*(b%MOD))%MOD;
}

ll sum(ll a, ll b){
    return ((a%MOD)+(b%MOD))%MOD;
}

ll sub(ll a, ll b){
    return ((a%MOD) - (b%MOD) + MOD)%MOD;
}

ll pot(ll a, ll b){
    ll expo=1, prod=a;
    b = b % (MOD-1);
    a = a % MOD;

    while(b>=1){
        if(b%2 == 1) expo = mult(expo,prod);
        prod = mult(prod,prod);
        b = b/2;
    }
    
    return expo;
}

ll inv_mod(ll a){
    return pot(a, MOD-2);
}

ll bfs(vector<v64> &g) {
    ll n = g.size();
    v64 prof(n, 0);
    v64 seq_prof(n,0);
    v64 seq_ver(n,0);
    
    seq_ver[0] = 1;
    seq_prof[0] = 1;
    queue<ll> q;

    q.push(0);
    prof[0] = 0;

    while (!q.empty()) {
        ll u = q.front();
        q.pop(); 

        for (ll v : g[u]) {
            prof[v] = prof[u] + 1;
            q.push(v);
            if(prof[u] == 0){
                seq_ver[v] = seq_prof[prof[u]];
                seq_prof[prof[v]] = sum(seq_prof[prof[v]], seq_ver[v]);
            }else{
                seq_ver[v] = sub(seq_prof[prof[u]], seq_ver[u]);
                seq_prof[prof[v]] = sum(seq_prof[prof[v]], seq_ver[v]);
            }
        }
    }

    ll resp = 0;

    forn(i,0,n){
        resp = sum(resp, seq_prof[i]); 
    }

    return resp;
}


void solve(){
    ll n; cin >> n;
    v64 parent(n);
    v64 prof(n, -1);
    vector<v64> g(n);
    prof[0] = 0; 
    parent[0] = 0;
    
    forn(i,1,n){
        ll pai_i;
        cin >> pai_i;
        pai_i--;
        parent[i] = pai_i;
        g[pai_i].push_back(i);
    }
    
    ll resp = bfs(g);

    cout << resp << ln;
}


int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}