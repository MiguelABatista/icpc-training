#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64;
typedef vector<ll> v64;

#define forn(i, s, e) for (ll i = (s); i < (e); i++)
#define ln "\n"

#if defined(DEBUG)
    #define _ (void) 0
    #define debug(x) cout << __LINE__ << ": " << #x << " = " << x << ln
    #define debugp(x) cout << __LINE__ << ": " << #x << " = " << x.first << " " << x.second << ln

#else
    #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
    #define debug(x) (void)0
    #define debugp(x) (void)0
#endif

const ll INF = 0x3f3f3f3f3f3f3f3fll;

const ll MAXN = 50'000;
const ll MAXLOGN = 20;

ll m[MAXN][MAXLOGN];

void build(v64& v){
    ll sz = v.size();

    forn(i,0,sz) m[i][0] = v[i];
    
    for(ll j = 1; (1<<j) <= sz; j++){
        for(ll i = 0; i + (1 << j) <= sz; i++){
            m[i][j] = max(m[i][j-1], m[i + (1 << (j-1))][j-1]);
        }
    }
}

ll query(ll a, ll b){
    ll j = __builtin_clzll(1) - __builtin_clzll(b-a+1);
    return max(m[a][j], m[b - (1 << j) + 1][j]); 
}

int main() {
    _;
    return 0;
}