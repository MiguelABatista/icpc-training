#include <bits/stdc++.h>
using namespace std;

typedef int ll;
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

// const ll INF = 0x3f3f3f3f3f3f3f3fll;

int main() {

    ll n; cin >> n;
    vll vec(n);
    forn(i,0,n) cin >> vec[i];

    vector dp(n, vll(n));
    
    forn(t,2,n){
        forn(l,0,n-t){
            ll r = l+t;
            trace(cout << l << " " << r << ln;)
            
            vll pos(n, -1);
            vll fila;
            forn(i,0,n){
                if(vec[i] >= l &&  vec[i] <= r){
                    pos[vec[i]] = sz(fila);
                    fila.push_back(0);
                }
            }

            debugv(fila);
            debugv(pos);
            
            ll ans = 0;
            forn(i,l,r+1){
                if(pos[i] > 0) ans += (fila[pos[i]-1] == 0 ? +1 : -1);
                if(pos[i] < t) ans += (fila[pos[i]+1] == 0 ? +1 : -1);
                fila[pos[i]] = 1;
                debug(t);
                debug(pos[i]);
                debug(i);

                debugv(fila);

                ll continha = 0;
                if(pos[i] > 0) continha -= (fila[pos[i]-1] == 0);
                if(pos[i] < t) continha -= (fila[pos[i]+1] == 0);
                if(pos[i] > 0 && pos[i] < t) continha += (fila[pos[i]-1] != fila[pos[i]+1]);
                debug(ans);
                debug(continha);
                if(i == l) dp[l][r] = max(dp[l][r], dp[l+1][r]);
                else if(i == r) dp[l][r] = max(dp[l][r], dp[l][r-1]);
                else {
                    debug(dp[l][i-1]);
                    debug(dp[i+1][r]);    
                    dp[l][r] = max(dp[l][r], dp[l][i-1] + ans+continha + dp[i+1][r]);
                }
            }
            trace(cout << "-------------\n\n";)
        }
    }

    forn(i,0,n){debugv(dp[i]);};
    cout << dp[0][n-1] << ln;

    return 0;
}