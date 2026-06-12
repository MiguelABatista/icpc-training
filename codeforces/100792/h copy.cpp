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

int main() {
    _;
    ll n; cin >> n;
    vll vec(n);
    forn(i,0,n){
        string s; cin >> s;
        vec[i] = stoi(s, 0, 16);
    }

    vll nor(n), accnor(n);
    vll off(n), accoff(n+1);

    forn(i,0,n){
        nor[i] = vec[i]^i;
        off[i] = vec[i]^(i-1);
    }

    forn(i,0,n) accnor[i] = nor[i] + (i == 0 ? 0 : accnor[i-1]);
    for(ll i = n-1; i >= 0; i--) accoff[i] = off[i] + accoff[i+1];

    ll best = accnor[n-1];
    forn(i,0,n){
        ll curr = (i == 0 ? 0 : accnor[i-1]) + accoff[i+1];
        best = max(best, curr);
    }
    
    cout << best << ln;
    return 0;
}
