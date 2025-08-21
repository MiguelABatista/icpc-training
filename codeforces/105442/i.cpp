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

int main(){
    _;
    ll n, k; cin >> n >> k;
    v64 vec(n);
    for(ll& x: vec) cin >> x;

    vector<v64> mat(31, v64(n));
    vector<v64> last(31, v64(n));
    
    forn(i,0,31){
        forn(j,0,n){
            mat[i][j] = ((vec[j] & (1<<i)) != 0);
        }
    }

    forn(i,0,31){
        forn(j,0,n){
            if(mat[i][j]) last[i][j] = j;
            else last[i][j] = (j== 0? -1 : last[i][j-1]);
        }
    }

    ll ans = 0;
    forn(i,0,n){
        ll lb = 0;
        ll rb = i;
        forn(j,0,31){
            if(k & (1<<j)){
                rb = min(last[j][i], rb);
            }else{
                lb = max(last[j][i]+1, lb);
            }
        }
        if(rb >= lb) ans += rb-lb+1;
    }
    cout << ans << ln;
    return 0;
}