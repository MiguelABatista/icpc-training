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
    string s1, s2;
    cin >> s1 >> s2;

    ll cnt1 = 0;
    ll cnt2 = 0;

    forn(i,0,n){
        if(s1[i] == '*'){
            cnt1++;
            if(s2[i] != '*'){
                cnt2++;
            }
        }
    }

    cout << fixed << setprecision(2) << ((double)cnt2)/((double)(cnt1)) << ln;
    return 0;
}