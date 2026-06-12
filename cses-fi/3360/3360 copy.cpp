#include <bits/stdc++.h>
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("popcnt")
 
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
    ll n; cin >> n;

    vector<vll> mat(n, vll(n));
    forn(i,0,n){
        string s; cin >> s;
        forn(j,0,n){
            mat[i][j] = s[j]-'A';
        }
    }
    
    vector<vector<vll>> next_dir(26 , vector<vll>(n, vll(n,-1)));
    vector<vector<vll>> next_bai(26 , vector<vll>(n, vll(n,-1)));
    
    for(ll i = n-1; i >= 0; i--){
        for(ll j = n-1; j >= 0; j--){
            if(i < n-1){
                forn(c,0,26){
                    if(mat[i+1][j] == c) next_dir[c][i][j] = i+1;
                    else  next_dir[c][i][j] = next_dir[c][i+1][j];
                }
            }
            if(j < n-1){
                forn(c,0,26){
                    if(mat[i][j+1] == c) next_dir[c][i][j] = j+1;
                    else  next_dir[c][i][j] = next_dir[c][i][j+1];
                }
            }
        }
    }

    forn(c,0,26){
        
    }

    return 0;
}