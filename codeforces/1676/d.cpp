#include <bits/stdc++.h> 

using namespace std;

typedef long long ll;

#define forn(i, s, e) for (ll i = (s); i < (e); i++)

void solve(){
    ll n, m; cin >> n >> m;

    vector<vector<ll>> mat(n, vector<ll>(m,0));
    forn(i,0,n){
        forn(j,0,m){
            cin >> mat[i][j]; 
        }
    }

    ll best  = 0;

    forn(i,0,n){
        forn(j,0,m){
            // calcula a pontuacao do bispo
            ll curr = mat[i][j];

            ll x = j-1, y = i-1 ;
            while (x >= 0 && y >= 0) {
                curr += mat[y][x];
                y--;
                x--;
            }
            x = j+1, y = i+1 ;
            while (x < m && y < n) {
                curr += mat[y][x];
                y++;
                x++;
            }
            x = j+1, y = i-1 ;
            while (x < m && y >= 0) {
                curr += mat[y][x];
                y--;
                x++;
            }

            x = j-1, y = i+1 ;
            while (x >= 0 && y < n) {
                curr += mat[y][x];
                y++;
                x--;
            }

            best = max(curr, best);
        }
    }
    cout << best << "\n";
}

int main() {
    ll t; cin >> t;

    forn(i,0,t) solve();

    return 0;
}
