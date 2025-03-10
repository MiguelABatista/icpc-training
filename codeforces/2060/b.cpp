#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64; 
typedef vector<ll> v64;

#define forn(i, s, e) for(ll i = (s); i < (e); i++)
#define ln "\n"

#if defined(DEBUG) || defined(debug)
    #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
    #define debug(x) cout << __LINE__ << ": " << #x << " = " << x << ln
#else
    #define _ (void)0
    #define debug(x) (void)0
#endif

const ll INF = 0x3f3f3f3f3f3f3f3fll;

void solve(){
    ll n, m;
    cin >> n >> m;

    vector<v64> cows(n,v64(m));

    forn(i,0,n){
        forn(j,0,m){
            cin >> cows[i][j];
        }
    }

    forn(i,0,n){
        sort(cows[i].begin(), cows[i].end());
    }

    v64 perm(n,-1);

    forn(i,0,n){
        if(cows[i][0] <= n){
            perm[cows[i][0]] = i;
        }
    }

    forn(i,0,n){
        if(perm[i] == -1){
            cout << -1 << ln;
            return;
        }
    }

    forn(i,0,n){
        forn(j,0,m-1){
            if(cows[i][j+1] - cows[i][j] != n){
                cout << -1 << ln;
                return;
            }
        }
    }

    forn(i,0,n){
        cout << perm[i] + 1 << ' ';
    }
    cout << ln;
}
int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}