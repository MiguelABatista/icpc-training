#include <bits/stdc++.h>
using namespace std;
    
typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> p64; 
typedef vector<ll> v64;
    
#define forn(i, s, e) for(ll i = (s); i < (e); i++)
#define ln "\n"
    
#if defined(DEBUG)
    #define _ (void)0
    #define debug(x) cout << __LINE__ << ": " << #x << " = " << x << ln
#else
    #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
    #define debug(x) (void)0
#endif
    
const ll INF = 0x3f3f3f3f3f3f3f3fll;
    
    
struct task{
    ll d, p, c, l, r;
    ld x;
};
    
ld conta(ld v, ll t, task tas) {
    t += tas.c;
    
    if (t > tas.d) return -INF;
    
    v += tas.p;
    
    ld bonus_prob = 0.0;
    
    if (t <= tas.l) {
        bonus_prob = 1.0;
    } else if (t <= tas.r) {
        bonus_prob = (tas.r - t) / ((ld)(tas.r - tas.l));
    } else {
        bonus_prob = 0.0;
    }
    
    ld expected_bonus = bonus_prob * tas.x;
    
    return v + expected_bonus;
}
    
int main(){
    _;
    ll n; cin >> n;
    
    vector<task> tasks(n);
    
    forn(i, 0, n){
        cin >> tasks[i].d >> tasks[i].p >> tasks[i].c;
        ll xl, xr; cin >> xl >> xr;
        ld x = (xl+xr)/((ld)2);
        tasks[i].x = x;
        cin >> tasks[i].l >> tasks[i].r;
    }
    
    ll pot2 = 1 << n;
    
    vector<ll> cost(pot2, 0);
    
    
    forn(mask, 1, pot2){
        forn(i,0,n){
            ll idx = 1 << i;
            
            if(!(idx & mask)) continue;
    
            cost[mask] = cost[mask ^ idx] + tasks[i].c;
            break;
        }
    }  
    
    vector<ld> dp(pot2, -1);
    
    dp[0] = 0;
    ld resp = 0;
    
    forn(mask, 1, pot2){
        forn(i,0,n){
            ll idx = 1 << i;
            if(!(idx & mask)) continue;
            dp[mask] = max(dp[mask], conta(dp[mask^idx], cost[mask^idx], tasks[i]));
            resp = max(resp,dp[mask]);
        }
    }  
    
    cout << fixed << setprecision(20) << resp << ln;
    return 0;
}