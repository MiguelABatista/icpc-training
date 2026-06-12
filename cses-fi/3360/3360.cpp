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
const ll MAX = 7;
#define _
#else
#define trace(u)
const ll MAX = 3005;
#define _ ios::sync_with_stdio(0); cin.tie(0)
#endif
 
#define debug(u) trace(cout << #u " = " << u << ln)
#define debugv(v) trace(cout << #v ": "; for (auto xx : v) cout << xx << " "; cout << ln)
 
const ll INF = 0x3f3f3f3f3f3f3f3fll;
 
int main() {
    _;
    ll n, k; cin >> n >> k;

    vector<vll> mat(n, vll(n));
    vector<vector<vll>> vec(k, vector<vll>(n));

    forn(i,0,n){
        string s; cin >> s;
        forn(j,0,n){
            ll x = s[j]-'A';
            vec[x][i].push_back(j);
        }
    }

    forn(c,0,k){
        auto linha = vec[c];
        bool achou = false;
        
        vector<vector<bool>> vis(n, vector<bool>(n));
        forn(l,0,n){
            forn(i,0,sz(linha[l])){
                forn(j,i+1, sz(linha[l])){
                    ll xi = linha[l][i];
                    ll xj = linha[l][j];
                    if(vis[xi][xj]){
                        cout << "YES" << ln;
                        achou = true;
                        break;
                    }
                    vis[xi][xj] = true;
                }
                if(achou) break;
            }
            if(achou) break;
        }

        if(!achou) cout << "NO" << ln;
    }

    return 0;
}