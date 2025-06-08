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

ll conv(p64 p){
    return p.first*100 + p.second;
}

void solve(){
    ll n, m;
    cin >> n >> m;
    vector<p64> vec(m);
    
    forn(i,0,m) {
        ll aux; cin >> aux;
        vec[i] = {aux/100, aux%100};
    }
    
    sort(vec.begin(), vec.end());


    ll resp = 0; 
    forn(i,0,(n+1)/2){
        resp += 5*abs(vec[m-i-1].first - vec[i].first);
        forn(kkk,0,3)
            cout << conv(vec[i]) << " " << conv(vec[m-i-1]) << " ";
        cout << ln;
    }
    ll idx = 0;
    forn(j,(n+1)/2, n){
        resp += 5*abs(vec[m-idx-1].first - vec[idx].first);
        forn(kkk,0,3)
            cout << conv(vec[m-idx-1]) << " " << conv(vec[idx]) << " ";
        cout << ln;
        idx++;
    }
    //cout << resp << ln;
}

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}