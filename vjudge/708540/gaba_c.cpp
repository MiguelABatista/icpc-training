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
    ll n; cin >> n;
    ll k; cin >> k;

    v64 vec(n);
    map<ll, ll> mp;

    forn(i,0,n) cin >> vec[i];

    ll l = 0;
    ll r = 0;
    ll resp = 0;
    mp[vec[l]]++;

    while(l < n){
        while(r < n-1){
            if((mp.size() == k) && (mp[vec[r+1]] == 0)){
                mp.erase(vec[r+1]);
                break;
            }
            r++;
            mp[vec[r]]++;
        }

        resp += r-l+1;

        mp[vec[l]]--;
        if(mp[vec[l]] == 0) mp.erase(vec[l]);
        l++;
    }
    
    cout << resp << ln;
    return 0;
}