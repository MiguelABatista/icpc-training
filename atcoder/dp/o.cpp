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
    ll n; cin >> n;
    vector<vll> mat(n, vll(n));
    
    forn(i,0,n){
        forn(j,0,n) cin >> mat[i][j];
    }
    ll potn = 1<<n;
    vll dp(potn); // dada mask de mulheres quantas maneiras eu tenho de casar os k primeiros homens com essa mask;

    forn(mask,0,potn){
        ll k =  __builtin_popcountll(mask);
        if(k == 0){
            dp[mask] = 1;
            continue;
        }
        ll resp = 0;
        forn(i,0,n){
            if(mat[k-1][i] && (((1<<i)&mask) > 0)){
                resp = (resp+dp[mask^(1<<i)])%MOD;
            }
        }
        dp[mask] = resp;
    }

    cout << dp[potn-1] << ln;
    return 0;
}
