#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64;
typedef vector<ll> v64;

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

#define debug(u) trace(cout << __LINE__ << ": " << #u " = " << u << ln)
#define debugv(v) trace(cout << __LINE__ << ": " << #v ": "; for (auto xx : v) cout << xx << " "; cout << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;
const ll LOG = 33;


int main() {
    _;
    
    ll n, q; cin >> n >> q;
    vector<v64> nxt(LOG, v64(n));
    vector<v64> g(n);
    forn(i,0,n){
        cin >> nxt[0][i];
        nxt[0][i]--;
        g[nxt[0][i]].push_back(i);
    }

    forn(j,1,LOG){
        forn(i,0,n){
            nxt[j][i] = nxt[j-1][nxt[j-1][i]]; 
        }
    }

    // auto anda = [&](ll x, ll k){
    //     ll j = 0;
    //     while(k){
    //         if(k&1) x = nxt[j][x];
    //         k >>= 1;j++;
    //     }
    //     return x;
    // };

    v64 cic(n, -1);
    v64 prof(n, -1);
    v64 vis(n, 0);

    ll nxt_cic = 0;
    
    vector<ll> st;
    forn(i,0,n){
        if(vis[i] == 1) continue;
        ll x = i;

        while(vis[x] != 0){
            vis[x] = -1;
            st.push_back(x);
            x = nxt[0][x];
        }

        if(vis[x] == -1){
            ll ini = x;
            x = nxt[0][x];        
            while(!st.empty() && x != ini){
                cic[x] = nxt_cic;
                vis[x] = 1;
                prof[x] = 0;
                prof[x] = 0;
                x = st.back();
                st.pop_back();                
            }
            cic[x] = nxt_cic;
            vis[x] = 1;
            x = st.back();
            st.pop_back();                
            
            nxt_cic++;
        }
        ll dep = prof[x]+1;
        ll curr_cir = cic[x];
        while(!st.empty()){
            x = st.back();
            st.pop_back();
            prof[x] = dep++;
            cic[x] = curr_cir;
            vis[x] = 1;
        }
    }    
    
    debugv(cic);
    debugv(prof);
    debugv(vis);
    return 0;
}
