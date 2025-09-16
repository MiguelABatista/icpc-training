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
    _; ll n; cin >> n;
    ll s, k; cin >> s >> k;
    bool found = false;
    ll counter, a, b;
    vector<bool> bad(s, false);
    forn(i, 0, k) {cin >> a; bad[a-1] = true;}

    forn(i, 0, n){
        cin >> a;
        counter = 0;
        forn(j, 0, a){
            cin >> b;
            if(bad[b-1]) counter++;
            if(3*counter > a and !found){
                found = true;
                cout << i+1 << ln;
            }
        }
    }

    if(!found) cout << -1 << ln;
    return 0;
}