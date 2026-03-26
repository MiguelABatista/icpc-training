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

    ll n = 8;
    vector<string> mat(n);
    forn(i,0,n) cin >> mat[i];

    v64 vec = {0,1,2,3,4,5,6,7};

    ll resp = 0;

    do{
        bool cont = false;
        forn(i,0,n) if(mat[i][vec[i]] == '*') cont = true;
        if(cont) continue;

        forn(i,0,n){
            forn(j,i+1,n){
                if(abs(vec[i]-vec[j]) == j-i) cont = true;
            }
        }

        if(cont) continue;

        trace(
            vector<string> p(n, string(n,'.'));
            forn(i,0,n) p[i][vec[i]] = '#';
            forn(i,0,n){
                forn(j,0,n) cout << p[i][j] << ",\n"[j == n-1];
            } 
            cout << ln;
            cout << "=,=,=,=,=,=,=,=" << ln;
            cout << ln;
        )

        resp++; 
    }while(next_permutation(vec.begin(), vec.end()));

    cout << resp << ln;
    return 0;
}
