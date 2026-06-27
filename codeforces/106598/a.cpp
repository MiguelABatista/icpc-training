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


int main() {
    _;
    ll n, q; cin >> n >> q;
    vector<tuple<ll,ll,ll,ll>> vec;

    forn(i,0,n){
        ll c, s; cin >> c >> s;
        vec.push_back({c,0,s,i});
    }
    forn(i,0,q){
        ll c, s; cin >> c >> s;
        vec.push_back({c,1,s,i});
    }

    sort(vec.begin(), vec.end());
    vll resp(q,-2);

    set<pll> s;

    // forn(i,0,sz(vec)){
    //     auto [a,b,c,d] = vec[i];
    //     cout << i << ": " <<  a << " " << b << " " << c << " " << d << ln;
    // };
    // cout << ln << ln;

    for(auto tup : vec){
        auto [c,t,m,idx] = tup;
        if(t == 0){
            s.insert((pll){idx,m});
        }else{
            debug(c);
            debug(t);
            debug(m);
            debug(idx);
            debugm(s);
            if(sz(s) == 0) continue;
            bool f = false;
            while(sz(s) >= 2){
                auto it = s.begin();
                auto it2 = next(s.begin());
                if(it->second == it2->second) s.erase(it2);
                else{
                    if(it->second == m) resp[idx] = it2->first;
                    else resp[idx] = it->first;
                    f = true;
                    break;
                }
            }
            if(f) continue;
            // sz(s) == 1;
            auto it = s.begin();
            if(it->second != m) resp[idx] = it->first;
        }
    }
    for(ll x : resp) cout << x+1 << ln;
    return 0;
}
