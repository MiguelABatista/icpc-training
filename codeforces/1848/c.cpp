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
    v64 a(n), b(n);
    forn(i,0,n) cin >> a[i];
    forn(i,0,n) cin >> b[i];
    
    vector<bool> to_ignore(n, false);

    forn(i,0,n){
        if(a[i]== 0 && b[i] == 0){
            to_ignore[i] = true;
            continue;
        }
        while(((a[i]&1) == 0) && ((b[i]&1) == 0)){
            a[i] /= 2;
            b[i] /= 2;
        }
    }
    
    ll first = -1;
    forn(i,0,n) if(!to_ignore[i]){
        first = i;
        break;
    }
    if(first == -1){
        cout << "YES" << ln;
        return;
    }

    ll inv = a[first]%2+2*(b[first]%2); // 1, 2, 3

    bool ok = true;
    forn(i,0,n){
        if(to_ignore[i]) continue;
        if(a[i]%2+2*(b[i]%2) != inv) ok = false;
    }

    if(ok){
        cout << "YES" << ln;
    }else{
        cout << "NO" << ln;
    }
    return;
}

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}

bool tenta(ll a, ll b){
    ll c;
    forn(i,0,1000){
        c = abs(a-b);
        a = b;
        b = c;
        if(a == 0) return true;
    }
    return false;
}

int main2(){
    ll n = 100;
    forn(i,0,n){
        forn(j,0,100){
            if(!tenta(i,j)) cout << i << " " << j << ln;
        }
    }
    return 0;
}