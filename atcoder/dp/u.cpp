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
    vector<vll> mat(n, vll(n));
    forn(i,0,n) forn(j,0,n) cin >> mat[i][j];

    ll pot = 1<<n;
    vll dp(pot);
    vll soma(pot);
    
    forn(mask, 0, pot){
        forn(i,0,n) {
            if((mask&(1<<i)) == 0) continue;
            forn(j,0,i){
                if((mask&(1<<j)) == 0) continue;
                soma[mask] += mat[i][j];
            }
        }
    }

    forn(mask, 0, pot){
        for (ll submask = mask; submask > 0; submask = (submask - 1) & mask) {
            dp[mask] = max(dp[mask], dp[mask^submask] + soma[submask]);
        }
    }

    cout << dp[pot-1] << ln;
    return 0;
}
