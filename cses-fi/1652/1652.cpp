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
    ll n, q; cin >> n >> q;
    vector<v64> mat(n, v64(n));
    forn(i,0,n){
        forn(j,0,n){
            char c; cin >> c;
            mat[i][j] = (c == '*');
        }
    }

    trace(forn(i,0,n){debugv(mat[i]);} cout << ln;);
    forn(j,1,n) mat[0][j] += mat[0][j-1];
    forn(i,1,n) mat[i][0] += mat[i-1][0];

    forn(i,1,n){
        forn(j,1,n){
            mat[i][j] += mat[i-1][j] + mat[i][j-1] - mat[i-1][j-1];
        }
    }

    trace(forn(i,0,n){debugv(mat[i]);});
    
    while(q--){
        ll a, b, x, y;
        cin >> a >> b >> x >> y;
        a--,b--,x--,y--;
        ll resp = mat[x][y];
        if(a > 0) resp -= mat[a-1][y];
        if(b > 0) resp -= mat[x][b-1];
        if(a*b > 0) resp += mat[a-1][b-1];
        cout << resp << ln;
    }
    return 0;
}
