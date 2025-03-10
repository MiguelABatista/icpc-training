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

int main(){
    _;
    ll n; cin >> n;
    vector<string> v(n);
    forn(i,0,n) cin >> v[i];
    string s1, s2;
    cin >> s1 >> s2;
    ll idx1, idx2;

    forn(i,0,n){
        if(v[i] == s1){
            idx1 = i;
        } 
        if(v[i] == s2){
            idx2 = i;
        }
    }

    if(idx1 == idx2){
        cout << 0 << ln;
    }

    ll dist = abs(idx1 - idx2);
    cout << (dist/2) + (dist % 2) << ln;
    return 0;
}