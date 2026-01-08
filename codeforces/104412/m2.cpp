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


int main(){
    _;
    ll n; cin >> n;
    v64 vec(n);
    forn(i,0,n) cin >> vec[i];

    ll resp = 0;

    forn(mask, 0, (1<<n)){
        v64 l(n);
        v64 r(n);
        bool bom = true;
        ll curr = INF;

        forn(i,0,n){
            if((1<<i)&mask) curr = vec[i];
            l[i] = curr;
        }
        for(ll i = n-1; i >= 0; i--){
            if((1<<i)&mask) curr = vec[i];
            r[i] = curr;
        }
        forn(i,0,n){
            if(((1<<i)&mask)) continue;
            if(vec[i] < min(l[i], r[i])){
                bom = false;
            }
        }
        if(bom) resp++;
    }

    cout << resp << ln;
    return 0;
}