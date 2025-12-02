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
const ll MOD = 1'000'000'007;
const ll MAXN = 505;

ll fat[MAXN];
ll invfat[MAXN];
ll invmod[MAXN];

void prep(){
    fat[0] = fat[1] = 1;
    invfat[0] = invfat[1] = 1;
    invmod[1] = 1;
    forn(i,2,MAXN){
        fat[i] = (i*fat[i-1])%MOD;
        ll a = MOD/i;
        ll b = MOD%i;
        invmod[i] = MOD - (a*invmod[b])%MOD;
        invfat[i] = (invmod[i]*invfat[i-1])%MOD;
    }  
}

ll choose(ll a, ll b){
    return (fat[a]* ((invfat[b]*invfat[b-a])%MOD))%MOD;
}

int main(){
    _;
    prep();
    string s; cin >> s;
    ll n = sz(s);

    vector<v64> dp(n,v64(n, 0));

    forn(i,0,n-1) if(s[i] == s[i+1]) dp[i][i+1] = 1;
    
    forn(t,1,n) if(t%2){
        forn(i,0,n-t){
            ll j = i+t;

            if(s[i] == s[i+1]){
                dp[i][j] = (dp[i][j] + choose(t-2+1, 1))%MOD;
            }

            forn(x,i+2,j) if(s[i] == s[x]){
                dp[i][j] = (dp[i][j] + (dp[i+1][x-1]*dp[x+1][j])%MOD )%MOD;
            }

            if(s[i] == s[j]){
                dp[i][j] =(dp[i][j] + dp[i+1][j-1])%MOD;
            }
        }
    }

    forn(i,0,n) debugv(dp[i]);
    cout << dp[0][n-1] << ln;
    return 0;
}