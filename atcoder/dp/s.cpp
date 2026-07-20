#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
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
#define debugv(v) trace(cout << #v ": "; for (auto xx : v) cout << xx << " "; cout << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;
const ll MOD = 1'000'000'007;
const ll MAX = 100'005;
const ll MAXD = 101;

ll dp[MAX][2][MAXD]; 
// dp[i][less][rd] quantos pref de tamanho i tem resto rd que são ou não menores já 
string s;
ll d;
ll n;

ll solve(ll i, ll less, ll rd){
    if(dp[i][less][rd] != -1) return dp[i][less][rd];
    if(i == 0){
        if(less){
            ll ans = 0;
            forn(dig,0,s[0]-'0') ans += (dig%d == rd);
            return dp[i][less][rd] = ans;
        }
        else return dp[i][less][rd] = (rd == (s[0]-'0')%d);
    }

    if(less == 0){
        ll dig = s[i]-'0';
        return dp[i][less][rd] = solve(i-1, less, (rd-dig + d)%d);
    }

    ll ans = 0;
    
    forn(dig,0,10){
        if(dig < s[i]-'0') ans = (ans + solve(i-1, 0, (rd-dig+20*d)%d))%MOD;
        debug(((rd-dig+10*d)%d));
        ans = (ans + solve(i-1, 1, (rd-dig+20*d)%d))%MOD;    
    }
    return dp[i][less][rd] = ans;
}

int main() {
    _;
    memset(dp, -1, sizeof(dp));
    cin >> s;
    cin >> d;
    n = sz(s);
    
    ll ans = (solve(n-1,0,0) + solve(n-1, 1, 0) + MOD - 1)%MOD;
    trace(
        forn(i,0,n) forn(l,0,2) forn(rd,0,d){
            cout << i << " " << l << " " << rd << " " << dp[i][l][rd] << "\n";
        }
    )

    cout << ans << ln;
    return 0;
}
