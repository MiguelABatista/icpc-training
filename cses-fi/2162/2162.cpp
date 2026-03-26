#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64;
typedef vector<ll> v64;

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
    
    v64 nxt(n);
    
    forn(i,0,n) nxt[i] = i+1;
    nxt[n-1] = 0;
    v64 out(n);
    v64 resp;

    ll curr = 0;
    forn(i,0,n){
        ll prox = nxt[curr];
        resp.push_back(prox);
        out[prox] = 1;
        nxt[curr] = nxt[prox];
        curr = nxt[prox]; 
    }

    forn(i,0,n) cout << resp[i]+1 << " \n"[i==n-1];
    return 0;
}
