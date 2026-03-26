#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64;
typedef vector<ll> v64;

#define forn(i, s, e) for (ll i = s; i < (e); i++)
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

vector<v64> testa(ll t, ll h, ll w, vector<v64>& mat, map<ll, p64>& inv){

    p64 post = inv[t];
    vector<v64> dist(h, v64(w, INF));
    vector<v64> vis(h, v64(w, 0));
    dist[post.first][post.second] = 0;
    vis[post.first][post.second] = 1;
    
    forn(i,0,h*w){
        p64 prox = inv[i];        
        auto [x,y] = prox;
        ll curr = i;
        ll proxval = INF;
        stack<p64> st;
        
        if(vis[x][y]) continue;

        auto arruma = [&](p64 tenta){
            ll val = mat[tenta.first][tenta.second];

            if(abs(val - t) > abs(proxval - t)) return;
            if(abs(val - t) == abs(proxval - t)){
                if(abs(val - curr) > abs(proxval - curr)) return;
            }

            proxval = val;
            prox = tenta;
        };

        while (!vis[x][y]){       
            st.push({x,y});
            vis[x][y] = 1; 
            curr = mat[x][y];
            if(x > 0){
                p64 tenta = {x-1, y};
                arruma(tenta);
            }
            if(y > 0){
                p64 tenta = {x, y-1};
                arruma(tenta);
            }
            if(x < h-1){
                p64 tenta = {x+1, y};
                arruma(tenta);
            }
            if(y < w-1){
                p64 tenta = {x, y+1};
                arruma(tenta);
            }
            
            debug(proxval);     
            proxval = INF;
            x = prox.first;
            y = prox.second;
        };


        if(dist[x][y] == INF){
            while(!st.empty()) st.pop();
            continue;
        }

        ll d = dist[x][y];
        ll cnt = 1;

        while (!st.empty()){
            auto [xx, yy] = st.top();
            st.pop();
            dist[xx][yy] = d + cnt;
            cnt++;
        }
    }   

    debug(t);
    trace(
        forn(i,0,h){
            forn(j,0,w){
                cout << setw(2) << (dist[i][j] == INF ? 99 : dist[i][j]) << " ";
            }
            cout << ln;
        }
        cout << ln << ln;
    );
    return dist;
}


int main() {
    _;
    ll h, w; cin >> h >> w;
    vector<v64> mat(h, v64(w));
    map<ll, p64> inv;

    forn(i,0,h){
        forn(j,0,w){
            cin >> mat[i][j];
            mat[i][j]--;
            inv[mat[i][j]] = {i,j};
        }
    }

    ll bestval = INF;
    ll bestidx = -1;

    vector<v64> dp(h, v64(w, 0));

    forn(t,0,h*w){
        auto m = testa(t, h, w, mat, inv);

        forn(i,0,h){
            forn(j,0,w){
                dp[i][j] = max(dp[i][j], m[i][j]);
            }
        }
    }

    trace(
        forn(i,0,h){
            forn(j,0,w){
                cout << setw(2) << (dp[i][j] == INF ? 99 : dp[i][j]) << " ";
            }
            cout << ln;
        }
        cout << ln << ln;
    );

    forn(i,0,h){
        forn(j,0,w){
            if(dp[i][j] < bestval){
                bestval = dp[i][j];
                bestidx = mat[i][j];
            }
        }
    }

    if(bestval == INF){
        cout << "impossible" << ln;
        return 0;
    }
    
    cout << bestidx+1 << " " << bestval << ln;
    return 0;
}