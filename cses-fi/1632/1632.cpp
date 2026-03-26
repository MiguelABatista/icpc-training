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

    ll n, k; cin >> n >> k;
    vector<p64> vec(n);    
    forn(i,0,n){
        ll a, b; cin >> a >> b;
        vec[i] = {b,a};
    }
    sort(vec.begin(), vec.end());
    multiset<ll> mt;
    forn(i,0,k) mt.insert(0);
    ll resp = 0;

    forn(i,0,n){        
        ll t = vec[i].second;
        auto it = mt.lower_bound(-t);
        if(it == mt.end()) continue;  
        mt.erase(it);      
        resp++;
        mt.insert(-vec[i].first);
    }

    cout << resp << ln;
    return 0;
}
 