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

mt19937_64 rng((ll) chrono::steady_clock::now().time_since_epoch().count());

ll uniform(ll l, ll r){
    uniform_int_distribution<ll> uid(l, r);
    return uid(rng);
}

int main() {
    _;
    ll n = uniform(4,5);
    ll m = uniform(n+2, min(n*(n-1)/2, 10ll));
    
    cout << n << " " << m << ln;

    ll x = uniform(2,n-1);
    set<p64> s;
    s.insert({1,x});
    s.insert({x,n});

    while(sz(s) < m){
        ll a = uniform(1,n);
        ll b = a;
        while(b == a) b = uniform(1,n);
        s.insert({a,b});
    }

    for(auto [a,b] : s) cout << a << " " << b << ln;
    return 0;
}
