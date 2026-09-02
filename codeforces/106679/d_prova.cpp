#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pll;
typedef vector<ll> vll;

#define forn(i,s,e) for(ll i=s; i<e; i++)
#define sz(u) ((ll) u.size())
#define ln "\n"

#ifdef DEBUG
#define trace(u) u
#define _
#else
#define trace(u)
#define _ ios::sync_with_stdio(0); cin.tie(0)
#endif

const ll INF = 0x3f3f3f3f3f3f3f3fll;

vector<string> transp(vector<string>& mat){
    ll n = sz(mat);
    ll m = sz(mat[0]);
    
    vector<string> resp(m, string(n, '#'));

    forn(i,0,n){
        forn(j,0,m){
            resp[j][i] = mat[i][j];
        }
    }
    return resp;
}

vector<string> flip(vector<string>& mat){
    ll n = sz(mat);
    ll m = sz(mat[0]);
    
    vector<string> resp(n, string(m, '#'));

    forn(i,0,n){
        forn(j,0,m){
            resp[i][j] = mat[n-i-1][j];
        }
    }
    return resp;
}

void print(vector<string>& mat){
    ll n = sz(mat);
    forn(i,0,n) cout << mat[i] << ln;
    cout << ln;
}

bool test(vector<string>& mat, vector<string>& mat2){
    ll n = sz(mat);
    ll m = sz(mat[0]);
    if(n != sz(mat2)) return false;
    if(m != sz(mat2[0])) return false;

    forn(i,0,n) forn(j,0,m) if(mat[i][j] != mat2[i][j]) return false;
    return true;
}

int main(){
    _;
    ll n, m; cin >> n >> m;

    vector<string> mat(n);
    forn(i,0,n) cin >> mat[i];

    vector<string> a = transp(mat);
    // print(a);
    vector<string> b = flip(mat);
    // print(b);
    vector<string> ba = flip(a);
    // print(ba);
    vector<string> ab = transp(b);
    // print(ab);
    vector<string> aba = transp(ba);
    // print(aba);
    vector<string> bab = flip(ab);
    // print(bab);
    vector<string> abab = transp(bab);
    // print(abab);
    
    ll resp = 1;
    resp += test(mat, a);
    resp += test(mat, b);
    resp += test(mat, ba);
    resp += test(mat, ab);
    resp += test(mat, aba);
    resp += test(mat, bab);
    resp += test(mat, abab);
    cout << resp << ln;
    return 0;   
}



// AC
// BD

// CD
// AB

// BD
// AC

// CA
// DB

// BA
// DC

// DB
// CA

// DC
// BA

// 1