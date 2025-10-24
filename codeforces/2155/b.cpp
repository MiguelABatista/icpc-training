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
    vector<string> lab(n, string(n, 'L'));
    if(k == n*n-1){
        cout << "NO" << ln;
        return;
    }
    if(k == 0){
        forn(j,0,n){
            lab[j][0] = 'R';
        }
    }
    forn(i,0,n){
        if(k >= n){
            k-= n;
            continue;
        }
        if(k ==  n-1) lab[i][k] = 'D';
        else lab[i][k] = 'R';
        forn(j,i+1,n){
            lab[j][0] = 'R';
        }
        k = 0;
    }
    cout << "YES" << ln;
    forn(i,0,n){ cout <<  lab[i] << ln;}
}
int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}