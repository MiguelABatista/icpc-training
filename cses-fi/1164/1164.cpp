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
    ll n; cin >> n;

    vector<tuple<ll,ll,ll>> events;
    forn(i,0,n) {
        ll x, y; cin >> x >> y;
        events.push_back({x,0, i});
        events.push_back({y,1, i});
    }

    sort(events.begin(), events.end());

    v64 ocup(n);
    set<ll> disp;
    ll prox = 1;
    
    for(auto [x, fecha, idx] : events){
        if(fecha){
            disp.insert(ocup[idx]);
            continue;
        }

        if(!disp.empty()){
            ocup[idx] = *disp.begin();
            disp.erase(disp.begin());
        }else{
            ocup[idx] = prox++;
        }
    }
    cout << prox-1 << ln;
    forn(i,0,n) cout << ocup[i] << " \n"[i==n-1];

    return 0;

}
