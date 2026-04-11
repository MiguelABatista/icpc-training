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
#define debugp(v) trace(cout << #v ": "; for (auto xx : v) cout << xx.first << ":" << xx.second << " "; cout << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;

int main() {
    _;
    ll n, k; cin >> n >> k;
    ll m = (k+1)/2;
    v64 vec(n);
    forn(i,0,n) cin >> vec[i];

    multiset<ll> small;
    multiset<ll> large;
    debug(n);
    debug(k);
    debug(m); 
    debugv(vec);

    forn(i,0,k) large.insert(vec[i]);
    forn(i,0,m){
        auto it = large.begin();
        small.insert(*it);
        large.erase(it);
    }

    
    cout << *prev(small.end()) << " ";
    forn(i,k,n){
        // debugv(small);
        // debugv(large);
        ll val = vec[i-k];
        auto it = small.find(val);
        if(it == small.end()) large.erase(val);
        else small.erase(it);
        large.insert(vec[i]);
        while(sz(small) < m){
            it = large.begin();
            small.insert(*it);   
            large.erase(it);
        }
        while (sz(large) && *prev(small.end()) > *large.begin()){
            auto itl = large.begin();
            ll vl = *itl;
            large.erase(itl);
            auto its = prev(small.end());
            ll vs = *its;
            small.erase(its);
            large.insert(vs);
            small.insert(vl);
        }
        
        cout << *prev(small.end()) << " \n"[i==n-1];
    }
    debugv(small);
    debugv(large);
    return 0;
}

