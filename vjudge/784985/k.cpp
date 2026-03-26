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

const ll INF = 0x3f3f3f3f3f3f3f3fll;

int main() {
    _;
    ll n; n = 500;
    vector<vector<bool>> mat(n, vector<bool>(n, false));
    
    forn(i,0,n){
        forn(j,0,n){

            forn(k,1,i+1){
                if(!mat[i-k][j]){
                    mat[i][j] = true;
                    break;
                }
            }
            if(mat[i][j]) continue;
            forn(k,1,j+1){
                if(!mat[i][j-k]){
                    mat[i][j] = true;
                    break;
                }
            }
            if(mat[i][j]) continue;
            forn(k,1,min(i,j)+1){
                if(!mat[i-k][j-k]){
                    mat[i][j] = true;
                    break;
                }
            }
        }
    }


    forn(i,0,n){
        forn(j,0,n) cout << (mat[i][j] ? ".," : "#,");; cout << ln;
    }
    return 0;
}
