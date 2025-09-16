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

v64 div(ll n){
    v64 resp;
    for(ll i = 1; i*i <= n; i++){
        if(i*i == n){
            resp.push_back(i);
            continue;
        }
        if(n%i == 0){
            resp.push_back(i);
            resp.push_back(n/i);
        }
    }
    return resp;
}

int main() {
    _;
    ll n;
    cin >> n;
    v64 vec(n);
    forn(i,0,n) cin >> vec[i];

    sort(vec.begin(), vec.end());

    if(vec[0] == vec[n-1]){
        cout << 1 << " " << 1'000'000'000-1 << ln;
        return 0;
    }

    if(vec[0]+1 == vec[n-1]){
        cout << 2 << " " << 1'000'000'000-1 << ln;
        return 0;
    }

    ll temp = vec[0];
    
    forn(i,0,n) vec[i] -= temp;
    ll d  = vec[0];
    
    forn(i,1,n){
        d = gcd(d, vec[i]);
    }

    if(d != 1){
        ll resp = (ll)div(d).size() - 1;
        cout << 1 << " " << resp << ln;
        return 0;
    }

    ll nonzero = 0;
    ll i = 1;
    while(nonzero == 0){
        nonzero = vec[i];
        i++;
    }

    v64 div1 = div(nonzero);
    v64 div2 = div(vec[n-1]);
    v64 div3 = div(vec[n-1]-nonzero);
    
    set<ll> test;
    
    for(ll x: div1) test.insert(x);
    for(ll x: div2) test.insert(x);
    for(ll x: div3) test.insert(x);

    ll ans = 0;

    for(ll m: test){
        set<ll> s;
        forn(i,0,n) s.insert(vec[i]%m);
        if((ll)s.size() == 2) ans++;
    }
 
    cout << 2 << " " << ans << ln;
    return 0;
}