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

void solve(){
    ll n; cin >> n;
    v64 vec(n);
    set<ll> pula;

    forn(i,0,n) cin >> vec[i];
    v64 s = vec;

    sort(s.begin(), s.end());

    forn(i,0,n){
        if(vec[i] == s[i]) pula.insert(i);
    }
    
    if(pula.size() == n){
        cout << "NO" << ln;
        return;
    }
    cout << "YES" << ln;
    cout << n - (ll)pula.size() << ln;
    forn(i,0,n){
        if(pula.count(i)) continue;
        cout << vec[i] << " ";
    }
    cout << ln;
}   

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}