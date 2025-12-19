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
const ll MOD1 = 1'000'000'007;
const ll b1 = 19;
const ll invb1 = 157894738;
const ll MOD2 = 1'000'000'009;
const ll b2 = 31;
const ll invb2 = 838709685;

void solve(){
    ll n; cin >> n;
    string s; cin >> s;
    v64 hash1(n);
    v64 hash2(n);
    ll pot1 = 1;
    ll pot2 = 1;
    
    hash1[0] = s[0]-'a';
    hash2[0] = s[0]-'a';
    
    forn(i,1,n){
        pot1 = (pot1*b1)%MOD1;
        pot2 = (pot2*b2)%MOD2;
        hash1[i] = ((s[i]-'a')*pot1)%MOD1; 
        hash2[i] = ((s[i]-'a')*pot2)%MOD2; 
    }

    v64 cum1(n);
    v64 cum2(n);

    cum1[0] = hash1[0];
    cum2[0] = hash2[0];

    forn(i,1,n){
        cum1[i] = (cum1[i-1]+hash1[i])%MOD1;
        cum2[i] = (cum2[i-1]+hash2[i])%MOD2;
    }

    auto sum1 = [&](ll l, ll r){
        if(l > r) return 0ll;
        return (cum1[r] +  (MOD1 - (l == 0 ? 0 : cum1[l-1])))%MOD1;  
    };
    auto sum2 = [&](ll l, ll r){
        if(l > r) return 0ll;
        return (cum2[r] +  (MOD2 - (l == 0 ? 0 : cum2[l-1])))%MOD2;  
    };

    set<p64> resp;

    forn(i,0,n-1){
        ll h1 = 0;
        ll h2 = 0;
        debug(sum1(0, i-1));
        debug(sum1(i+2, n-1));
        h1 = (sum1(0, i-1) + (invb1*( (invb1*sum1(i+2, n-1))%MOD1 ))%MOD1)%MOD1;
        h2 = (sum2(0, i-1) + (invb2*( (invb2*sum2(i+2, n-1))%MOD2 ))%MOD2)%MOD2;
        resp.insert({h1,h2});
        debug(h1);
        debug(h2);
        debug(i);
        debug(sz(resp));
    }
    // cout << sz(resp) << " " << n-2 << ln;
    cout << sz(resp) << ln;
}

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}