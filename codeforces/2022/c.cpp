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
    ll m = n/3;
    vector<v64> mat(2, v64(n+1));
    forn(i,0,2)forn(j,1,n+1){
        char c; cin >> c;
        mat[i][j] = (c=='A');
    }

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

    v64 dp1(m+1);
    // #
    // ##
    v64 dp2(m+1);
    // ##
    // #
    v64 dp3(m+1);
    // ##
    // ##

    dp1[1] = (mat[0][1] + mat[1][1] + mat[1][2] >= 2); 
    dp2[1] = (mat[0][1] + mat[1][1] + mat[0][2] >= 2); 
    dp3[1] = testa(3);

    auto linha = [&](ll c, ll l){
        return (ll)(mat[l][c]+mat[l][c-1]+mat[l][c-2] >= 2);
    };

    forn(i,2,m+1){
        dp1[i] = max(
            dp1[i-1] + linha(3*(i-1)+1, 0) + linha(3*(i-1)+2, 1),
            dp3[i-1] + (mat[0][3*(i-1)+1] + mat[1][3*(i-1)+1] + mat[1][3*(i-1)+2] >= 2)
        );
        dp2[i] = max(
            dp2[i-1] + linha(3*(i-1)+2, 0) + linha(3*(i-1)+1, 1),
            dp3[i-1] + (mat[0][3*(i-1)+1] + mat[1][3*(i-1)+1] + mat[0][3*(i-1)+2] >= 2)
        );
        
        dp3[i] = dp3[i-1] + testa(3*i);
        dp3[i] = max(dp3[i], 
            dp1[i] + (mat[0][3*i-1] + mat[0][3*i] + mat[1][3*i] >= 2)
        );
        dp3[i] = max(dp3[i], 
            dp2[i] + (mat[1][3*i-1] + mat[0][3*i] + mat[1][3*i] >= 2)
        );       
    }

    debugv(mat[0]);
    debugv(mat[1]);
    debugv(dp1);
    debugv(dp2);
    debugv(dp3);
    cout << dp3[m] << ln;
    trace(cout << "------------\n\n";);
}

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}