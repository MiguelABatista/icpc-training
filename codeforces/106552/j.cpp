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
const ll MAX = 30;
#define _
#else
#define trace(u)
const ll MAX = 1'000'005;
#define _ ios::sync_with_stdio(0); cin.tie(0)
#endif

#define debug(u) trace(cout << #u " = " << u << ln)
#define debugv(v) trace(cout << #v ": "; for (auto xx : v) cout << xx << " "; cout << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;

int main() {
    _;
    vll freq(MAX);
    vll resp(MAX);
    ll n; cin >> n;
    forn(i,0,n){
        ll x; cin >> x;
        freq[x]++;
    }

    forn(i,0,MAX) if(freq[i]){
        for(ll d = 1; d*d <= i; d++){
            if(i%d) continue;
            resp[d] += freq[i];
            if(d*d != i) resp[i/d] += freq[i];
        } 
    }
    debugv(freq);
    debugv(resp);
    ll ans = 0;
    forn(i,2,MAX){
        if(resp[i] > resp[ans]) ans = i;
    }

    cout << ans << ln;
    return 0;
}
