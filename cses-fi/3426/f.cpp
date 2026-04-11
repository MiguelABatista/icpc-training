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
    vll acc(n+1); 
    acc[0] = 0;
    forn(i,0,n) cin >> vec[i];
    forn(i,1,n+1){
        acc[i] = acc[i-1]^vec[i-1];
    }
    
    vll aux(64);
    forn(i,0,64){
        forn(j,0,n+1) aux[i] += !!(acc[j]&(1ll<<i));
    }

    ll resp = 0;
    forn(i,0,64){
        resp += (1LL<<i)*aux[i]*(n+1-aux[i]);
    }

    debugv(aux);
    debugv(acc);

    forn(i,1,n+1) resp -= acc[i-1]^acc[i];
    cout << resp << ln;
    return 0;
}
