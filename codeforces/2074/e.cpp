#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64; 
typedef vector<ll> v64;

#define forn(i, s, e) for(ll i = (s); i < (e); i++)
#define ln "\n"

#if defined(DEBUG) || defined(debug)
    #define _ (void)0
    #define debug(x) cout << __LINE__ << ": " << #x << " = " << x << ln
#else
    #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
    #define debug(x) (void)0
#endif

mt19937_64 rng((ll) chrono::steady_clock::now().time_since_epoch().count());

ll uniform(ll l, ll r){
	uniform_int_distribution<ll> uid(l, r);
	return uid(rng);
}

const ll INF = 0x3f3f3f3f3f3f3f3fll;

ll interact(char c, ll i, ll j, ll k){
    cout << c << ' ' << i << ' ' << j << ' ' << k << ln;
    cout.flush();
    if(c == '!') return 0;
    ll resp;
    cin >> resp;
    return resp;
}

void solve(){
    ll n; cin >> n;
    ll a, b, c, x;

    a = uniform(1,n);
    b = a;
    c = a;

    while(b == a) b = uniform(1,n);
    while((c == a) || (c == b)) c = uniform(1,n);
    
    x = interact('?', a, b, c);

    if(x == 0){
        interact('!', a, b, c);
        return;
    }

    forn(h,0,75){
        ll respa, respb, respc;
        
        respa = interact('?', x, b, c);
        respb = interact('?', a, x, c);
        respc = interact('?', a, b, x); 

        if(respa == 0){
            interact('!', x, b, c);
            return;
        }
        if(respb == 0){
            interact('!', a, x, c);
            return;
        }
        if(respc == 0){
            interact('!', a, b, x);
            return;
        }

        ll escolha = uniform(0,2); 
        
        if(escolha == 0){
            a = x;
            x = respa;
        }
        if(escolha == 1){
            b = x;
            x = respb;
        }
        if(escolha == 2){
            c = x;
            x = respc;
        }
    }   
    assert(false);
}

int main(){
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}