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
#define debugm(v) trace(cout << #v ": "; for (auto xx : v) cout << xx.first << ":" << xx.second << " "; cout << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;

void solve(){
    ll n; cin >> n;
    vll vec(n);
    forn(i,0,n) cin >> vec[i];
    vll d(n-1);
    forn(i,0,n-1) d[i] = vec[i+1] - vec[i];

    ll p1 = 0;
    ll p2 = 0;
    debugv(d);
    while(p2 < n-1){
        trace(cout << p1 << " " << p2 << ln;)
        if((d[p2] - d[p1])%2 == 0){
            p2++; 
            continue;
        }
        trace(cout << p1 << "$" << p2 << ln;)
        sort(d.begin()+p1, d.begin()+p2);
        p1 = p2;
    }
    sort(d.begin()+p1, d.begin()+p2);

    forn(i,1,n){
        vec[i] = vec[i-1] + d[i-1];
    }
    forn(i,0,n) cout << vec[i] << " \n"[i==n-1];
}

int main() {
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}
