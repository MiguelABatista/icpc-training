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
    ll n;
    cin >> n;
    v64 vec(n);
    forn(i,0,n) cin >> vec[i];

    ll resp1 = 0;
    ll resp2 = 0;

    set<ll> s1, s2;

    forn(m,2,110){
        set<ll> s;
        forn(i,0,n) s.insert(vec[i]%m);
        if(s.size() == 1) resp1++, s1.insert(m);
        if(s.size() == 2) resp2++, s2.insert(m);
    }

    bool tudo1 = false;
    bool tudo2 = false;

    ll m = 1000;
    set<ll> s;
    forn(i,0,n) s.insert(vec[i]%m);
    if(s.size() == 1) tudo1 = true;
    if(s.size() == 2) tudo2 = true;
    

    if(tudo1){
        cout << 1 << " " << 1'000'000'000-1 << ln;
        return 0;
    }
    if(tudo2){
        cout << 2 << " " << 1'000'000'000-1 << ln;
        return 0;
    }

    if(resp1 > 0){
        cout << 1 << " " << resp1 << ln;
        // for(ll x: s1) cout << x << " ";; cout << ln;
        return 0;
    } 
 
    if(resp2 > 0){
        cout << 2 << " " << resp2 << ln;
        // for(ll x: s2) cout << x << " ";; cout << ln;
        return 0;
    }
    cout << 3 << " " << 0 << ln;

    return 0;
}