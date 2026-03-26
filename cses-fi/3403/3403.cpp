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
    ll n, m; cin >> n >> m;
    v64 v1(n);
    v64 v2(m);
    forn(i,0,n) cin >> v1[i];
    forn(i,0,m) cin >> v2[i];

    vector<vector<p64>> dp(n, vector<p64>(m, {-1, -1})); 
    // valor, 0 = esq 1 = dir 2 = ambos

    dp[0][0] = {v1[0]==v2[0], -1};
    
    forn(i,1,n){
        dp[i][0].first = min(1ll, dp[i-1][0].first + (v1[i] == v2[0]));
        dp[i][0].second = 0;
    }
    forn(i,1,m){
        dp[0][i].first = min(1ll, dp[0][i-1].first + (v1[0] == v2[i]));
        dp[0][i].second = 1;
    }

    forn(i,1,n){
        forn(j,1,m){
            p64 resp = {dp[i-1][j].first, 0};
            if(resp.first < dp[i][j-1].first) resp = {dp[i][j-1].first, 1};
            if(v1[i] == v2[j]){
                if(resp.first < dp[i-1][j-1].first + 1) resp = {dp[i-1][j-1].first + 1, 1};
            }
            dp[i][j] = resp;
        }
    }
    cout << dp[n-1][m-1].first << ln;
    v64 resp;
    ll x = n-1;
    ll y = m-1;
    while(x > 0 || y > 0){
        ll nx = x;
        ll ny = y;
        if(dp[x][y].second == 0 || dp[x][y].second == 2) nx--;
        if(dp[x][y].second == 1 || dp[x][y].second == 2) ny--;
        if(dp[x][y].first > dp[nx][ny].first){
            assert(v1[x] == v2[y]);
            resp.push_back(v1[x]);
        }
        x = nx;
        y = ny;
    }
    if(v1[0] == v2[0]) resp.push_back(v1[0]);
    reverse(resp.begin(), resp.end());
    forn(i,0,sz(resp)) cout << resp[i] << " \n"[i==sz(resp)-1];
    return 0;
}
