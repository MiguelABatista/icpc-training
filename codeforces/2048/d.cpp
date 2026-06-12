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
    ll n, m; 
    cin >> n >> m;
    ll kevin = 0;
    vll a(n-1);
    vll b;
    ll facil = 0;
    cin >> kevin;
    
    forn(i,0,n-1) cin >> a[i];
    
    forn(i,0,m){
        ll x; cin >> x;
        if(x <= kevin) facil++;
        else b.push_back(x);
    }

    sort(a.begin(), a.end());
    sort(b.rbegin(), b.rend());

    forn(k,1,m+1){
        ll resp = m/k;
        ll off = k - (facil%k);
        ll idx = off - 1;
        while(idx < sz(b)){
            ll s = (ll)(a.end() - lower_bound(a.begin(), a.end(), b[idx]));
            resp += s;
            idx += k;
        }
        cout << resp << " ";
    }
    cout << ln;
}

int main() {
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}
