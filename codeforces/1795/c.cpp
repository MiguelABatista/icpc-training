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
        x += offset;
        s.insert(x);
    }
    void remove(ll x){
        x += offset;
        auto it = s.find(x);
        s.erase(it);
    }
    void update_all(ll add){
        offset += add;
    }
    ll size(){
        return sz(s);
    }
    ll get_min(){
        auto it = s.begin();
        return *it-offset;
    }
    void erase_min(){
        s.erase(s.begin());
    }
};

void solve(){
    ll n; cin >> n;
    vll a(n), b(n);
    forn(i,0,n) cin >> a[i];
    forn(i,0,n) cin >> b[i];
    
    Venise v;
    
    forn(i,0,n){
        v.insert(a[i]);
        ll tot = v.size()*b[i];
        v.update_all(b[i]);
        while(v.size() > 0 && v.get_min() < 0){
            tot -= abs(v.get_min());
            v.erase_min();
        }
        cout << tot << " \n"[i==n-1];
    }

}

int main() {
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}
