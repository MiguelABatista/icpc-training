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

#define debug(u) trace(cout << #u " = " << u << ln)
#define debugv(v) trace(cout << #v ": "; for (auto xx : v) cout << xx << " "; cout << ln)
#define debugm(v) trace(cout << #v ": "; for (auto xx : v) cout << xx.first << ":" << xx.second << " "; cout << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;

int main() {
    _;
    ll n; cin >> n;
    vector<vector<char>> mat(n, vector<char>(n));
    
    forn(i,0,n){
        forn(j,0,n) cin >> mat[i][j];
    }

    vector<vector<p64>> prox(2);
    ll idx = 0;
    prox[0].push_back({0,0});
    string resp;
    resp.push_back(mat[0][0]);

    while(sz(prox[idx])){
        debug(idx);
        debugm(prox[idx]);
        prox[idx^1].clear();
        char c = 'Z'+1;
        
        for(auto [i,j]: prox[idx]){
            if(i+1 < n) c = min(c, mat[i+1][j]);
            if(j+1 < n) c = min(c, mat[i][j+1]);
        }
        debug(c);
        for(auto [i,j]: prox[idx]){
            if(i+1 < n && mat[i+1][j] == c){
                p64 p = {i+1,j};
                if(prox[idx^1].empty() || prox[idx^1].back() != p) prox[idx^1].push_back(p);
                
            } 
            if(j+1 < n && mat[i][j+1] == c){
                p64 p = {i,j+1};
                if(prox[idx^1].empty() || prox[idx^1].back() != p) prox[idx^1].push_back(p);
            }
        }

        if(c != 'Z'+1) resp.push_back(c);
        idx ^= 1;
        debug(idx);
        debugm(prox[idx]);
        trace(cout << ln << ln;); 
    }
    cout << resp << ln;
    return 0;
}
