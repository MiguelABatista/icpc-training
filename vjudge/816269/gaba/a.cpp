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
const ll MAX = 1'000'005;

vll mem(MAX+1, INF);

ll rec(ll n){
    if(mem[n] != INF) return mem[n];
    ll aux = n;
    ll resp = INF;
    while(aux > 0){
        ll d = aux%10;
        aux /= 10;
        if(d == 0) continue;
        resp = min(resp, rec(n-d) + 1);
    }
    return mem[n] = resp;
}

int main() {
    // _;
    ll n; cin >> n;
    mem[0] = 0;
    forn(i,1,10) mem[i] = 1;
    
    cout << rec(n) << ln;

    return 0;
}
