#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pll;
typedef vector<ll> vll;

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
#define debugv(v) trace(cout << #v ": "; for (auto xx : v) cout << fixed << setprecision(3) << xx << " "; cout << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;



int main() {
    _;
    ll n; cin >> n;
    ll aa = 0;
    ll bb = 0;
    ll cc = 0;
    forn(i,0,n){
        ll x; cin >> x;
        if(x == 1) aa++;
        if(x == 2) bb++;
        if(x == 3) cc++;
    }

    vector<vector<vector<ld>>> dp(n+1,vector<vector<ld>>(n+1, vector<ld>(n+1)));
    // dp[c][b][a] valor esperado para a pratos com 1 b pratos com 2 c pratos com 3
    // dp[c][b][a] = 1 + (1 - (a+b+c)/n)*dp[c][b][a] + a/n*dp[c][b][a-1] + b/n*dp[c][b-1][a+1] + c/n*dp[c-1][b+1][a];
    // (a+b+c)/n)dp[c][b][a] = 1 + a/n*dp[c][b][a-1] + b/n*dp[c][b-1][a+1] + c/n*dp[c-1][b+1][a];
    // dp[c][b][a] = n/(a+b+c) + a/(a+b+c)*dp[c][b][a-1] + b/(a+b+c)*dp[c][b-1][a+1] + c/(a+b+c)*dp[c-1][b+1][a];

    forn(c,0,n+1){
        forn(b,0,n+1){
            forn(a,0,n+1){
                ld resp = 0;
                if(a+b+c > n) continue;
                if(a+b+c > 0) resp += (ld(n)/ld(a+b+c));
                if(a > 0) resp += (ld(a)/ld(a+b+c))*dp[c  ][b  ][a-1];
                if(b > 0) resp += (ld(b)/ld(a+b+c))*dp[c  ][b-1][a+1];
                if(c > 0) resp += (ld(c)/ld(a+b+c))*dp[c-1][b+1][a  ];
                dp[c][b][a] = resp;
            }
        }
    }

    cout << fixed << setprecision(14) << dp[cc][bb][aa] << ln;
    return 0;
}
