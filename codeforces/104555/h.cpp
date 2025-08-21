// Template Skeleton
//
// Sets up fast I/O, aliases, and basic macros for contests.

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

// Segment Tree (Range Query + Point Update)
//
// Balanced binary tree for range queries with a customizable combine; supports point updates and range queries.
//
// complexity: O(log N) per op, O(N)

template<typename T>
struct node {
    ll lm, rm;
    unique_ptr<node> lc, rc;
    T val;

    static constexpr T neutral = T(-INF); // Customize this for min/max/gcd/etc.

    node(ll l_, ll r_, const vector<T>& v) : lm(l_), rm(r_) {
        if (lm == rm) {
            val = v[lm];
        } else {
            ll m = (lm + rm) / 2;
            lc = make_unique<node>(lm, m, v);
            rc = make_unique<node>(m + 1, rm, v);
            pull();
        }
    }

    static T comb(const T& a, const T& b) {
        return max(a,b); // Change to min/max/gcd as needed
    }

    void pull() {
        val = comb(lc->val, rc->val);
    }

    void point_set(ll idx, T x) {
        if (lm == rm) {
            val = x;
            return;
        }
        if (idx <= lc->rm) lc->point_set(idx, x);
        else rc->point_set(idx, x);
        pull();
    }

    T query(ll lq, ll rq) {
        if (rq < lm || lq > rm) return neutral;
        if (lq <= lm && rm <= rq) return val;
        return comb(lc->query(lq, rq), rc->query(lq, rq));
    }
};

struct trab{
    ll l, r, c;
    ll trad_r;
    trab(){
        l = r = c = -1;
    }

   	bool operator < (const trab p) const {
		if (r != p.r) return r < p.r;
		if (l != p.l) return l < p.l;
        if (c != p.c) return c < p.c;
		return 0;
	}
};

int main(){
    _; ll n, s; cin >> n >> s;
    // vector<ll> tempo(n);
    set<ll> conj;
    vector<trab> trabs(n);
    forn(i, 0, n){
        cin >> trabs[i].l >> trabs[i].r >> trabs[i].c;
        conj.insert(trabs[i].r);
    }

    ll aux = 0;
    map<ll,ll> traduz;
    for(auto x : conj){
        traduz[x] = aux;
        // tempo[aux] = x;
        aux++;
    }

    for(auto& t : trabs){
        t.trad_r = traduz[t.r];
    } 

    sort(trabs.begin(), trabs.end());

    v64 dp(conj.size(), 0);
    v64 asdasd = v64(conj.size(),0); 
    node bit(0, conj.size()-1, asdasd); 
    
    forn(i, 0, n){
        trab& t = trabs[i];
        ll idx = t.trad_r;

        if(idx == 0){
            dp[idx] =  max(0ll, (t.r-t.l+1)*s-t.c);
            bit.point_set(idx, dp[idx] - s*t.r);
            continue;
        }

        ll trad_l = traduz[*conj.lower_bound(t.l)];
        ll prev = 0;
        if(trad_l != 0) prev = dp[trad_l-1];
        
        ll ans = prev + (t.r-t.l+1)*s-t.c;
        ll temp = bit.query(trad_l, t.trad_r-1);
        ans = max(ans, temp + - t.c + t.r*s);
        ans = max(ans, dp[idx-1]);
        ans = max(ans, dp[idx]);
        dp[idx] = ans;
        bit.point_set(idx, dp[idx] - s*t.r);
    }

    // forn(i,0,conj.size()) cout << dp[i] << " ";; cout << ln;
    cout << *prev(dp.end()) << ln;
    return 0;
}
