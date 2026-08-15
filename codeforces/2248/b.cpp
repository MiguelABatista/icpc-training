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

void solve(){
    ll n, m; cin >> n >> m;
    vll a(n), b(m);

    forn(i,0,n) cin >> a[i];
    forn(i,0,m) cin >> b[i];

    if(n < 2*m){
        cout << "NO" << ln;
        return;
    }

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    vll menores(m);
    vll maiores(m);
    forn(i,0,m) menores[i] = a[i];
    forn(i,0,m) maiores[i] = a[n-m+i];
    debugv(a);
    debugv(menores);
    debugv(maiores);
    bool ok = true;
    forn(i,0,m){
        if(b[i] < menores[i]) ok = false;
        if(b[i] > maiores[i]) ok = false;
    }

    if(ok) cout << "YES" << ln;
    else cout << "NO" << ln;
}

int main() {
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}
