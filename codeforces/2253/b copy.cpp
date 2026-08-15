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
    ll n; cin >> n;
    vll vec(n);
    forn(i,0,n) cin >> vec[i];
    vector<pll> comps;

    ll p1 = 0;
    ll p2 = 0;
    while(p2 < n){
        if(vec[p2] == vec[p1]){
            p2++;
            continue;
        }else{
            comps.push_back({p2-p1, vec[p1]});
            p1 = p2;
        }
    }
    comps.push_back({p2-p1, vec[p1]});
    debugv(vec);
    debugm(comps);

    ll k = sz(comps);

    ll bonus = 0;
    forn(i,0,k-1){
        if(i > 0 && comps[i].first == 1 && comps[i+1].first >= 2 && (comps[i+1].second != comps[i-1].second)){
            bonus = max(bonus, 1ll);
            debug(1);
        } 
        if(comps[i].first >= 2 && comps[i+1].first >= 2){
            bonus = max(bonus, 2ll);
            debug(2);
        }
        if(i+2 < k && comps[i].first >= 2 && comps[i+2].second != comps[i].second){
            bonus = max(bonus, 1ll);
            debug(3);
        } 
    }
    
    cout << k + bonus << ln;
    trace(cout << "-----------------\n\n");
}

int main() {
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}
