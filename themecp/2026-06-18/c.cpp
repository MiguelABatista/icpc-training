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

ll n, m;

void sl(vector<vll>& mat, ll x, ll y){
    if(x == y) return;
    forn(i,0,m) swap(mat[x][i], mat[y][i]);
}

void sc(vector<vll>& mat, ll x, ll y){
    if(x == y) return;
    forn(i,0,n) swap(mat[i][x], mat[i][y]);
}

void print(vector<vll>& mat){
    forn(i,0,n) forn(j,0,m) cout << mat[i][j] << " \n"[j==m-1]; 
}

void ajeita(vector<vll>& mat){
    trace(
        print(mat);
        cout << ln;
    );
    
    ll x1 = -1;
    ll y1 = -1;
    forn(i,0,n){
        forn(j,0,m){
            if(mat[i][j] == 1){
                x1 = i;
                y1 = j;
                break;
            }
        }
        if(x1 != -1) break;
    }
    sl(mat, 0,x1);
    sc(mat, 0,y1);
    trace(
        print(mat);
        cout << ln;
    );
    vll lin(m);
    map<ll,ll> invlin;
    forn(i,0,m){
        lin[i] = mat[0][i];
        invlin[mat[0][i]] = i;
    }

    sort(lin.begin(), lin.end());
    
    forn(i,0,m){
        if(invlin[lin[i]] == i) continue;
        ll x = i;
        ll y = invlin[lin[i]];
        sc(mat, x, y);
        invlin[mat[0][x]] = x;
        invlin[mat[0][y]] = y;
    }

    vll col(n);
    map<ll,ll> invcol;
    forn(i,0,n){
        col[i] = mat[i][0];
        invcol[mat[i][0]] = i;
    }
    sort(col.begin(), col.end());

    forn(i,0,n){
        if(invcol[col[i]] == i) continue;
        ll x = i;
        ll y = invcol[col[i]];
        sl(mat, x, y);
        invcol[mat[x][0]] = x;
        invcol[mat[y][0]] = y;
    }

    trace(
        print(mat);
        cout << ln << ln;
    )
}

void solve(){
    cin >> n >> m;
    vector<vll> mat1(n, vll(m));
    vector<vll> mat2(n, vll(m));
    forn(i,0,n) forn(j,0,m) cin >> mat1[i][j];
    forn(i,0,n) forn(j,0,m) cin >> mat2[i][j];
    ajeita(mat1);
    ajeita(mat2);

    forn(i,0,n){
        forn(j,0,m){
            if(mat1[i][j] != mat2[i][j]){
                cout << "NO" << ln;
                return;
            }
        }
    }
    cout << "YES" << ln;
    trace(cout << "---------------------\n\n");
}

int main() {
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}
