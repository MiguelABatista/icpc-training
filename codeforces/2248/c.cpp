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

void solve(){
    ll n; cin >> n;
    vll vec(2*n);
    forn(i,0,2*n){
        cin >> vec[i];
        vec[i]--;
    }

    vector<pll> pos(n, {-1,-1});

    forn(i,0,2*n){
        if(pos[vec[i]].first == -1) pos[vec[i]].first = i;
        else pos[vec[i]].second = i;
    }

    vll dp(2*n);

    dp[0] = 1;

    forn(i,1,2*n){
        dp[i] = dp[i-1] + 1;
        if(i == pos[vec[i]].first) continue;
        ll ant = pos[vec[i]].first;
        ll aux = (ant == 0 ? 0 : dp[ant-1]) + (i-ant + 1)*(i-ant + 1);
        dp[i] = max(dp[i], aux);
    }

    cout << dp[2*n-1] << ln;
    trace(cout << "----------------\n\n";)
}

int main() {
    _;
    ll t; cin >> t;
    forn(i,0,t){
        solve();
    }
    return 0;
}
