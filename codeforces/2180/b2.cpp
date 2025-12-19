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
    ll n; cin >> n;
    vector<string> vec(n);
    forn(i,0,n) cin >> vec[i];
    string resp = "{}";

    forn(mask, 0, 1<<n){
        string curr;
        forn(i,0,n){
            if(mask&(1<<i)) curr += vec[i];
            else curr = vec[i] + curr;
        }
        if(curr < resp) resp = curr;
    }

    cout << resp << ln; 
}

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}