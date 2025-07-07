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
    _; ll r, c, k; cin >> r >> c >> k;

    bool works = true;

    string led, pat;
    forn(i, 0, r){
        cin >> led >> pat;
        bool broken_led = false, needs_led = false;
        for(auto s : led) if(s == '-') broken_led = true;
        for(auto s : pat) if(s == '*') needs_led = true;

        if(broken_led and needs_led) works = false;
    }

    if(works) cout << "Y" << ln;
    else cout << "N" << ln;

    return 0;
}