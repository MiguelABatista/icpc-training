#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64; 
typedef vector<ll> v64;

#define forn(i, s, e) for(ll i = (s); i < (e); i++)
#define ln "\n"

#if defined(DEBUG)
    #define _ (void)0
    #define debug(x) cout << __LINE__ << ": " << #x << " = " << x << ln
#else
    #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
    #define debug(x) (void)0
#endif

const ll INF = 0x3f3f3f3f3f3f3f3fll;

struct Bit {
    ll n;
    v64 bit;
    Bit(ll _n=0) : n(_n), bit(n+1) {}
    Bit(v64& v) : n(v.size()), bit(n+1) {
        for (ll i = 1; i <= n; i++) {
            bit[i] += v[i - 1];
            ll j = i + (i & -1);
            if (j <= n) bit[j] += bit[i];
        }
    }
    void update(ll i, ll x) {
        debug(i);
        for(i++; i <= n; i += i & -i) bit[i] += x;
    }
    ll pref(ll i) {
        ll ret = 0;
        for(i++; i; i -= i & -i){debug(i); ret += bit[i];}
        return ret;
    }
    ll query(ll l, ll r) {
        debug(l);
        debug(r);
        return pref(r) - pref(l-1);
    }
    ll upper_bound(ll x){ 
        ll p = 0;
        for(ll i = __lg(n); i+1; i--)
            if(p + (1<<i) <= n and bit[p + (1<<i)] <= x)
                x -= bit[p += (1<<i)];
        return p;
    }
};

int main(){
    _; ll n; cin >> n;
    vector<vector<ll>> v(n);
    forn(i, 0, n){
        ll a; cin >> a;
        forn(j, 0, a){
            ll b; cin >> b; b++;
            v[i].push_back(b);
        }
    }

    Bit fenw(n+1);
    ll sum = 0;

    forn(i, 0, n){
        for(auto x : v[i]){
            sum += fenw.query(x+1, n);
        }
        for(auto x : v[i]){
            fenw.update(x, 1);
        }
    }

    cout << sum << ln;
    
    return 0;
}