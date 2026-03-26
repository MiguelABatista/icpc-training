#include <bits/stdc++.h>
#include <bits/stdc++.h>
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64;
typedef vector<ll> v64;
typedef vector<v64> Mat;

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
const ll MOD = 1'000'000'007;

Mat mult(Mat& m1, Mat& m2){
    ll n = sz(m1);
    Mat mat(n, v64(n));

    forn(i,0,n){
        forn(k,0,n){
            forn(j,0,n){
                mat[i][j] = (mat[i][j] + m1[i][k]*m2[k][j])%MOD;
            }
        }
    }

    return mat;
}


int main() {
    _;
    ll m, n; cin >> m >> n;
    v64 s(m);
    v64 l(m);
    forn(i,0,m) cin >> s[i];
    forn(i,0,m) cin >> l[i];

    Mat mat(2, v64(2));

    forn(i,0,m){
        mat[0][0] = (mat[0][0] + (s[i]+l[i])*s[i])%MOD;
        mat[0][1] = (mat[0][1] + (s[i]*s[i]))%MOD;
        mat[1][0] = (mat[1][0] + (s[i]+l[i])*l[i])%MOD;
        mat[1][1] = (mat[1][1] + (s[i]*l[i]))%MOD;
    }

    Mat prod = {{1,0}, {0,1}};
    Mat pot = mat;
    n--;
    while(n > 0){
        if(n%2 == 1) prod = mult(prod, pot);
        pot = mult(pot, pot);
        n /= 2;
    }

    Mat ini = {{s[0], 0}, {l[0], 0}};
    Mat sla = mult(prod, ini);

    ll resp = 0;    
    
    forn(j,0,m){
        ll curr = (sla[0][0]*(s[j]+l[j]) + sla[1][0]*s[j])%MOD; 
        resp = (resp + curr)%MOD;
    }

    cout << resp << ln;
    return 0;
}
