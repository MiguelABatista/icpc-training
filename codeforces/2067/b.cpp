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
    ll n; cin >> n;
    v64 freq(1002,0);
    forn(i,0,n){
        ll aux;
        cin >> aux;
        freq[aux]++;
    }

    forn(i,0,1001){
        ll f = freq[i];
        if(f == 0) continue;
        if(f == 1){
            cout << "No" << ln;
            return;
        } 
        freq[i+1] += f-2;
    }

    if(freq[1001] % 2 == 1){
        cout << "No" << ln;
        return;
    } 
    cout << "Yes" << ln;
}

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();

}