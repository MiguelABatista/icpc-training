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

vector<vector<ld>> dist(ll k, ll x, ll y){
    const ll n = 8;
    vector<vector<ld>> mat(n , vector<ld>(n,0));
    mat[x][y] = 1;
    forn(t,0,k){
        vector<vector<ld>> next_mat(n , vector<ld>(n,0));

        forn(i,0,n){
            forn(j,0,n){
                ll cnt = 0;
                if(i-1 >= 0) cnt++;
                if(j-1 >= 0) cnt++;
                if(i+1 <  n) cnt++;
                if(j+1 <  n) cnt++;
                
                if(i-1 >= 0) next_mat[i-1][j] += mat[i][j]/cnt;
                if(j-1 >= 0) next_mat[i][j-1] += mat[i][j]/cnt;
                if(i+1 <  n) next_mat[i+1][j] += mat[i][j]/cnt;
                if(j+1 <  n) next_mat[i][j+1] += mat[i][j]/cnt;
            }
        }
        swap(mat,next_mat);
    }
    return mat;
}

int main() {
    _;
    ll k; cin >> k;
    ll n = 8;

    vector<vector<vector<ld>>> lst(n*n);

    forn(i,0,n){
        forn(j,0,n){
            lst[i*8+j] = dist(k,i,j);
        }
    }

    ld resp = 0;
    // vector<vector<ld>> negprog(n,vector<ld>(n,1));

    forn(i,0,n){
        forn(j,0,n){
            ld aux = 1;
            forn(idx,0,n*n){
                aux *= (1-lst[idx][i][j]);
            }
            resp += aux;
        }
    }

    cout << fixed << setprecision(6) << resp << ln;
    return 0;
}
