#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
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
const ld ep = 1e-10;
 
int main() {
    _;
    ll n; ld velo; cin >> n >> velo;
    vector<ld> prio;
    vector<ld> nprio;
    
    forn(i,0,n){
        char c; ll x;
        cin >> c >> x;
        
        if(c == 'P'){
            prio.push_back(x);
        }else{
            nprio.push_back(x);
        }
        
    }
    sort(prio.rbegin(), prio.rend());
    sort(nprio.rbegin(), nprio.rend());
    ld tot = 0;

    while(sz(prio) && sz(nprio)){
        ld vprio = (velo*0.75)/sz(prio);
        ld tprio = *min_element(prio.begin(), prio.end())/vprio;
        
        ld vnprio = (velo*0.25)/sz(nprio); 
        ld tnprio = *min_element(nprio.begin(), nprio.end())/vnprio;

        ld t = min(tprio, tnprio);
        tot += t;
        for(auto& x: prio) x -= vprio*t;
        for(auto& x: nprio) x -= vnprio*t;

        vector<ld> tmp;
        for(auto x : prio) if(x > ep) tmp.push_back(x);
        prio = tmp;
        tmp.clear();
        
        for(auto x : nprio) if(x > ep) tmp.push_back(x);
        nprio = tmp;
    }
    
    if(sz(prio) == 0) swap(prio, nprio);

    while(sz(prio)){
        ld vprio = velo/sz(prio);
        ld tprio = *min_element(prio.begin(), prio.end())/vprio;
        ld t = tprio;
        tot += tprio;
        for(auto& x: prio) x -= vprio*tprio;
        
        vector<ld> tmp;
        for(auto x : prio) if(x > ep) tmp.push_back(x);
        prio = tmp;
    }

    cout << fixed << setprecision(20) << tot << ln;
    return 0;
}