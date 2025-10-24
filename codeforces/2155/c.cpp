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
const ll MOD = 676767677;

bool simu(string& s, v64& vec, ll n){
    bool ruim = false;
    
    forn(i,1,n){
        if(vec[i] - vec[i-1] == -1){
            if(s[i-1] != 'R'){
                ruim = true; 
                break;
            }
            s[i] = 'R';
        }
        if(vec[i] - vec[i-1] == 0){
            if(s[i-1] == 'R') s[i] = 'L';
            if(s[i-1] == 'L') s[i] = 'R';
        }
        if(vec[i] - vec[i-1] == 1){
            if(s[i-1] != 'L'){
                ruim = true; 
                break;
            }
            s[i] = 'L';
        }
    }
    if(ruim) return false;

    ll lc = 0;
    ll rc = 0;
    forn(i,0,n){
        if(s[i] == 'L') lc++;
        if(s[i] == 'R') rc++;
    }
    if(s[0] == 'L') rc++;
    if(s[n-1] == 'R') lc++;

    if(rc == vec[0] && lc == vec[n-1]) return true;
    return false;
}
void solve(){
    ll n; cin >> n;
    v64 vec(n);
    forn(i,0,n) cin >> vec[i];
    ll ans = 0;
    string s(n, '.');
    s[0] = 'L';
    if(simu(s,vec,n)) ans++;
    s[0] = 'R';
    if(simu(s,vec,n)) ans++;
    cout << ans << ln;
}
int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}