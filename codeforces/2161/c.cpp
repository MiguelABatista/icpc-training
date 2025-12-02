#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64; 
typedef vector<ll> v64;

#define forn(i, s, e) for(ll i = (s); i < (e); i++)
#define sz(x) ((ll) x.size())
#define ln "\n"

#ifdef DEBUG
    #define trace(x) x
    #define _ (void)0
#else
    #define trace(x) (void)0
    #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
#endif

#define debugv(v) trace({cout << #v": "; for (auto x : v) cout<< x << " "; cout << ln;})
#define debug(x) trace(cout << __LINE__ << ": " #x " = " << x << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;

void solve(){
    ll n, x; cin >> n >> x;
    v64 vec(n);
    forn(i,0,n) cin >> vec[i];
    sort(vec.begin(), vec.end());

    ll p1 = 0;
    ll p2 = n-1;
    ll curr = 0;
    ll ans = 0;
    v64 resp;
    while(p1 <= p2){
        if(curr/x != (curr+vec[p2])/x){
            resp.push_back(vec[p2]);
            ans += vec[p2];
            curr += vec[p2];
            p2--;
        }else{
            resp.push_back(vec[p1]);
            curr += vec[p1];
            p1++;
        }
    }
    cout << ans << ln;
    forn(i,0,n) cout << resp[i] << " ";; cout << ln;
}
int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}