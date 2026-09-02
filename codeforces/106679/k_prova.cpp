#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pll;
typedef vector<ll> vll;

#define forn(i,s,e) for(ll i=s; i<e; i++)
#define sz(u) ((ll) u.size())
#define ln "\n"

#ifdef DEBUG
#define trace(u) u
#define _
#else
#define trace(u)
#define _ ios::sync_with_stdio(0); cin.tie(0)
#endif

const ll INF = 0x3f3f3f3f3f3f3f3fll;

int main(){
    _;
    ll n; cin >> n;
    vll c(n);
    vll k(n);

    forn(i,0,n) cin >> c[i];
    forn(i,0,n) cin >> k[i];

    ll tot = 0;
    forn(i,0,n) tot += c[i];

    ll menor = INF;
    forn(i,0,n){
        menor = min(menor, c[i]-k[i]);
    }

    if(menor < 0){
        cout << -1 << ln;
        return 0;
    }
    tot -= menor;
    cout << tot << ln;
    return 0;
}