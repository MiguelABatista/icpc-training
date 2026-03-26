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

ll rec(ll curr, ll qnt, ll tight, string& num, vector<vector<v64>>& dp){
    if(curr == sz(num)) return 1;

    if(dp[curr][qnt][tight] != -1) dp[curr][qnt][tight];
    ll lim;
    if(!tight) lim = 9;
    else lim = num[curr]-'0';

    ll ans = 0;
    forn(cd, 0, lim+1){
        ll nqnt = qnt;
        ll ntight = tight;
        
        if(cd != 0) nqnt++;
        if(nqnt > 3) continue;
        if(tight && (cd == lim)) ntight = true;
        else ntight = false;

        ans += rec(curr+1, nqnt, ntight, num, dp);
    }

    dp[curr][qnt][tight] = ans;
    return ans;
}

ll calc(ll n){
    vector<vector<v64>> dp(20, vector<v64>(4, v64(2, -1)));
    string s = to_string(n);
    return rec(0,0,1,s, dp);
}

void solve(){
    ll l, r; cin >> l >> r;
    cout << calc(r) - calc(l-1) << ln;
}
int main() {
    _;

    ll t; cin >> t;
    while(t--) solve();

    return 0;
}
