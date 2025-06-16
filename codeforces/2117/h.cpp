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

struct T{
    ll l_max = 0;
    ll r_max = 0;
    ll sum = 0;
    ll best_sub = 0;
    
    T(){}
    
    T(ll val){
        sum = val;
        if(val <= 0) return;
        l_max = val;
        r_max = val;
        best_sub = val;
    }

    T(ll x, ll y, ll z, ll w){
        l_max = x;
        r_max = y;
        sum = z;
        best_sub = w;
    } 
};

struct node {
    ll lm, rm;
    unique_ptr<node> lc, rc;
    T val;

    T neutral = T(); // Customize this for min/max/gcd/etc.

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
        ll l_max = max(a.l_max, a.sum + b.l_max);
        ll r_max = max(a.r_max + b.sum, b.r_max);
        ll sum = a.sum + b.sum;
        ll best_sub = max(a.best_sub, b.best_sub);
        best_sub = max(best_sub, a.r_max + b.l_max);
        return T(l_max, r_max, sum, best_sub); 
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

    void print(){
        cout << lm << " " << rm << " : " << val.l_max << " " << val.r_max << " " << val.best_sub << " " << val.sum << ln; 
        if(lc) lc->print();
        if(rc) rc->print();
    }
};

void solve(){
    ll n; cin >> n;
    
}

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}