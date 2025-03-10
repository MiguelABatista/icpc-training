#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64; 
typedef vector<ll> v64;

#define forn(i, s, e) for(ll i = (s); i < (e); i++)
#define ln "\n"

#if defined(DEBUG) || defined(debug)
    #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
    #define debug(x) cout << __LINE__ << ": " << #x << " = " << x << ln
#else
    #define _ (void)0
    #define debug(x) (void)0
#endif

const ll INF = 0x3f3f3f3f3f3f3f3fll;

// 700*700 ~~ 5 * 10^5

void solve(){
    ll n,m;
    cin >> n >> m;
    vector<v64> mat(n, v64(m));
    v64 colors(n*m, 0);

    forn(i,0,n){
        forn(j,0,m){
            cin >> mat[i][j];
            colors[mat[i][j]-1] = 1;
        }
    }

    forn(i,0,n){
        forn(j,0,m){
            bool found = false;
            ll curr_color = mat[i][j];
            if(i < n-1 && mat[i+1][j] == curr_color){
                found = true;
            }
            if(j < m-1 && mat[i][j+1] == curr_color){
                found = true;
            }
            if(i > 0 && mat[i-1][j] == curr_color){
                found = true;
            }
            if(j > 0 && mat[i][j-1] == curr_color){
                found = true;
            }
            if(found){
                colors[curr_color-1] = 2;
            }
        }
    }

    ll resp = 0;
    bool dois = false;
    for(auto c: colors){
        if(c == 2) dois = true;
        resp += c;
    }
    if(dois) resp -= 2;
    else resp -= 1;
    cout << resp << ln;
}   

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}