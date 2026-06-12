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

int main() {
    _;
    ifstream cin("feast.in");
    ofstream cout("feast.out");
    ll t, a, b; cin >> t >> a >> b;

    vll dp(t+1, 0);
    dp[0] = 1;

    forn(i,0,t+1){
        if(dp[i]){
            if(i+a <= t) dp[i+a] = 1;
            if(i+b <= t) dp[i+b] = 1;
        }
    }

    vll agua(t+1);

    forn(i,0,t+1){
        if(dp[i]) agua[i/2] = 1;
    }
    forn(i,0,t+1){
        if(agua[i]){
            if(i+a <= t) agua[i+a] = 1;
            if(i+b <= t) agua[i+b] = 1;
        }
    }

    ll resp = 0;
    forn(i,0,t+1) if(agua[i]) resp = i;

    cout << resp << ln;

    
    return 0;
}
