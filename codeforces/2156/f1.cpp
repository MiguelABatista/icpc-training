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

bool try_p(ll p, v64& vec, v64& inv){
    if(p < 2) return false;
    if(inv[p] > inv[p-1] || inv[p] > inv[p-2]) return false;
    try_p(p-1,vec,inv);
    try_p(p-2,vec,inv);
    ll a = inv[p];
    ll b = inv[p-1]; 
    ll c = inv[p-2];
    vec[inv[p]] = p-2;
    vec[inv[p-1]] = p;
    vec[inv[p-2]] = p-1;
    inv[p-2] = a;
    inv[p-1] = c;
    inv[p] = b;
    return true;
}

void solve(){
    ll n; cin >> n;
    v64 vec(n);
    v64 inv(n);
    forn(i,0,n){
        cin >> vec[i];
        vec[i]--;
        inv[vec[i]] = i;
    }

    ll curr = 0;
    while(curr < n){
        ll p = vec[curr];
        if(p < 2){
            curr++;
            continue;
        }
        if(!try_p(p, vec, inv)) curr++;
        // for(ll x: vec) cout << x+1 << " ";; cout << ln;
    }
    for(ll x: vec) cout << x+1 << " ";; cout << ln;
}
int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}