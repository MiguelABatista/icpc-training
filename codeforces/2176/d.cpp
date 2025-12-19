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
#define debugp(v) trace({cout << #v": "; for (auto f : v) cout<< f.first << ":" << f.second << " "; cout << ln;})
#define debug(x) trace(cout << __LINE__ << ": " #x " = " << x << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;
const ll MOD = 998244353;
const ll LOG = 60;

void solve(){
    ll n, m; cin >> n >> m;
    v64 vec(n);

    
    forn(i,0,n) cin >> vec[i];
    
    
	set<pair<p64,p64>> ed;
    forn(i,0,m){
        ll a, b; cin >> a >> b;
        a--, b--;
		ed.insert({{vec[b],vec[a]},{b,a}});
	}

    vector<map<ll,ll>> mapa(n);

    for(auto [p1, p2] : ed){
		auto [y,x] = p1;
		auto [b,a] = p2;
		mapa[b][x] = (mapa[b][x]+mapa[a][y-x]+1)%MOD;
    }

    ll resp = 0;

    forn(i,0,n){
        for(auto [k,v] : mapa[i]) resp = (v + resp)%MOD;
    }

    cout << resp << ln;
    
	trace(cout << "--------------\n\n";);
}

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}