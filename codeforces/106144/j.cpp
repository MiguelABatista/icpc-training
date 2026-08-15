#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pll;
typedef vector<ll> vll;

#define forn(i,s,e) for (ll i=(s); i<(e); i++)
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
#define debugv(v) trace(cout << #v ": "; for(auto xx : v) cout << xx << " "; cout << ln)


const ll INF = 0x3f3f3f3f3f3f3f3fll;

vll pot10 = {1};

ll logg10(ll n){
    ll resp = 0;
    while(pot10[resp] <= n) resp++;
    return resp;
}

ll shift(ll n, ll x){
    // debug(logg10(n/pot10[x]));
    // debug((n%pot10[x])*pot10[logg10(n/pot10[x])]);
    // debug(n/pot10[x]);
    return (n%pot10[x])*pot10[logg10(n/pot10[x])] + n/pot10[x];
}

void solve(){
    ll n; cin >> n;
    ll lim = logg10(n);
    vll resp;
    forn(i,1,lim){
        // debug(i);
        // debug(shift(n,i));
        if((shift(n,i) - n)%lim == i) resp.push_back(shift(n,i) - n);
    }

    sort(resp.begin(), resp.end());
    cout << sz(resp) << ln;
    forn(i,0,sz(resp)){
        cout << resp[i];
        if(i < sz(resp) - 1) cout << " ";
    }
    cout << ln;
}
 
int main(){
    _;
    forn(i,0,11) pot10.push_back(pot10.back()*10);

    ll t; cin >> t; 
    while(t--) solve();
    return 0;
}