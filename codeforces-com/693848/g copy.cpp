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


int main() {
    _;
    ll n; cin >> n;
    vll pot(30);
    forn(i,0,30) pot[i] = 1<<i;

    vll vec(n+1);
    vec[0] = 0;
    
    forn(i,1,n){
        for(ll x : pot){
            if(x > i) break;
            if(vec[i-x] == 0) vec[i] = 1;
        }
    }
    forn(i,0,n) if(vec[i] == 0) cout << i << ln;
    return 0;
}
