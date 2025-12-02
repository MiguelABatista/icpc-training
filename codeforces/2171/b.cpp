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
    v64 vec(n);
    forn(i,0,n) cin >> vec[i];

    if(vec[0] == -1 && vec[n-1] == -1){
        vec[0] = vec[n-1] = 0;
    }else if(vec[0] == -1){
        vec[0] = vec[n-1];
    }else if(vec[n-1] == -1){
        vec[n-1] = vec[0];
    }

    cout << abs(vec[0] -vec[n-1]) << ln;
    forn(i,0,n) cout << (vec[i] == -1 ? 0 : vec[i]) << " ";; cout << ln;
    
}

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}