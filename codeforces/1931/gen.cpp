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

mt19937_64 rng((ll) chrono::steady_clock::now().time_since_epoch().count());

ll uniform(ll l, ll r){
	uniform_int_distribution<ll> uid(l, r);
	return uid(rng);
}


int main(){
    _;
    cout << 1 << ln;
    ll n = uniform(4,5);
    ll k = uniform(4,n);
    set<p64> s;
    forn(i,0,n) s.insert({uniform(0,100000), i+1});
    v64 gaba(n);
    ll cnt = 0;
    
    for(auto [p, v] : s) gaba[cnt++] = v;
    v64 truegaba = gaba;
    set<ll> s2;
    while(sz(s2) < k) s2.insert(uniform(1,n));
    cnt = 0;
    cout << n << " " << k << ln;
    ll a = uniform(0,n-1);
    ll b = a;
    while(abs(b-a) <= 1) b = uniform(0,n-1);

    for(ll val: s2){
        cout << val << " ";
        
        if(cnt&1){
            swap(gaba[a],gaba[b]);
        }
        cnt++;
        forn(i,0,n) if(gaba[i] != val) cout << gaba[i] << " ";
        cout << ln;
    }
    cout << ln;
    forn(i,0,n) cout << truegaba[i] << " ";; cout << ln;
    cout << a << " " << b << ln;
    return 0;
}