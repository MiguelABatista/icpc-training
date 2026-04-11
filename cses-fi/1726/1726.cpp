#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
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
    ll k; cin >> k;
    ll n = 8;
    vector<vector<vector<vector<ld>>>> tab(2, 
        vector<vector<vector<ld>>>(n, vector<vector<ld>>(n, vector<ld>(n*n)))
    );
    ll idx = 0;
    forn(i,0,n){
        forn(j,0,n){
            tab[idx][i][j][1] = 1;
        }
    }

    forn(iii,0,k){
        forn(i,0,n){
            forn(j,0,n){
                forn(t,0,n*n){
                    if(i > 0)
                }
            }
        }
    }
    return 0;
}
