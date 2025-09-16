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

int main() {
    _;
    ll n; cin >> n;

    vector<p64> vec(n);
    
    forn(i,0,n) cin >> vec[i].first >> vec[i].second;

    ll a1, a2, d1, d2; 
    cin >> a1 >> d1 >> a2 >> d2;

    map<p64, ll> mp;
    mp[{0,0}] = 1;
    vector<pair<p64, ll>> to_add;
    
    forn(i,0,n){
        for(auto [p, val] : mp){
            p64 newp = {p.first + vec[i].first, p.second+ vec[i].second};
            to_add.push_back({newp, val}) ;
        }

        for(auto [p2, val2] : to_add){
            mp[p2] += val2;
        }
        
        to_add.clear();
    }

    ll a1d1 = 0;
    ll a2d1 = 0;
    ll a1d2 = 0;
    ll a2d2 = 0;

    // cout << a1 << " " << a2 << ln;
    // cout << d1 << " " << d2 << ln;
    
    for(auto [p, val] :mp){
        // cout << p.first << " " << p.second << " : " << val << ln;
        if(p.first <= a2){
            if(p.second <= d2){
                a2d2 += val;
            }
            if(p.second < d1){
                a2d1 += val;
            }
        }
            if(p.first < a1){
            if(p.second <= d2){
                a1d2 += val;
            }
            if(p.second < d1){
                a1d1 += val;
            }
        }
    }

    cout << a2d2 - a1d2 - a2d1 + a1d1 << ln;
    return 0;
}