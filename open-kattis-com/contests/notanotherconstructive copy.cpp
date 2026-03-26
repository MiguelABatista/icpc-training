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
    ll n, k; cin >> n >> k;
    string s; cin >> s;
    vector<set<pair<p64,ll>>> dp(n+1);
    dp[0].insert({{0,0},0});
    
    forn(i,1,n+1){
        if(s[i] == 'N'){
            for(auto& [p, nac]: dp[i-1]){
                auto& [n, na] = p;
                dp[i].insert({{n+1, na},nac});
            }
        }else if(s[i] == 'A'){
            for(auto& [p, nac]: dp[i-1]){
                auto& [n, na] = p;
                dp[i].insert({{n, na+n},nac});
            }
        }else if(s[i] == 'C'){
            for(auto& [p, nac]: dp[i-1]){
                auto& [n, na] = p;
                dp[i].insert({{n, na},nac+na});
            }
        }else if(s[i] == '?'){
            for(auto& [p, nac]: dp[i-1]){
                auto& [n, na] = p;
                dp[i].insert({{n+1, na},nac});
                dp[i].insert({{n, na+n},nac});
                dp[i].insert({{n, na},nac+na});
                dp[i].insert({{n, na},nac});
            }
        }else{
            for(auto& [p, nac]: dp[i-1]){
                auto& [n, na] = p;
                dp[i].insert({{n, na},nac});
            }
        }
    }

    ll resp = 0;
    for(auto& [p, nac]: dp[n]){
        resp = max(nac, resp);
    }

    cout << resp << ln;
    return 0;
}
