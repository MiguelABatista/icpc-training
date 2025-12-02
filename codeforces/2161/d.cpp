#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64; 
typedef vector<ll> v64;

#define forn(i, s, e) for(ll i = (s); i < (e); i++)
#define sz(x) ((ll) x.size())
#define ln "\n"

#ifdef DEBUG
    #define trace(x) x
    #define _ (void)0
#else
    #define trace(x) (void)0
    #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
#endif

#define debugv(v) trace({cout << #v": "; for (auto x : v) cout<< x << " "; cout << ln;})
#define debugm(v) trace({cout << #v": "; for (auto x : v) cout<< x.first << ":" << x.second << " "; cout << ln;})
#define debug(x) trace(cout << __LINE__ << ": " #x " = " << x << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;

ll f(vector<v64>& inv, ll val, ll idx){
    if(sz(inv[val]) == 0) return 0;
    auto it = lower_bound(inv[val].begin(), inv[val].end(), idx);
    return (ll)(it - inv[val].begin());
}

void solve(){
    ll n; cin >> n;
    v64 vec(n);
    vector<p64> aux(n);
    vector<v64> inv(n);
    forn(i,0,n){
        cin >> vec[i];
        vec[i]--;
        aux[i] = {vec[i], i};
        inv[vec[i]].push_back(i);
    }

    sort(aux.begin(), aux.end());

    v64 dp(n);
    v64 valores = {-2,-1};

    dp[0] = 1;
    ll lastlastval = -2;
    ll lastval = -1;
    ll currval = -1;
    currval = aux[0].second;
    debugm(aux);
    forn(i,1,n){
        dp[i] = dp[i-1];
        ll val = aux[i].second;
        if(val != currval){
            lastlastval = lastval;
            lastval = currval;
            currval = val;
        }
        if(lastval == currval-1){
            ll possible = f(inv, lastval, i);
            ll xxx = 0;
            if(lastlastval >= 0) xxx = inv[lastlastval].back();
            if(lastlastval >= 0) possible += dp[xxx];
            dp[i]= max(dp[i], possible);
        }else{
            dp[i]++;
            continue;
        }
    }
    cout << n- dp[n-1] << ln;
}

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}