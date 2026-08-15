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
#define debugm(v) trace(cout << #v ": "; for (auto xx : v) cout << xx.first << ":" << xx.second << " "; cout << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;

void solve(){
    // ll n; cin >> n;
    ll n = 100;
    vector<pll> resp;
    vector<ll> resp2(n+1);
    forn(x,2,n+1){
        forn(k,1,x){
            if(x + 2*k > n) break;
            if((((x)^(x+k))^(x+2*k)) == 0){
                resp.push_back({x,k});
                resp2[x+2*k]++;
            }
        }
    }

    for(auto [x,k] : resp){
        cout << bitset<6>(x) << " " << bitset<6>(k) << " : " << bitset<6>(x^k) << " " << x << " " << k << ln;
    }

    cout << sz(resp) << ln;
    debugv(resp2);
    // forn(i,0,n+1) if(resp2[i] > 0) cout << i << " " << resp2[i] << ln;
}

int main() {
    _;
    solve();
    return 0;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}
