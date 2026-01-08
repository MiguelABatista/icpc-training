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
#define debug(x) trace(cout << __LINE__ << ": " #x " = " << x << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;
const ll MAXN = 200'005;

int main(){
    _;
    ll n; cin >> n;
    bitset<MAXN> target;
    gauss_z2<MAXN> gz;
    forn(i,0,n){
        ll b; cin >> b;
        if(!b) target[i] = true;
    }

    vector<v64> g(n);
    forn(i,0,n-1){
        ll a, b;
        cin >> a >> b;
        a--;
        b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    forn(i,0,n){
        bitset<MAXN> bs;
        bs[i] = true;
        for(ll x: g[i]) bs[x] = true;
        gz.add(bs);
    }

    bool resp = gz.add(target);
    if(resp) cout << "YES" << ln;
    if(resp) cout << "NO" << ln;
    return 0;
}