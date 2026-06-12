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
const ll MAX = 100'005;

int main() {
    _;
    ll n, w; cin >> n >> w;
    vll peso(n);
    vll valor(n);
    forn(i,0,n) cin >>  peso[i] >> valor[i];
    vll dp(MAX, INF);
    dp[0] = 0;
    // obs1: ordem dos fores
    forn(t,0,n){
        for(ll i = MAX-1; i >= 0; i--){ // obs2: for de tras pra frente
            if(i+valor[t] < MAX) {
                dp[i+valor[t]] = min( // pega maximo
                    dp[i+valor[t]], dp[i] + peso[t]
                );
            } 
        }
    }
    ll resp = 0;
    forn(i,0,MAX) if(dp[i] <= w) resp = max(resp, i);
    cout << resp << ln;
    return 0;
}
