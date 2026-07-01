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

struct Venice{
    multiset<ll> s;
    ll offset = 0;
    void add(ll x){
        x += offset;
        s.insert(x);
    }

    void remove(ll x){
        x += offset;
        auto it = s.find(x);
        s.erase(it);
    }

    void update_all(ll x){
        offset += x;
    }

    ll get_min(){
        return *s.begin() - offset;
    }

    ll size(){
        return sz(s);
    }
};

void solve(){
    ll n; cin >> n;
    vll v(n), t(n);
    forn(i,0,n) cin >> v[i];
    forn(i,0,n) cin >> t[i];
    
    Venice s;
    forn(i,0,n){
        s.add(v[i]);
        s.update_all(t[i]); 

        ll total = t[i] * s.size(); 
        
        while (s.size() > 0 && s.get_min() < 0) {
            ll x = s.get_min();             
            total -= abs(x);

            s.remove(x);
        }

        cout << total << " \n"[i==n-1];
    }
}

int main() {
    _;
    ll t = 1;
    while(t--) solve();
    return 0; 
}
