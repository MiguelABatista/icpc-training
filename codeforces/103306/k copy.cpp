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
const ll MAX = 1'000'005;


// Flattened Divisor Sieve (CSR format)
// Precomputes all divisors up to n. 
// Faster than vector<vll> for cache reasons 
// Time Complexity: O(n log n) | Space Complexity: O(n log n)

vector<vll> divs(MAX);
vll pot2(MAX);
void prep(){
    pot2[0] = 1;
    forn(i,1,MAX) pot2[i] = 2*(pot2[i-1])%MOD;
    forn(i,1,MAX){
        for(ll j = i; j < MAX; j += i){
            divs[j].push_back(i);
        }
    }
}

// for d | x =
// forn(k,head[x], tail[x]){
//     ll d = divs[k];
// }

int main() {
    _;
    prep();

    ll t; cin >> t;
    vll mem(MAX, -1);
    while(t--){
        ll n; cin >> n;
        ll resp = 0;
        for(ll d: divs[n]) resp += pot2[d];
        debug(resp);
        resp = (resp + MOD - pot2[n])%MOD;
        mem
        cout << resp << ln;   
    }
    return 0;
}
