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
#define debugv(v) trace(cout << #v ": "; for (auto xx : v) cout << xx << " "; cout << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;
const ll MAX = 50;

vector<vll> esc(MAX+1, vll(MAX+1));

void prep(){
    forn(i,0,MAX+1) esc[i][0] = 1;
    forn(i,1,MAX+1){
        forn(j,1,MAX+1){
            esc[i][j] = esc[i-1][j] + esc[i-1][j-1];
        }
    }
    // trace(
    //     forn(i,0,MAX+1){
    //         cout << i << " : ";
    //         forn(j,0,MAX+1) cout << esc[i][j] << " ";
    //         cout << ln;
    //     }
    // )
}

ll sim(ll n, ll t){
    if(t%2 == 1 && n%2 == 0) return 0;
    return esc[n/2][t/2];
}

int main() {
    _;
    prep();
    ll n, k; cin >> n >> k;
    k = min(k,2*n-k);
    
    ll resp = 0;
    forn(t,0,k+1){
        ll x = esc[n][t] + sim(n, t);
        if(t == k/2 && k%2 == 0) resp += x;
        else resp += x/2; 
        debug(resp);
    }
    cout << resp << ln;

    return 0;
}
