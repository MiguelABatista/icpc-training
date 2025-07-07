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
    ll n; ll k;
    cin >> n >> k;
    v64 perm(n);
    vector<bool> visitados(n, false);
    vector<ll> dp(n+1,0);

    forn(i,0,n){
        cin >> perm[i];
        perm[i]--;
    }

    map<ll,ll> mp;
    ll cap = 0;
    forn(i,0,n){
        if(visitados[i]) continue;
        ll curr = i;
        ll sz = 0;
        while(visitados[curr] == false){
            sz++;
            visitados[curr] = true;
            curr = perm[curr];

        }
        mp[sz]++;
        cap += sz / 2;              
    }

    const ll LIM = 1'000'000;                 // we don't need sums > k
    bitset<1'000'000 + 1> bs;
    bs[0] = 1;

    for (auto [len, cnt] : mp) {
        for (ll take = 1; cnt; cnt -= take, take = min((take << 1), cnt)) {
            ll shift = len * take;
            if(shift > LIM) shift = LIM + 1;          
            else bs |= (bs << shift);
        }
    }

    bool reachable = bs[k];

    ll ans = k;
    if(!reachable) ans++;
    ll ans_max;
    if (k <= cap) ans_max = 2 * k;
    else ans_max = min(n, k + cap);

    cout << ans << " " << ans_max << ln; 
    return 0;
}