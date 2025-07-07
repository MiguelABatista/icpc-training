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

mt19937_64 rng((ll) chrono::steady_clock::now().time_since_epoch().count());

ll uniform(ll l, ll r){
	uniform_int_distribution<ll> uid(l, r);
	return uid(rng);
}

int main(){
    _;
    ll n = uniform(1,10);
    v64 perm(n);
    iota(perm.begin(), perm.end(), 1);
    mt19937 rng(random_device{}());

    while (true) {
        shuffle(perm.begin(), perm.end(), rng);
        bool valid = true;
        forn(i, 0, n) {
            if (perm[i] == i + 1) {
                valid = false;
                break;
            }
        }
        if (valid) break;
    }

    forn(i, 0, n) cout << perm[i] << " \n"[i == n - 1];
    
    return 0;
}
