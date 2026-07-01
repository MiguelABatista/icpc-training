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
    ll n, k; cin >> n >> k;
    string s; cin >> s;
    debug(s);
    forn(i,0,n){
        debug(s);
        if(i+k >= n) break;
        if(s[i] == '1'){
            s[i] = '0';
            s[i+k] = (s[i+k] == '1' ? '0' : '1');
        }
    }
    bool ok = true;
    forn(i,0,n) if(s[i] == '1') ok = false;
    if(ok) cout << "YES" << ln;
    else cout << "NO" << ln;
}

int main() {
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}
