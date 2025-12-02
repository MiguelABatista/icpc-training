#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64; 
typedef vector<ll> v64;

#define forn(i, s, e) for(ll i = (s); i < (e); i++)
#define sz(x) ((ll) x.size())
#define ln "\n"

#ifdef DEBUG
    #define trace(x) x
    #define _ (void)0
#else
    #define trace(x) (void)0
    #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
#endif


#define debugv(v) trace({cout << #v": "; for (auto x : v) cout<< x << " "; cout << ln;})
#define debugm(v) trace({cout << #v": "; for (auto x : v) cout<< x.first << ":" << x.second << " "; cout << ln;})
#define debug(x) trace(cout << __LINE__ << ": " #x " = " << x << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;


int main(){
    _;
    ll n, m, c; cin >> n >> m >> c;
    ll tot = 0;
    map<ll,ll> mp;
    map<ll,ll> nxt;

    forn(i,0,n){
        ll p; cin >> p;
        mp[p]++;
        mp[p+m]++;
    }

    ll ant = -1;
    ll first = -1;

    for(auto [k,v] : mp){
        if(ant != -1){
            nxt[ant] = k;
        }else{
            first = k;
        }
        ant = k;
    }

    ll ans = 0;
    ll p1 = first;
    ll p2 = nxt[first];
    ll curr = 0; 

    while(p1 < m && p2 <= ant){
        if(curr >= c){
            ll nxtp = nxt[p1]; 
            debug(p1);
            debug(nxtp);
            debug(curr);
            debug(p2);
            debug(curr*(nxtp-p1));
            trace(cout << ln);
            ans += curr*(nxtp-p1);
            p1 = nxtp;
            curr -= mp[p1];
            continue;
        }
        curr += mp[p2];
        p2 = nxt[p2];
    }
    cout << ans << ln;
    return 0;
}