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
const ll MOD = 1'000'000'007;

struct venise{
    ll off = 0;
    map<ll,ll> mp;

    void add_on(ll add, ll idx){
        mp[idx-off] += add;
    }
    ll ask(ll idx){
        return mp[idx-off];
    }
    void add_off(ll add){
        off += add;
    }
};

void solve(){
    string s; cin >> s;
    ll n = sz(s);
    vll vec(n);
    forn(i,0,n) vec[i] = (s[i] == '1' ? 1 : -1);
    
    ll resp = 0;
    venise ven;
    forn(i,0,n){
        ll x = vec[i];
        ven.add_on(x, i+1);
        ven.add_off(x);
        resp += (resp+ven.ask(0))%MOD;
    }
    
    cout << resp << ln;
}

int main() {
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}
