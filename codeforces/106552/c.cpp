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
    ll n; cin >> n;
    vll vec(n);
    forn(i,0,n) cin >> vec[i];

    set<pll> s;
    vll pre(n+1,-1);
    ll pt = 0;
    
    forn(i,0,n){
        if(pre[vec[i]] != -1){
            ll npt = pre[vec[i]]+1;
            forn(j,pt,npt){
                s.erase({vec[j], j});
                pre[vec[j]] = -1;
            }
            pt = npt;
        }
        pre[vec[i]] = i;
        s.insert({vec[i],i});
        auto [v, k] = *prev(s.end());
        cout << v << " " << k+1 << ln;
    }
    return 0;
}
