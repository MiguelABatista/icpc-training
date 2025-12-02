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
    vector<string> mat(n);
    forn(i,0,n) cin >> mat[i];
    // forn(i,0,n) cout << mat[i] << ln;;
    set<ll> s1;
    set<ll> s2;
    ll cnt = 0;
    forn(i,0,n){
        forn(j,0,n) if(mat[i][j] == '#'){
            cnt++;
            s1.insert(i+j);
            s2.insert(i-j);
        }
    }
    
    bool bom = false;
    if(cnt == 4 ){
        forn(i,0,n){
           forn(j,0,n) if(mat[i][j] == '#'){
                if(i != n-1 && j != n-1){
                    if(mat[i+1][j] == '#' && mat[i][j+1] == '#' &&  mat[i+1][j+1] == '#'){
                        bom = true;
                    }
                }
            }
        }
    }

    // debugv(s1);
    // debugv(s2);
    if(s1.size() == 0 || s2.size() == 0) bom = true;
    if(s1.size() == 1) bom = true;
    if(s1.size() == 2){
        ll x = *s1.begin();
        ll y = *s1.rbegin();
        if(abs(x-y) == 1) bom = true;
    }
    
    if(s2.size() == 1) bom = true;
    if(s2.size() == 2){
        ll x = *s2.begin();
        ll y = *s2.rbegin();
        if(abs(x-y) == 1) bom = true;
    }
    if(bom) cout << "YES" << ln;
    else cout << "NO" << ln;
}
int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}