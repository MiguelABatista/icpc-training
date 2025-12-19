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
    v64 vec(n);
    ll pos1 = -1;
    ll posn = -1;
    forn(i,0,n){
        cin >> vec[i];
        if(vec[i] == 1) pos1 = i;
        if(vec[i] == n) posn = i;
    }

    string s; cin >> s;
    bool imp = false;
    if(s[0] == '1' || s[n-1] == '1') imp = true;
    if(s[pos1] == '1' || s[posn] == '1') imp = true;    
    
    if(imp){
        cout << -1 << ln;
        return;
    }

    debug(pos1);
    debug(posn);
    if((pos1 == 0) || (pos1 == n-1)){
        if((posn == 0) || (posn == n-1)){
            cout << 1 << ln;
            cout << 1 << " " << n << ln;
            return;
        }
        cout << 3 << ln;
        cout << 1 << " " << posn+1 << ln;
        cout << posn+1 << " " << n << ln;
        cout << 1 << " " << n << ln;
        return;
    }

    if((posn == 0) || (posn == n-1)){
        cout << 3 << ln;
        cout << 1 << " " << pos1+1 << ln;
        cout << pos1+1 << " " << n << ln;
        cout << 1 << " " << n << ln;
        return;
    }

     
    ll baixo = min(pos1, posn)+1;
    ll cima = max(pos1, posn)+1;
    
    cout << 5 << ln;
    cout << 1 << " " << baixo << ln;
    cout << 1 << " " << cima << ln;
    cout << baixo << " " << cima << ln;
    cout << baixo << " " << n << ln;
    cout << cima << " " << n << ln;
}

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}