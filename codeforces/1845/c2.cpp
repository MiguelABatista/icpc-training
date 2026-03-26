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

void solve(){
    string s; cin >> s;
    ll n = sz(s);
    ll m; cin >> m;
    string l; cin >> l;
    string r; cin >> r;

    ll lim = 1<<m;
    forn(mask, 0, lim){
        string tenta(m, ' ');

        forn(i,0,m){
            if(mask&(1<<i)) tenta[i] = l[i];
            else tenta[i] = r[i];
        }

        ll idxm = 0;
        ll idxn = 0;
        while(idxm < m && idxn < n){
            if(s[idxn] == tenta[idxm]) idxm++;
            idxn++;
        }
        if(idxm == m) continue;
        cout << "YES" << ln;
        return;
    }
    cout << "NO" << ln;
    trace(cout << "----------------\n\n");
}
int main() {
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}
