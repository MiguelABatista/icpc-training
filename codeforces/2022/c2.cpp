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
    ll n; cin >> n;
    vector<v64> mat(2, v64(n));
    forn(i,0,2)forn(j,0,n){
        char c; cin >> c;
        mat[i][j] = (c=='A');
    }
    v64 dp(n);
    
    auto testa = [&](ll c){
        ll amt = 0;
        forn(i,0,3) amt += mat[0][c-i];
        forn(i,0,3) amt += mat[1][c-i];
        if(amt <= 1) return 0;
        if(amt >= 4) return 2;
        if(amt == 3) return 1;

        if(mat[0][c-2] == 1 && mat[1][c] == 1) return 0;
        if(mat[0][c] == 1 && mat[1][c-2] == 1) return 0;
        return 1;
    };

    forn(i,2,n){
        dp[i] = testa(i) + (i>= 3 ? dp[i-3] : 0);
    }
    cout << dp[n-1] << ln;
}

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}