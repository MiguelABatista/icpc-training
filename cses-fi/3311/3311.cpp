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

    ll n, m; cin >> n >> m;
    vector<string> mat(n);
    forn(i,0,n) cin >> mat[i];

    forn(i,0,n){
        forn(j,0,m){
            if((i+j) % 2 == 0){
                if(mat[i][j] == 'A') mat[i][j] = 'B';
                else mat[i][j] = 'A';
            }else{
                if(mat[i][j] == 'C') mat[i][j] = 'D';
                else mat[i][j] = 'C';
            }
        }
    }

    forn(i,0,n) cout << mat[i] << ln;
    return 0;
}
