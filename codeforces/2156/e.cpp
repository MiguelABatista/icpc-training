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

ll ask(ll i, ll x){
    cout << "? " << i << " " << x << ln;
    ll ans;
    cin >> ans;
    return ans; 
}

void solve(){
    ll n; cin >> n;
    ll pot = 1;
    while(2*pot <= n) pot *= 2;

    set<ll> options;
    forn(i, 1, n) options.insert(i);

    ll l = 1, r = n, counter = 0;
    while(pot >= 1){
        debug(l);
        debug(r);

        ll expected = (r-l+1) - pot; // expected number of guys in options1
        if(l == 1) expected++; 

        if(expected <= 0){
            pot /= 2;
            continue;
        }
        set<ll> options0, options1;

        for(auto x : options){
            counter ++;
            ll on = ask(x, pot);
            if(on == 1) options1.insert(x);
            if(on == 0) options0.insert(x);
        }


        if(options1.size() < expected){
            l = r - expected + 1;
            swap(options, options1);
        }
        else{
            r = r - expected;
            swap(options, options0);
        }

        pot /= 2;
    }

    assert(counter <= 2*n);
    cout << "! " << l << ln; 
}

int main(){
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}