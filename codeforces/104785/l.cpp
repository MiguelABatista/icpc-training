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
    _; ll v1, d1, t1, v2, d2, t2; cin >> v1 >> d1 >> t1 >> v2 >> d2 >> t2;
    bool dead1 = false, dead2 = false;

    ll t = 0;
    while(!dead1 and !dead2){
        if(t%t1 == 0) v2 -= d1;
        if(t%t2 == 0) v1 -= d2;

        if(v2 <= 0) dead2 = true;
        if(v1 <= 0) dead1 = true;

        t++;
    }

    if(dead1 and dead2) cout << "draw" << ln;
    else if(dead1) cout << "player two" << ln;
    else if(dead2) cout << "player one" << ln;
    
    return 0;
}