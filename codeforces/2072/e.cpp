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

ll escolhe_2(ll n){
    return (n*(n-1))/2;
}

void solve(){
    ll k; cin >> k;
    ll curr_x = 0;
    ll curr_y = 0;
    vector<p64> resp;
    ll t = 1;
    ll n = 0;
    while(k > 0){
        t = 1;
        while(escolhe_2(t) <= k) t++;
        t--;

        k -= escolhe_2(t);
        
        forn(i,0,t){
            resp.push_back({curr_x, curr_y});
            curr_x++;
            n++;
        }
        curr_x++;
        curr_y++;
    }

    cout << n << ln;
    for(auto p: resp){
        cout << p.first << ' ' << p.second << ln;
    }
}

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}