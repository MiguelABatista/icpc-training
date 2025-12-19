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
const ll BOUND = 1'000'000'000'000'000'000ll;

void solve(){
    ll n; cin >> n;
    v64 a(2*n);
    set<ll> s;
    forn(i,0,2*n) cin >> a[i], s.insert(a[i]);
    
    sort(a.rbegin(), a.rend());

    v64 vec(2*n);
    forn(i,0,n){
        vec[2*i] = a[i];
        vec[2*i+1] = a[i+n]; 
    }

    ll x = 0;
    forn(i,0,2*n) x += vec[i]*(1-2*(i&1));
    if(x > vec[0]){
        cout << x << " ";
        forn(i,0,2*n) cout << vec[i] << " ";; cout << ln;
        return;
    }
    if(x < vec[0]){
        ll delta = vec[0] - x;
        cout << vec[0] << " ";
        vec[0] += delta;
        forn(i,0,2*n) cout << vec[i] << " ";; cout << ln;
        return;
    }
    ll maior = vec[0];
    vec.erase(vec.begin());
    vec.push_back(maior);
    x = vec[2*n-2];
    vec[2*n-2] += vec[2*n-2] + maior;
    cout << x << " ";
    forn(i,0,2*n) cout << vec[i] << " ";; cout << ln;

}

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}