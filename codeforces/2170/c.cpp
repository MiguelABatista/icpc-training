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
    v64 q(n), r(n);
    forn(i,0,n) cin >> q[i];
    forn(i,0,n) cin >> r[i];

    sort(q.begin(), q.end());
    sort(r.begin(), r.end());

    v64 degq(n);
    v64 degr(n);

    forn(i,0,n){
        ll targetq = (k-r[i])/(r[i]+1);
        degr[i] = upper_bound(q.begin(), q.end(), targetq) - q.begin();
        
        ll targetr = (k-1)/(q[i]+1);
        degq[i] = upper_bound(r.begin(), r.end(), targetr) - r.begin();
    }

    ll resp = 0;
    ll minq = INF;
    ll minr = INF;

    forn(i,0,n){
        minq = min(minq, degq[i]+i);
        minr = min(minr, degr[i]+i);
        if(minq >= i+1 && minr >= i+1){
            resp = i+1;
        }
    }
    cout << resp << ln;
}

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}