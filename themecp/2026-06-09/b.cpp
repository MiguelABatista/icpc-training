#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;
typedef vector<ll> vll;

#define forn(i, s, e) for (ll i = (s); i < (e); i++)
#define sz(u) ((ll) u.size())
#define ln "\n"

#ifdef DEBUG
#define trace(u) u
#define _
#else
#define trace(u)
#define _ ios::sync_with_stdio(0); cin.tie(0)
#endif

#define debug(u) trace(cout << #u " = " << u << ln)
#define debugv(v) trace(cout << #v ": "; for (auto xx : v) cout << setw(2) << xx << " "; cout << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;

void solve(){
    ll n; cin >> n;
    string s; cin >> s;
    vll vec(n);
    ll abre = 0;
    ll fecha = 0;
    forn(i,0,n){
        if(s[i] == '(') abre++;
        else fecha++;
        vec[i] = abre-fecha;
    }
    debug(abre);
    debug(fecha);
    if(abre != fecha){
        cout << -1 << ln;
        return;
    }

    bool pos = true;
    bool neg = true;
    forn(i,0,n){
        if(vec[i] > 0) neg = false;
        if(vec[i] < 0) pos = false;
    }

    if(neg || pos){ 
        cout << 1 << ln;
        forn(i,0,n) cout << 1 << " \n"[i==n-1];
        return;
    }

    cout << 2 << ln;
    debugv(vec);
    if(vec[0] < 0){
        forn(i,0,n) vec[i] *= -1;
    }
    debugv(vec);

    ll curr = 0;
    // 0 pos 1 neg
    cout << curr+1 << " ";
    forn(i,1,n){
        cout << curr+1 << " \n"[i==n-1];
        if(i == n-1) break;
        if(vec[i] == 0 && vec[i+1]*vec[i-1] < 0) curr ^= 1;
    }   
}

int main() {
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}
