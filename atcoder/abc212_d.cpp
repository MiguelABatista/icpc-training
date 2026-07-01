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

struct Venise{
    ll offset = 0;
    multiset<ll> s;
    void insert(ll x){
        x -= offset;
        s.insert(x);
    }
    void remove(ll x){
        x -= offset;
        auto it = s.find(x);
        s.erase(it);
    }
    void update_all(ll add){
        offset += add;
    }
    ll get_max_erase(){
        auto it = s.begin();
        ll x = *it;
        s.erase(it);
        return x + offset;
    }
    ll size(){
        return sz(s);
    }
};

void solve(){
    ll q; cin >> q;
    Venise v;
    while(q--){
        debug(v.size());
        ll t; cin >> t;
        if(t == 1){
            ll x; cin >> x;
            v.insert(x);
        }
        if(t == 2){
            ll x; cin >> x;
            v.update_all(x);
        }

        if(t == 3){
            cout << v.get_max_erase() << ln;
        }
    }
}

int main() {
    _;
    ll t = 1;;
    while(t--) solve();
    return 0;
}
