#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64; 
typedef vector<ll> v64;

#define forn(i, s, e) for(ll i = (s); i < (e); i++)
#define ln "\n"

#if defined(DEBUG)
    #define _ (void)0
    #define debug(x) cout << __LINE__ << ": " << #x << " = " << x << ln
#else
    #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
    #define debug(x) (void)0
#endif

const ll INF = 0x3f3f3f3f3f3f3f3fll;

int main(){
    _;
    ll t; cin >> t;
    vector<p64> valid(10000, {-1,-1});

    forn(a,0,101){
        forn(b,a,101){
            ll aux = (a+b)*(a+b);
            if(aux > 9999) break;

            valid[aux] = {a,b};
        }
    }    

    forn(i,0,t){
        ll ano; cin >> ano;
        if(valid[ano].first == -1){
            cout << -1 << ln;
            continue;
        }

        cout << valid[ano].first << " " << valid[ano].second << ln;
        // cout << (valid[ano].first+ valid[ano].second)*(valid[ano].first+ valid[ano].second) << ln;
    }
    return 0;
}