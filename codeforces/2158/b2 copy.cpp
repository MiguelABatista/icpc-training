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
    v64 vec(2*n);
    forn(i,0,2*n) cin >> vec[i];
    sort(vec.begin(), vec.end());

    ll resp = 0;
    do {
        map<ll, ll> freq1, freq2;
        ll curr = 0;
        forn(i,0,n) freq1[vec[i]]++;
        forn(i,n,2*n) freq2[vec[i]]++;
        for(auto [k,v]: freq1) if(v%2 == 1) curr++;
        for(auto [k,v]: freq2) if(v%2 == 1) curr++;
        resp = max(resp, curr);
    }while(next_permutation(vec.begin(), vec.end()));
    cout << resp << ln;
}

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}