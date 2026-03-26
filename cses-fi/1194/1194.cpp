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

void solve(ll i, ll j, vector<vector<char>>& mat){
    string s;
    debug(i);
    debug(j);
    trace(forn(ii,0,sz(mat)){debugv(mat[ii]);});

    while(mat[i][j] != 'S'){
        s.push_back(mat[i][j]);
        if(mat[i][j] == 'U'){
            i++;
            continue;
        }
        if(mat[i][j] == 'D'){
            i--;
            continue;
        } 
        if(mat[i][j] == 'L'){
            j++;
            continue;
        }
        if(mat[i][j] == 'R'){
            j--;
            continue;
        }
    }
    reverse(s.begin(), s.end());
    cout << "YES" << ln;
    cout << sz(s) << ln;
    cout << s << ln;
}

int main() {
    _;
    ll n, m; cin >> n >> m;

    vector<string> mat(n, string(m, '.'));
    vector<v64> valid(n, v64(m, 1));
    vector<vector<char>> path(n, vector<char>(m, '.'));

    forn(i,0,n){ 
        forn(j,0,m){
            cin >> mat[i][j];
        }
    }


    vector<vector<p64>> mostros(2);
    vector<vector<p64>> vc(2);

    forn(i,0,n){
        forn(j,0,m){
            if(mat[i][j] == 'M'){
                valid[i][j] = 0;
                mostros[0].push_back({i,j});
            }
            if(mat[i][j] == 'A'){
                vc[0].push_back({i,j});
            }
            if(mat[i][j] == '#'){
                valid[i][j] = 0;
            }
        }
    }

    trace(forn(i,0,n){debugv(mat[i]);});
    trace(forn(i,0,n){debugv(valid[i]);});

    auto [a,b] = vc[0][0];
    path[a][b] = 'S';
    if(a == n-1 || a == 0 || b == m-1 || b == 0){
        cout << "YES" << ln;
        cout << 0 << ln;
        return 0;
    }
    ll k = 0;

    while(sz(vc[k])){
        debugm(vc[k]);
        mostros[k^1].clear();
        vc[k^1].clear();
        for(auto [i,j] : mostros[k]){
            if(i > 0 && valid[i-1][j]){
                mostros[k^1].push_back({i-1, j});
                valid[i-1][j] = 0;
            }
            if(j > 0 && valid[i][j-1]){
                mostros[k^1].push_back({i, j-1});
                valid[i][j-1] = 0;                
            }
            if(i < n-1 && valid[i+1][j]){
                mostros[k^1].push_back({i+1, j});
                valid[i+1][j] = 0;                
            }
            if(j < m-1 && valid[i][j+1]){
                mostros[k^1].push_back({i, j+1});
                valid[i][j+1] = 0;                
            }
        }
        trace(forn(i,0,n){debugv(valid[i]);});

        for(auto [i,j] : vc[k]){
            if(i > 0 && valid[i-1][j] && path[i-1][j] == '.'){
                vc[k^1].push_back({i-1, j});
                path[i-1][j] = 'U';
                if(i-1 == 0){
                    solve(i-1, j, path);
                    return 0;
                }
            }
            if(j > 0 && valid[i][j-1] && path[i][j-1] == '.'){
                vc[k^1].push_back({i, j-1});
                path[i][j-1] = 'L';   
                if(j-1 == 0){
                    solve(i, j-1, path);
                    return 0;
                }             
            }
            if(i < n-1 && valid[i+1][j] && path[i+1][j] == '.'){
                vc[k^1].push_back({i+1, j});
                path[i+1][j] = 'D';       
                if(i+1 == n-1){
                    solve(i+1, j, path);
                    return 0;
                }         
            }
            if(j < m-1 && valid[i][j+1] && path[i][j+1] == '.'){
                vc[k^1].push_back({i, j+1});
                path[i][j+1] = 'R';  
                if(j+1 == m-1){
                    solve(i, j+1, path);
                    return 0;
                }              
            }
        }
        k ^= 1;
    }
    trace(forn(i,0,n){debugv(valid[i]);});
    trace(forn(i,0,n){debugv(path[i]);});

    cout << "NO" << ln;
    return 0;
}
