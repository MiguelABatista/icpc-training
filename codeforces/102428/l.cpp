#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64; 
typedef vector<ll> v64;

#define forn(i, s, e) for(ll i = (s); i < (e); i++)
#define ln "\n"

#if defined(DEBUG)
    #define _ (void)0
    #define debug(x) cout << __LINE__ << ": " << #x << " = " << x << ln
#else
    #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
    #define debug(x) (void)0
#endif

const ll INF = 0x3f3f3f3f3f3f3f3fll;

ll n, m;
vector<string> mat;
vector<v64> dp;

bool testa(ll l){
    debug(l);
    vector<multiset<ll>> minv(m-l+1);

    forn(i,0,l){
        forn(j,0,m-l+1){
            minv[j].insert(dp[i][j]);
        }
    }

    forn(i,0,n-l+1){
        forn(j,0,m-l+1){
            if(*minv[j].begin() >= l) return true;
        }

        if(i == n-l) break;

        forn(j,0,m-l+1){
            minv[j].erase(minv[j].find(dp[i][j]));
            minv[j].insert(dp[i+l][j]);
        }
    }
    return false;
}

int main(){
    _;
    cin >> n >> m;

    mat.resize(n);
    forn(i,0,n) cin >> mat[i];

    dp.resize(n, v64(m,-1));

    forn(i,0,n){
        dp[i][m-1] = 1;
        for(ll j = m-2.; j >=0; j--){
            if(mat[i][j] == mat[i][j+1]) dp[i][j] = dp[i][j+1]+1;
            else dp[i][j] = 1;
        }
    }

    // forn(i,0,n) forn(j,0,m) cout << mat[i][j] << " \n"[j==m-1];
    
    // forn(i,0,n) forn(j,0,m) cout << dp[i][j] << " \n"[j==m-1];
        
    
    forn(i,0,n) cin >> mat[i];

    ll l = 1;
    ll r = min(n,m);
    ll mid = (l+r)/2;
    ll ans = l;

    while(l <= r){
        if(testa(mid)){
            ans = mid;
            l = mid+1;
        }else{
            r = mid-1;
        }
        mid = (l+r)/2;
    }

    cout << ans*ans << ln;
    return 0;
}