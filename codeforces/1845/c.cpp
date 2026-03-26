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
    s.insert(s.begin(), '#');

    ll n = sz(s);
    ll m; cin >> m;
    string l; cin >> l;
    string r; cin >> r;

    vector<v64> next(n, v64(10, INF));

    for(ll i = n-2; i >= 0; i--){
        ll x = s[i+1] - '0';
        
        forn(j,0,10) next[i][j] = next[i+1][j]; 
        next[i][x] = i+1;
    }

    ll idxn = 0;

    forn(i,0,m){
        ll bestval = -1;

        forn(d, (l[i] - '0'), (r[i]-'0')+1){
            if(next[idxn][d] > bestval){
                bestval = next[idxn][d];
            }
        }

        if(bestval == INF){
            cout << "YES" << ln;
            return;
        }
        idxn = bestval;
    }
    cout << "NO" << ln;
}
int main() {
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}
