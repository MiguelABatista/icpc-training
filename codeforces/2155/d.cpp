#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64; 
typedef vector<ll> v64;

#define forn(i, s, e) for(ll i = (s); i < (e); i++)
#define sz(x) ((ll) x.size())
#define ln endl

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

bool ask(ll u, ll v){
    cout << u+1 << " " << v+1 << ln;
    ll x; cin >> x;
    return (x == 1);
}

void solve(){
    ll n; cin >> n;
    ll delta = 1;
    while(true){
        forn(i,0,n){
            if(ask(i,(i+delta)%n)) return;
        }
        delta++;
    }
}

int main(){
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}