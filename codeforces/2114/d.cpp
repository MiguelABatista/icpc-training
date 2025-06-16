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

ll area(multiset<ll>& setx, multiset<ll>& sety, ll n){
    if(n == 0) return 1;

    ll lx = *(--setx.end()) - *setx.begin() + 1;
    ll ly = *(--sety.end()) - *sety.begin() + 1;

    ll s = lx*ly;

    if(s == n){
        s = (max(lx,ly)+1)*min(lx,ly);
    }

    return s;
}

void solve(){
    ll n; cin >> n;
    multiset<ll> setx;
    multiset<ll> sety;
    vector<p64> monster(n);
    
    forn(i,0,n){
        ll x, y;
        cin >> x >> y;
        monster[i] = {x,y};
        setx.insert(x);
        sety.insert(y);
    }

    ll min_area = area(setx, sety, INF);

    forn(i,0,n){
        setx.erase(setx.find(monster[i].first));
        sety.erase(sety.find(monster[i].second));

        ll s = area(setx, sety, n-1);
        min_area = min(min_area, s);

        setx.insert(monster[i].first);
        sety.insert(monster[i].second);
    }

    cout << min_area << ln;
}

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}