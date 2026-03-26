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
    ll n; cin >> n;
    
    vector<v64> mat(n, v64(n,-1));
    mat[0][0] = 0;

    forn(i,0,n){
        forn(j,0,n){
            set<ll> s;
            forn(k,0,2*n) s.insert(k); 
            
            forn(k,0,i){
                auto it = s.find(mat[k][j]);
                if(s.end() == it) continue;
                s.erase(it);
            }

            forn(k,0,j){
                auto it = s.find(mat[i][k]);
                if(s.end() == it) continue;
                s.erase(it);
            }

            mat[i][j] = *s.begin();
        }
    }

    forn(i,0,n){
        forn(j,0,n) cout << mat[i][j] << " \n"[j==n-1];
    }

    return 0;
}
