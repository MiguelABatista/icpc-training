#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64; 
typedef vector<ll> v64;

#define forn(i, s, e) for(ll i = (s); i < (e); i++)
#define ln "\n"

#if defined(DEBUG) || defined(debug)
    #define _ (void)0
    #define debug(x) cout << __LINE__ << ": " << #x << " = " << x << ln
#else
    #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
    #define debug(x) (void)0
#endif

const ll INF = 0x3f3f3f3f3f3f3f3fll;

const ll maxv = 1000100;
vector<bool> prime(maxv, true);
v64 factor(maxv), ans(maxv), cnt(maxv);

void sieve() {
    factor[1] = 1;
    forn(i, 2, maxv) {
        if (!prime[i]) continue;
        factor[i] = i;

        for (ll j = i*i; j < maxv; j += i) {
            prime[j] = false;
            factor[j] = i;
        }
    }
}

void get_parts(ll i, ll mult, v64& primes, v64& vec) {
    if (i == primes.size()) {
        vec.push_back(mult);
        return;
    }

    get_parts(i+1, mult, primes, vec);
    get_parts(i+1, mult * -primes[i], primes, vec);
}

v64 factors(ll n) {
    v64 ret;
    set<ll> st;
    while(n != 1) {
        if (!st.count(factor[n])) ret.push_back(factor[n]);
        st.insert(factor[n]);
        n /= factor[n];
    }

    return ret;
}


int main(){
    _;
    ll n; cin >> n;
    v64 pow2(maxv);
    pow2[1] = 2;
    forn(i, 2, maxv) {
        pow2[i] = (pow2[i-1] * 2) % (1000000000 + 7);
    }
    sieve();

    forn(i, 0, n) {
        ll food; cin >> food;
        v64 parts;
        v64 primes = factors(food);

        get_parts(0, 1, primes, parts);
        for (auto part : parts) {
            cnt[abs(part)]++;
        }
    }

    forn(i, 1, maxv) {
        if (!cnt[i]) continue;
        for (ll j = i; j < maxv; j += i) {
            ans[j] += cnt[i];
        }
    }

    ll q; cin >> q;
    forn(i, 0, q) {
        ll val; cin >> val;
        cout << pow2[ans[val]] << ln;
    }
 
    return 0;
}