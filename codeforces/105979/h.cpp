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
    ll n, h, k; cin >> n >> h >> k;

    vector<tuple<ll,ll,ll>> vec;

    forn(i,0,n){
        ll x, y, t; cin >> x >> y >> t;
        vec.push_back({x,y,t});
    }

    ll inix, iniy;
    cin >> inix >> iniy;
    queue<pair<tuple<ll,ll,ll>, ll>> q;

    forn(i,0,n){
        auto [x,y,t] = vec[i];
        if(x == inix && y == iniy){
            q.push({vec[i], 0});
            swap(vec[i], vec[n-1]);
            vec.pop_back();
            break;
        }
    }

    auto reach = [&](tuple<ll,ll,ll> tus, tuple<ll,ll,ll> tuc){
        auto [xs, ys, ts] = tus;
        auto [xc, yc, tc] = tuc;

        ll d2 = (xs-xc)*(xs-xc) + (ys-yc)*(ys-yc);
        if(ts == 0 && tc == 0) return false;
        if(ts == 0 && tc == 1) return d2 <= k*k;
        if(ts == 1 && tc == 0) return d2 <= h*h;
        if(ts == 1 && tc == 1) return d2 <= max(k,h)*max(k,h);
        assert(false);
    };

    while(!q.empty()){
        auto [tup, d] = q.front();
        q.pop();
        auto [x,y,t] = tup;
        if(y == 0){
            cout << d << ln;
            return 0;
        } 
        if((t == 1 && y >= -h)){
            cout << d+1 << ln;
            return 0;
        }
        for(ll i = 0; i < sz(vec);){
            if(reach(tup, vec[i])){
                q.push({vec[i], d+1});
                swap(vec[i], vec.back());
                vec.pop_back();
            }else{
                i++;
            }
        }
    }    
    
    cout << -1 << ln;
    return 0;
}
