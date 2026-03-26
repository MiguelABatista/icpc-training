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

ll rec(ll falta, ll td, ll curr, ll tight, string& num, vector<vector<v64>>& dp){
    if(curr == sz(num)) return 1;

    if(dp[curr][falta][tight] != -1) dp[curr][falta][tight];
    ll lim;
    if(!tight) lim = 9;
    else lim = num[curr]-'0';

    ll ans = 0;
    forn(cd, 0, lim+1){
        ll nfalta = falta;
        ll ntight = tight;
        
        
        if(tight && (cd == lim)) ntight = true;
        else ntight = false;

        ans += rec(curr+1, nfalta, ntight, num, dp);
    }

    dp[curr][qnt][tight] = ans;
    return ans;
}



int main() {
    _;
    string s; cin >> s;

    vector<vector<v64>> dp(20, vector<v64>(4, v64(2, -1)));
    cout << rec(0,0,1,s, dp) << ln;


    return 0;
}
