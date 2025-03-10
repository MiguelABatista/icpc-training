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
    ll n;
    cin >> n;
    v64 vec(n);
    ll soma_pos = 0;
    ll soma_neg = 0;
    forn(i,0,n){
        cin >> vec[i];
        if(vec[i] < 0) soma_neg += vec[i];
        if(vec[i] > 0) soma_pos += vec[i];
    }

    ll p1 =0; 
    ll p2 = n-1;
    ll resp = 0;

    while(p1 <= p2){
        debug(p1);
        debug(p2);
        debug(resp);
        if(vec[p1] > 0){
            soma_pos -= vec[p1];
            resp += vec[p1];
            p1++;
            continue;
        }
        if(vec[p2] < 0){
            soma_neg -= vec[p2];
            resp -= vec[p2];
            p2--;
            continue;
        }

        if(soma_pos >= -soma_neg){
            soma_neg -= vec[p1];
            p1++;
            continue;
        }
        if(soma_pos < -soma_neg){
            soma_pos -= vec[p2];
            p2--;
            continue;
        }
    }
    
    cout << resp << ln;
}

int main(){
    _;
    ll t; cin >> t;
    while(t--){
        solve();
    }
    return 0;
}