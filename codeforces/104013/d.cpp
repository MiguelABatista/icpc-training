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

 
int main() {
    _;
    ll n, w, h, s;
    cin >> n >> w >> h >> s;
    ll bst = 0;
    char c = 0;
    forn(xx,0,n){
        char cc; cin >> cc;
        vector<vector<char>> m(h,vector<char>(w));
        forn(i,0,h) forn(j,0,w) cin >> m[i][j];

        // forn(i,0,h){ debugv(m[i]);};
        ll cnt = 0;
        char curr = '.';
        
        forn(i,0,h){
            cnt = 0;
            forn(j,0,w){
                if(curr != m[i][j]) cnt++;
                curr = m[i][j];
            }
            if(curr != '.') cnt++;
            curr = '.';
            if(cnt > bst){
                bst = cnt;
                c = cc;
            }
        }
        
    }
    debug(bst);
    ll v = (s+bst-1)/bst;
    forn(i,0,v) cout << c;
    cout << ln;
    return 0;
}
 