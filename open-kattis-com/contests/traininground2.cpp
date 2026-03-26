#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64;
typedef vector<ll> v64;

#define forn(i, s, e) for (ll i = s; i < (e); i++)
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
    ll n, i, t; cin >> n >> i >> t;
    set<p64> s;
    vector<v64> proib(n+1, v64(n+1, 0));
    s.emplace(i, t);

    auto test = [&](ll curi, ll curt, ll il, ll ih, ll tl, ll th){
        if(curi < il) return false;
        if(curi > ih) return false;
        if(curt < tl) return false;
        if(curt > th) return false;
        return true;
    };

    forn(j, 0, n) {
        ll il, ih, tl, th; cin >> il >> ih >> tl >> th;
        
        vector<p64> toadd;
        vector<p64> toera;

        for (auto [mi, mt] : s) {
            if (test(mi, mt, il, ih, tl, th)) {
                toadd.emplace_back(mi+1, mt);
                toadd.emplace_back(mi, mt+1);
                toera.emplace_back(mi, mt);
            }
        } 
        for(auto& p: toera){
            s.erase(p);
            proib[p.first-i][p.second-t] = 1;
        }
        for(auto& p: toadd){
            if(proib[p.first-i][p.second-t]) continue;
            s.insert(p);
        }
    }

    ll ans = 0;
    for (auto [x, y] : s) ans = max(ans, x+y - i - t);
    cout << ans << ln; 

    return 0;
}
