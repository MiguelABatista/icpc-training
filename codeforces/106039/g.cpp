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
    string s; cin >> s;

    v64 sum(n), cnt(n), nxt(n,INF);
    forn(i, 0, n) {
        if (i > 0) sum[i] = sum[i-1], cnt[i] = cnt[i-1];
        if (s[i] == '(') sum[i]++;
        else sum[i]--, cnt[i]++;
    }

    for (ll i = n-1; i >= 0; i--) {
        if (sum[i] == 0) nxt[i] = i;
        else nxt[i] = nxt[i+1];
    }

    ll resp = 0;
    
    forn(i,0,n){
        ll prox = nxt[i];
        if(s[i] == ')') continue;
        if(prox == INF) continue;
        resp += n/2 - cnt[prox] ; 
        // debug(i);
        // debug(prox);
        // debug((n/2 - cnt[prox]));
    }
    
    cout << resp << ln;
    return 0;
}