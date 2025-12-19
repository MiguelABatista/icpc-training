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


void solve(){
    ll n, m, k; cin >> n >> m >> k;

    vector<v64> mat(n, v64(m, 0));

    auto decomp = [&](ll x){
        return (p64){x/m, x%m};
    };

    forn(idx, 0, m*n){
        auto [a,b] = decomp(idx);
        mat[a][b] = idx%k + 1;
    }

    trace(
        cout << ln << ln;
        cout << n << " " << m << " " << k << ln;
        forn(i,0,n){
            forn(j,0,m) cout << mat[i][j] << " ";; cout << ln;
        }
        cout << ln;
    );

    if(m%k == 0){
        forn(i,0,n) if((i&1)){
            ll ini = mat[i][0];
            forn(j,0,m-1) mat[i][j] = mat[i][j+1];
            mat[i][m-1] = ini;
        }
    }   
    forn(i,0,n){
        forn(j,0,m) cout << mat[i][j] << " ";; cout << ln;
    } 
    
}

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}