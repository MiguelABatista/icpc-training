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

void solve(){
    ll n; cin >> n;

    set<ll> s;
    v64 resp(n);
    forn(i,0,n) s.insert(i+1);
    
    if(n == 6){
        cout << 7 << ln;
        cout << "1 2 4 6 5 3" << ln;
        return; 
    }

    if(n%2 == 1){
        s.erase(1);
        s.erase(3);
        s.erase(n-1);
        s.erase(n);
        ll cnt = 0;
        for(ll x: s) resp[cnt++] = x;
        resp[cnt++] = 1; 
        resp[cnt++] = 3;
        resp[cnt++] = n-1;
        resp[cnt++] = n;
    }else{
        ll pot2 = 1;
        while(pot2*2 <= n) pot2 *= 2;
        s.erase(1);
        s.erase(3);
        s.erase(pot2-2);
        s.erase(pot2-1);
        s.erase(pot2);
        ll cnt = 0;
        for(ll x: s) resp[cnt++] = x;
        debug(cnt);
        resp[cnt++] = 1;
        resp[cnt++] = 3;
        resp[cnt++] = pot2-2;
        resp[cnt++] = pot2-1;
        debug(cnt);
        resp[cnt++] = pot2;
    }

    ll ans = 0;
    forn(i,0,n){
        if((i+1)&1){
            ans = ans&resp[i];
        }else{
            ans = ans|resp[i];
        }
    }
    cout << ans << ln;
    forn(i,0,n) cout << resp[i] << " ";; cout << ln;

}

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}