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
const ll MOD = 1'000'000'007;


int main() {
    _;
    vll pot2(64);
    pot2[0] = 1;
    forn(i,1,64) pot2[i] = (pot2[i-1]*2)%MOD;
    ll n; cin >> n;
    vll vec(n); 
    forn(i,0,n) cin >> vec[i];

    vll aux(64);
    forn(i,0,64){
        forn(j,0,n) aux[i] += !!(vec[j]&(1ll<<i));
    }
    debugv(aux);
    ll resp = 0;
    forn(i,0,64){
        resp = (resp + (pot2[i]*((aux[i]*(n-aux[i]))%MOD)))%MOD;
    }
    cout << resp%MOD << ln;
    return 0;
}
