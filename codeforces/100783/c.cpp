#include <bits/stdc++.h>
using namespace std;


typedef long long ll;
typedef pair<ll, ll> p64;
typedef vector<ll> v64;

#define forn(i, s, e) for (ll i = (s); i < (e); i++)
#define ln "\n"

#if defined(DEBUG)
    #define _ 42
    #define debug(x) cout << __LINE__ << ": "<< #x << " = " << x << ln;
#else
    #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
    #define debug(x) 42
#endif

const ll INF = 0x3f3f3f3f3f3f3f3fll;
const ll MAXK = 200'001;
// const ll MAXK = 11;

int main() {
    _;
    ll n; cin >> n;
    v64 vec(n);
    forn(i,0,n) cin >> vec[i];

    bitset<MAXK> ks;
    ks[0] = 1;
    forn(i,0,n) ks[vec[i]] = 1;
    

    ll m; cin >> m;
    v64 target(m);
    forn(i,0,m) cin >> target[i];

    bitset<MAXK> resp;

    forn(i,0,n){
        // debug(vec[i]);
        // auto temp = ks << vec[i];
        // cout << temp << ln;
        resp |=  ks << vec[i];
    }

    ll cnt = 0;
    forn(i,0,m) cnt += resp[target[i]];
    cout << cnt << ln;
    return 0;
}