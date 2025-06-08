#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
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

int main(){
    _;
    ll n; cin >> n;
    ll q; cin >> q;
    
    vector<v64> anc(21, v64(n,-1));
    
    anc[0][0] = -1;

    forn(i,1,n){
        cin >> anc[0][i];
        anc[0][i]--;
    }

    ll idx = 1;
    for(ll pot2 = 2; pot2 <= n; pot2 *= 2){
        forn(j,0,n) anc[idx][j] = (anc[idx-1][j] == -1 ? -1 : anc[idx-1][anc[idx-1][j]]);
        idx++;
    }

    //forn(i,0,5) 
    //    forn(j,0,n)
    //        cout << anc[i][j] << " \n"[j==n-1]; 
    
    forn(i,0,q){
        ll x, k; cin >> x >> k;
        x--;
        idx = 19;
        ll pot2 = (1<<19);
        while(k > 0 && idx >= 0){
            if(pot2 <= k && anc[idx][x] != -1){
                debug(x);
                debug(k);
                debug(idx);
                debug(anc[idx][x]);
                x = anc[idx][x];
                k -= (1<<idx);
            }
            idx--;
            pot2 /= 2;
        }

        if(k > 0) cout << -1 << ln;
        else cout << x+1 << ln; 

    }
}