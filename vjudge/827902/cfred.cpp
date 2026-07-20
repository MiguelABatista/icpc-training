#include <bits/stdc++.h>
using namespace std;

typedef long long ll ; 
typedef vector<ll> vll ; 
typedef pair<ll,ll> pll ;

#define forn(i,s,e) for(ll i = (s) ; i<(e) ; i++)
#define sz(u) ((ll)u.size())
#define ln '\n'

#ifdef DEBUG  
#define trace(u) u 
#define _
#else 
#define trace(u) 
#define _ ios::sync_with_stdio(0);cin.tie(0);
#endif

const ll INF = 0x3f3f3f3f3f3f3ffll ;

pair<ll,vll> hungarian(const vector<vll> &a) {
    if (a.empty()) return {0,{}};
    ll n  = sz(a)+1 , m = sz(a[0])+1;
    vll u(n) ,v(m) , p(m) , ans(n-1);
    forn(i,1,n) {
        p[0] = i ;
        ll j0 = 0 ;
        vll dist (m,INF) , pre(m,-1);
        vector<bool> done(m+1);
        do {
            done[j0] = true ; 
            ll i0 = p[j0] , j1 = 0 ,delta=INF;
            forn(j,1,m) if (!done[j]) {
                auto cur = a[i0-1][j-1]-u[i0]-v[j];
                if (cur < dist[j]) dist[j] = cur , pre[j] = j0 ;
                if (dist[j] < delta) delta = dist[j],j1=j;
            }
            forn(j,0,m) {
                if (done[j]) u[p[j]] +=delta,v[j]-=delta;
                else dist[j]-=delta;
            }
            j0 = j1 ;
        }
        while (p[j0]);
        while(j0) {
            ll j1 = pre[j0];
            p[j0] = p[j1] , j0=j1;
        }

    }
    forn(j,1,m) if (p[j]) ans[p[j]-1] = j-1;
    return {-v[0],ans};
}

int main () {
    _;
    ll n ; cin >> n ;
    vector<vll> a (n,vll(n));
    forn(i,0,n)
        forn(j,0,n)
            cin >> a[i][j];
    auto [val,ans] = hungarian(a);
    cout << val << ln;
    forn(i,0,n) {
        cout << i+1 << " " << ans[i]+1  <<ln;
    }
    return 0 ;
}