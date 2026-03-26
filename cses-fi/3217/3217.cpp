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

p64 soma(p64 p1, p64 p2, ll n){
    p64 resp = {p1.first+p2.first, p1.second + p2.second};
    if(resp.first < 0 || resp.first >= n) return {-INF, -INF};
    if(resp.second < 0 || resp.second >= n) return {-INF, -INF};
    return resp;
}

int main() {
    _;

    ll n; cin >> n;

    vector<v64> mat(n, v64(n, INF));

    queue<p64> q;
    q.push({0,0});
    mat[0][0] = 0;

    vector<p64> moves = {
        {1,2},
        {1,-2},
        {-1,2},
        {-1,-2},
        {2,1},
        {2,-1},
        {-2,1},
        {-2,-1}
    };

    while(!q.empty()){
        auto [a,b] = q.front();
        q.pop();
        for(p64 mov : moves){
            p64 prox = soma(mov, {a,b}, n);
            if(prox.first == -INF) continue;
            if(mat[prox.first][prox.second] < INF) continue;
        
            mat[prox.first][prox.second] = mat[a][b] + 1;
            q.push(prox);
        }
    }

    forn(i,0,n){
        forn(j,0,n) cout << mat[i][j] << " \n"[j==n-1];
    }

    return 0;
}
