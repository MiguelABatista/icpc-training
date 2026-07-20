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
const ll MAX = 70;
const ll INF = 999;
#define _
#else
#define trace(u)
#define _ ios::sync_with_stdio(0); cin.tie(0)
const ll MAX = 10'005;
const ll INF = 0x3f3f3f3f3f3f3f3fll;
#endif

#define debug(u) trace(cout << __LINE__ << ": " #u " = " << u << ln)
#define debugv(v) trace(cout << #v ": "; for (auto xx : v) cout << setw(4) <<  xx << " "; cout << ln)


int main() {
    _;
    ll n; cin >> n;
    vector<pll> vec(n);
    forn(i,0,n) cin >> vec[i].second >> vec[i].first;

    sort(vec.rbegin(), vec.rend());

    vector<vll> dp(n, vll(MAX, INF));
    
    dp[0][vec[0].second] = vec[0].second*vec[0].first;

    forn(h,1,n){
        debug(h);
        auto [t,f] = vec[h];

        auto getval = [&](ll a){
            // debug(a); 
            return dp[h-1][a] - t*(a/2);
        };

        // dp[h][x] = min j in (x-f x+f só com msm paridade) dp[h-1][j]
        // vamos fazer uma slid window        
        auto run = [&]( ll x0){
            debug(1);
            multiset<ll> s;
            ll  l = llabs(f-x0), r = f + x0;
            for(ll i = l; i <= r; i += 2) if(i >= 0) s.insert(getval(i));
            
            for(ll x = x0; x < MAX; x += 2){
                if(!s.empty()) dp[h][x] = *s.begin() + t*((x+f)/2);
                if(dp[h][x] > INF/2) dp[h][x] = INF;
                r += 2;
                if(r < MAX) s.insert(getval(r));
                ll newl = llabs(f-(x+2));

                debug(l);
                debug(r);
                debug(newl);
                debug((s.find(getval(l)) == s.end()));
                if(newl < l) s.insert(getval(newl));
                else if(newl > l) s.erase(s.find(getval(l)));
                l = newl;
                // trace(
                //     cout << x << ": " << dp[h][x] << ln;
                //     debugv(s);
                //     cout << ln;
                // )
            }
        };

        run(0);
        run(1);
    }

    trace(  
        cout << "     :";
        forn(i,0,MAX) cout << setw(4) << i%10 << " ";; cout << ln;
        forn(i,0,n){debugv(dp[i]);}
    )

    ll resp = INF;
    forn(i,0,MAX) resp = min(resp, dp[n-1][i]);
    cout << resp << ln;
    return 0;
}
