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
    ll n, k; cin >> n >> k;
    vector<v64> shoots(k, v64(n));



    forn(i,0,k){
        forn(j,0,n) cin >> shoots[i][j];
    }
 
    if(k == 1 || n == 1){
        cout << "YES" << ln;
        return;
    }

    v64 poder(n+1);
    ll val = shoots[0][0];
    ll lb = -INF;
    ll ub = INF;
    forn(i,1,n){
        poder[shoots[0][i]] = 2*i;
    }

    forn(i,0,k){ 
        forn(j,1,n) if(shoots[i][j] == val){
            if(j > 1) lb = max(lb, poder[shoots[i][j-1]]);
            if(j < n-1) ub = min(ub, poder[shoots[i][j+1]]);
        }
    }  
    debug(lb);
    debug(ub); 
    if(lb >= ub){
        cout << "NO" << ln;
        return;
    }
    poder[val] = (lb+ub)/2;
    debugv(poder);
    bool bom = true;
    forn(i,0,k){
        forn(j,1,n-1){
            if(poder[shoots[i][j]] > poder[shoots[i][j+1]]) bom = false;
        }
    }
    if(bom) cout <<"YES" << ln;
    else cout << "NO" << ln;
}

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}