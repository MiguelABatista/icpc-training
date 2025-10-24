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
    ll n, m ,k; cin >> n >> m >> k;
    map<ll,ll> mp;
    forn(i,0,k){
        ll a, b;
        cin >> a >> b;
        mp[b]++;
    }

    if(m == 1){
        cout << "Yuyu" << ln;
        return; 
    }if(n == 1){
        if(mp[2]%2 == 1){
            cout << "Mimo" << ln;
        }else{
            cout << "Yuyu" << ln;
        }
        return;
    }
    bool has_odd = false;

    for(auto [key,v] : mp){
        if(key == 1) continue;
        if(v%2 == 1) has_odd = true;
    }

    if(has_odd){
        cout << "Mimo" << ln;
    }else{
        cout << "Yuyu" << ln;
    }
}
int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}