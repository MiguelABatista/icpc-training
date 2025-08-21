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
const ll INF = 0x3f3f3f3f3f3f3f3fll;

template<typename T>
struct node {
    ll lm, rm;
    unique_ptr<node> lc, rc;
    T val;

    static constexpr T neutral = T(INF); // Customize this for min/max/gcd/etc.

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
        return min(a, b); // Change to min/max/gcd as needed
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

v64 fib;
void prep(){
    fib = {2,3};
    ll cnt = 1;
    while(fib[cnt] <= 3'000'000'000ll){
        fib.push_back(fib[cnt-1]+fib[cnt]);
        cnt++;
    }
}

int main(){
    _;
    prep();
    ll n, q; cin >> n >> q;
    v64 vec(n);
    map<ll, set<ll>> mp;
    forn(i,0,n){
        cin >> vec[i];
        mp[vec[i]].insert(i);
    } 

    vector<p64> inter(q);
    vector<ll> resp(q);

    forn(i,0,n){
        cin >> inter[i].first >> inter[i].second;
    }

    // forn(i,0,n) cout << i << " ";; cout << ln;

    for(ll f: fib){
        v64 dir(n,INF);

        forn(i,0,n){
            ll target = f - vec[i];
            if(mp.find(target) == mp.end()) continue;
            auto& temp = mp[target];
            auto it = temp.upper_bound(i); 
            if(it == temp.end()) continue;
            dir[i] = *it;
        }

        // forn(i,0,n) cout << (dir[i] != INF ? char(dir[i]+'0') : '*') << " ";; cout << ln; 

        node seg(0, n-1, dir);
        
        forn(i,0,q){
            auto [l,r] = inter[i];
            
            ll temp = seg.query(l,r); 
            if(temp <= r) resp[i]++;
        }
    }

    forn(i,0,q) cout << resp[i] << ln; 
    return 0;
}