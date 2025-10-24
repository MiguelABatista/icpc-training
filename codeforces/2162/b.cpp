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

bool test_valid(ll mask, string s, ll n){
    bool one = false;
    string s2;
    forn(i,0,n){
        if((mask & (1<<i)) == 0){
            s2.push_back(s[i]);
        };
        if(one){
            if(s[i] == '0') return false;
        }else{
            if(s[i] == '1') one = true;
        }
    }
    
    ll k = s2.size();
    if(k == 0) return false;
    debug(s2);
    forn(i,0,k/2){
        debug(s2[i]);
        debug(s2[k-i]);
        if(s2[i] != s2[k-i]) return false;
    }
    return true;
}



void solve(){
    ll n; cin >> n;
    string s; cin >> s;
    forn(mask, 0, 1<<n){
        bool b1 = test_valid(mask, s, n);
        if(b1){
            v64 resp;
            forn(i,0,n) if(mask & (1<<i)){
                resp.push_back(i);
            }
            cout << sz(resp) << ln;
            for(ll x: resp) cout << x+1 << " ";; cout << ln;
            return;
        }
    }   
    cout << 0 << ln << ln;
}

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}