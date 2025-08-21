    #include <bits/stdc++.h>
    using namespace std;

    typedef long long ll;
    typedef pair<ll, ll> p64; 
    typedef vector<ll> v64;

    #define forn(i, s, e) for(ll i = (s); i < (e); i++)
    #define ln "\n"

    #if defined(DEBUG)
        #define _ (void)0
        #define debug(x) cout << __LINE__ << ": " << #x << " = " << x << ln
        #define debug(x) cout << __LINE__ << ": " << #x << " = " << x << ln
    #else
        #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
        #define debug(x) (void)0
    #endif

    const ll INF = 0x3f3f3f3f3f3f3f3fll;
    const ll MAX = 100'010;
    const ll MAXLOG = 20;

    vector<v64> g(MAX);
    vector<v64> g2(MAX);

    ll n, p, r;
    ll pai[MAXLOG][MAX];
    ll in[MAX], out[MAX], h[MAX];

    void dfs(ll k, ll alt) {
        h[k] = alt;
        in[k] = p++;
        for (ll i = 0; i < (ll) g[k].size(); i++)
            if (in[g[k][i]] == -1) {
                pai[0][g[k][i]] = k;
                dfs(g[k][i], alt+1);
            }
        out[k] = p++;
    }

    void build(ll raiz) {
        for (ll i = 0; i < n; i++) pai[0][i] = i;
        p = 0, memset(in, -1, sizeof in);
        dfs(raiz, 0);

        // pd dos pais
        for (ll k = 1; k < MAXLOG
    ; k++) for (ll i = 0; i < n; i++)
            pai[k][i] = pai[k - 1][pai[k - 1][i]];
    }

    bool anc(ll a, ll b) { // se a eh ancestral de b
        return in[a] <= in[b] and out[a] >= out[b];
    }

    ll lca(ll a, ll b) {
        if (anc(a, b)) return a;
        if (anc(b, a)) return b;

        // sobe a
        for (ll k = MAXLOG
    - 1; k >= 0; k--)
            if (!anc(pai[k][a], b)) a = pai[k][a];

        return pai[0][a];
    }

    ll dist(ll a, ll b){
        return h[a]+h[b]-2*h[lca(a,b)];
    }

    vector<v64> dp(2, v64(MAX, -1));

    void dfs2(ll u, ll pa){
        ll ans_dentro = 1;
        ll ans_fora = 0;

        for(ll v: g2[u]){
            if(v == pa) continue;
            dfs2(v, u);
            ans_dentro += min(dp[0][v], dp[1][v]);
            ans_fora += dp[1][v];
        }

        dp[0][u] = ans_fora;
        dp[1][u] = ans_dentro;
    }

    int main(){
        _;
        cin >> n >> r;
        vector<p64> rats(r);
        set<ll> solitarios;
        set<ll> surfistas;

        forn(i,0,n-1){
            ll a, b;
            cin >> a >> b;
            g[a].push_back(b);
            g[b].push_back(a);
        }

        build(0);
        
        while(r--){
            ll a, b;
            cin >> a >> b;
            ll lc = lca(a,b);
            ll da = dist(lc, a);
            ll db = dist(lc, b);

            if(da < db) swap(a,b), swap(da,db);
            ll d = (da+db)/2;
            ll pa = a;
            for(ll k = MAXLOG-1; k >= 0; k--){
                // debug(pa);
                // debug(pai[k][pa]);
                // debug(h[a] - d);
                // debug(h[a]);
                // debug(d);
                // debug(h[pai[k][pa]]);
                
                if(h[pai[k][pa]] >= h[a] - d) pa = pai[k][pa];
            }
            if((da + db) % 2 == 0){
                solitarios.insert(pa);
            }else{
                surfistas.insert(pa);
            }
        }

        ll ans = (ll)solitarios.size();

        v64 deg(n);
        v64 state(n, -1);
        
        for(ll suf: surfistas){
            if(solitarios.count(suf)) continue;
            if(solitarios.count(pai[0][suf])) continue;
    
            deg[suf]++;
            deg[pai[0][suf]]++;

            g2[suf].push_back(pai[0][suf]);
            g2[pai[0][suf]].push_back(suf);
        }

        forn(i,0,n){
            if(dp[0][i] != -1) continue; 
            dfs2(i,-1);
            ans += min(dp[0][i], dp[1][i]);
        }

        // forn(i,0,n) cout << i%10 << " ";; cout << ln;
        // forn(i,0,n) cout << dp[0][i] << " ";; cout << ln;
        // forn(i,0,n) cout << dp[1][i] << " ";; cout << ln;
        cout << ans << ln; 
        return 0;  
    }
