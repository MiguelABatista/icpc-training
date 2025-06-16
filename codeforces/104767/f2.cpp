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

void solve(v64 v){
    ll n = v.size();

    ll best_resp = 0;

    do {
        ll curr = 0;
        forn(i,0,n-1){
            curr += gcd(v[i], v[i+1]);
        }
        best_resp = max(best_resp, curr);
    } while (std::next_permutation(v.begin(), v.end()));
    
    cout << best_resp << ln;
    return ;
}

int main(){
    ll n; cin >> n;
    v64 vec(n);
    forn(i,0,n) cin >> vec[i];

    sort(vec.begin(), vec.end());

    solve(vec);

    return 0;
}