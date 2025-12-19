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

void solve(){
    ll n, m; cin >> n >> m;
    vector<v64> mat(n, v64(m));
    ll maxval = 0;
    forn(i,0,n) forn(j,0,m){
        cin >> mat[i][j];
        maxval = max(maxval, mat[i][j]);
    }


    v64 r(n);
    v64 c(m);
    ll tot = 0;

    forn(i,0,n) forn(j,0,m) if(mat[i][j] == maxval){
        r[i]++;
        c[j]++;
        tot++;
    }

    ll to_sub = 0;
    forn(i,0,n) forn(j,0,m) {
        ll val = r[i] + c[j] - (mat[i][j] == maxval ? 1 : 0);
        if(val == tot){
            to_sub = 1;
            break;
        }
    }
    cout << maxval - to_sub << ln;
}

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}