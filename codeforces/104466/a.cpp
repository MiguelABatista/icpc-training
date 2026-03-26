#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
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

// const ll INF = 0x3f3f3f3f3f3f3f3fll;
const ll INF = 999;
const ld ep = 0.000'000'001;
const ll LIM = 1'000'000'000;
const ld sq3 = sqrt(3.0L);
const ld sq62 = sqrt(6.0L) - sqrt(2.0L);

ll calc(ll a, char f){
    if(f == 'c'){
        return (ll)(a*sq3 + ep);
    }
    if(f == 't'){
        return a-1;
    }
    if(f == 's'){
        return (ll)(a*sq62 + ep);
    }
}

bool test_t(ll x){
    return x < LIM; 
}

bool test_c(ll x){
    ll guess = (ll)(x/sq3 + ep);

    forn(t,-20, 20){
        if(calc(guess+t, 'c') == x) return true;
    }
    return false;
}

bool test_c(ll x){
    ll guess = (ll)(x/sq62 + ep);

    forn(t,-20, 20){
        if(calc(guess+t, 'c') == x) return true;
    }
    return false;
}

int main(){
    _;

    ll n; cin >> n;    
    ll acc = 0;
    v64 nim(n);
    forn(i,0,n){
        string s;
        ll a;
        cin >> s >> a;
        nim[i] = calc(a, s[0]);
        acc ^= nim[i];
    }

    ll resp = 0;
    forn(i,0,n){
        ll aux = resp^nim[i];
        
    }
    return 0;
}