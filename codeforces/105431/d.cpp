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

int main(){
    _;
    ll n, k;
    cin >> n >> k;
    v64 a(n*k);
    
    forn(i,0,n*k) cin >> a[i];

    vector<v64> mp(n+1, v64());

    v64 vec(n*k, 0);

    node dp(0,n*k-1, vec);

    forn(i,0,n*k){
        ll aux; cin >> aux;
        mp[aux].push_back(i);
    }

    forn(i,0,n*k){
        ll curr = a[i];
        for(ll j = k-1; j >= 0; j--){
            ll val = 0;
            ll idx = mp[curr][j]; 
            if(idx != 0) val = dp.query(0, idx-1);
            dp.point_set(idx, val+1);
        }
    }

    cout << dp.query(0,n*k-1) << ln;
    return 0;
}