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
#define debugp(u) trace(cout << #u " = " << u.first << ":" << u.second << ln)
#define debugv(v) trace(cout << #v ": "; for (auto xx : v) cout << xx << " "; cout << ln)
#define debugm(v) trace(cout << #v ": "; for (auto xx : v) cout << xx.first << ":" << xx.second << " "; cout << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;

// Modular Arithmetic Helpers
//
// Provides fast modular mul, fast exponentiation.
//
// complexity: O(log E) for power/inverse

typedef unsigned long long ull;
const ll MOD = 998244353;

ull modmul(ull a, ull b, ull M){ 
    ll ret = a*b - M * ull(1.L / M*a*b);    
    return ret + M * (ret < 0) - M * (ret >= (ll)M);
};

ull modpow(ull b, ull e, ull mod){
    ull ans = 1;
    for(; e; b = modmul(b, b, mod), e /= 2)
        if(e & 1) ans = modmul(ans, b, mod);
    return ans;
}


// Trie (Prefix Tree)
//
// Stores strings over a fixed alphabet to support insert, erase, and prefix counting in linear time.
//
// complexity: O(|s|) per op, O(total keys)

struct Trie {
    vector<map<ll,ll>> to;
    vll end, pref;
    ll sigma; ll norm;

    Trie(ll sigma_=1000, ll norm_=0) : sigma(sigma_), norm(norm_) {
        to = {map<ll,ll>()};
        end = {0}, pref = {0};
    }

    void insert(vll s) {
        ll x = 0;
        for (auto c : s) {
            ll &nxt = to[x][c-norm];
            if (!nxt) {
                nxt = sz(to);
                to.push_back(map<ll,ll>());
                end.push_back(0), pref.push_back(0);
            }
            x = nxt, pref[x]++;
        }
        end[x]++, pref[0]++;
    }

    void erase(vll s) {
        ll x = 0;
        for (ll c : s) {
            ll &nxt = to[x][c-norm];
            x = nxt, pref[x]--;
            if (!pref[x]) nxt = 0;
        }
        end[x]--, pref[0]--;
    }

    ll find(vll s) {
        ll x = 0;
        for (auto c : s) {
            x = to[x][c-norm];
            if (!x) return -1;
        }
        return x;
    }

    ll count_pref(vll s) {
        ll id = find(s);
        return id >= 0 ? pref[id] : 0;
    }
};


ll solve(vector<pll>& vec, pll centro){
    ll n = sz(vec);
    map<pll, vll> mp;


    vll vals;
    
    forn(i,0,n){
        pll dir = {vec[i].first - centro.first, vec[i].second - centro.second};
        ll d = gcd(dir.first, dir.second);
        ll dist2 = dir.first*dir.first + dir.second*dir.second;
        dir.first /= d;
        dir.second /= d;
        mp[dir].push_back(dist2);
        vals.push_back(dist2);
    }
    
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
 
    auto compress = [&](ll& x) {
        x = (ll)(lower_bound(vals.begin(), vals.end(), x) - vals.begin());
    };

    Trie trie(1000, 0);
    for(auto [p, v] : mp){ 
        for(ll& x: v) compress(x);
        sort(v.begin(), v.end());
        debugp(p);
        debugv(v);
        trie.insert(v);
    }

    ll ans = 0;
    forn(i,1,sz(trie.pref)){
        ll c = trie.pref[i];
        ans = (ans + modpow(2,c, MOD) - 1 + MOD)%MOD;
    }
    debug(ans);
    trace(cout << "-------------------\n\n";)
    return ans;
}

int main() {
    _;
    ll n; cin >> n;
    vector<pll> vec(n);

    forn(i,0,n){
        cin >> vec[i].first >> vec[i].second;
    }

    ll resp = 0;
    forn(i,0,n){
        vector<pll> aux = vec;
        debug(i);
        aux.erase(aux.begin()+i);
        pll centro = vec[i];
        resp += solve(aux, centro);
    }
    cout << resp + n << ln;
    return 0;
}
