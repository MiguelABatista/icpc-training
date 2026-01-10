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

ll match(string a, string b) {
    ll bst = 0;
    forn(i, 0, sz(a)) {
        forn(j, 0, sz(b)) {
            if (i+j >= sz(a)) {
                bst = max(bst, j);
                break;
            }
            if (a[i+j] != b[j]) break;
            if (j == sz(b) - 1) {
                return 0;
            }
        }
    }
    return sz(b) - bst;
}

int main(){
    _;
    ll h, w, n; cin >> h >> w >> n;
    vector<string> vs(n);
    forn(i, 0, n) {
        cin >> vs[i];
    }
    set<ll> rem;
    forn(i, 0, n) {
        forn (j, 0, n) {
            if (i == j) continue;
            if (!match(vs[i], vs[j])) rem.insert(j);
        }
    }
    vector<string> nvs;
    forn(i, 0, n) {
        if (!rem.count(i)) {
            nvs.push_back(vs[i]);
        }
    }
    n = sz(nvs);

    // vector<vector<p64>> g(n);
    vector<v64> g(n, v64(n));
    vector<ll> tam(n);
    forn(i, 0, n) {
        tam[i] = sz(nvs[i]);
        forn(j, 0, n) {
            if (i==j) continue;
            g[i][j] = match(nvs[i], nvs[j]);
        }
    }

    ll lim = 1<<n;
    vector<vector<p64>> dp_ini(lim, vector<p64>(n,{INF,-1}));
    // melhor fazer tal mask com tal ultimo cara

    forn(mask,0,lim){
        forn(i,0,n){
            ll pot = 1<<i; 
            if((pot&mask) == 0) continue;
            ll xor_mask = mask^pot;
            
            if(xor_mask == 0){
                dp_ini[i][mask] = {tam[i], i};
                continue;
            }
            
            forn(j,0,n){
                ll potj = 1<<j; 
                if((potj&xor_mask) == 0) continue;
                if(dp_ini[i][mask].first > dp_ini[j][xor_mask].first + g[j][i]){
                    dp_ini[i][mask].first = dp_ini[j][xor_mask].first+g[j][i];   
                    dp_ini[i][mask].second = j;
                }
            }
        }
    }

    vector<p64> dp(lim, {INF, -1});

    forn(mask,0,lim){
        forn(i,0,n){
            if(dp[mask].first > dp_ini[mask][i].first){
               dp[mask].first = min(dp[mask].first, dp_ini[mask][i].first); 
               dp[mask].second = i;
            }
            // dp[mask] = min(dp[mask], dp_ini[mask][i]);
        }
    }

    // mask da linha i
    v64 linhas(h, 0);

    forn(i,0,n){
        ll best = w;
        ll best_j = h;
        forn(j,0,h){
            ll mask = linhas[j];
            mask ^= (1<<i);
            if(dp[mask].first < best){
                best = dp[mask].first;
                best_j = j;
            }
        }
        if(best_j == h){
            cout << "impossible"  << ln;
            return 0;
        }
        linhas[best_j] ^= (1<<i);
    }

    forn(i,0,h){
        ll mask = linhas[i];
        v64 idxs;
        ll j = dp[mask].second;
        idxs.push_back(j);
        mask ^= (1<<j);

        while(mask > 0){
            j = dp_ini[mask][j].second;
            mask ^= (1<<j);
            idxs.push_back(j);
        }        
        reverse(idxs.begin(), idxs.end());

        string s = nvs[idxs[0]];
        forn(k,1,sz(idxs)){
            ll a = idxs[k-1];
            ll b = idxs[k];
            ll aux = g[a][b];
            for(ll x = tam[b]-aux; x < tam[b]; x++){
                s.push_back(nvs[b][x]);
            }
        }

        cout << s << ln;
    }
    // NVS = vector string4

    
    return 0;
}