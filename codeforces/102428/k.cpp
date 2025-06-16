#include <bits/stdc++.h>
using namespace std;

typedef __int128_t ll;
typedef pair<ll, ll> p64; 
typedef vector<ll> v64;
typedef complex<double> cd;

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
const int MAXD = 10010;
int main(){
    _;
    ll n; string s;
    cin >> s; n = s.size();

    vector<ll> root;
    ll sng = (s[0] == 'H' ? 1 : -1);

    forn(i,0,n-1){
        if(s[i] != s[i+1]){
            root.push_back(2*(i+1)+1);
        }
    }

    if(root.empty()){
        cout << 0 << ln;
        cout << (long long)sng << ln;
        return 0;
    }

    vector<__int128_t> resp(MAXD, 0);
    resp[0] = 1;

    // x3 + 2x2 - x + 6
    // 1 2 -1 6
    for(ll r: root){
        for(ll i = MAXD-1; i >= 1; i--){
            resp[i] -= r*resp[i-1]; 
        } 
    }

    bool should_flip = ((root.size() & 1) ? (s[0]=='H') : (s[0]=='A'));
    if (should_flip)
        for (auto &x : resp) x = -x;

    cout << root.size() << ln;
    forn(i,0,root.size()+1){
        cout << (long long)resp[i] << " ";
    }

    cout << ln;
    return 0;
}