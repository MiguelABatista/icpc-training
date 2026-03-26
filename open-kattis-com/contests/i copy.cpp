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
const ll N = 40;
const ll NA = 400;
const ll NAC = 2400;
bool pode[45][450][2500];

struct tripla{
    ll a, b, c;
    ll idx = -1;
    char ch = 'X';
    tripla(ll x, ll y, ll z) : a(x), b(y), c(z){};
    tripla(ll x, ll y, ll z, ll idx_, char ch_) : a(x), b(y), c(z), idx(idx_), ch(ch_){};
};

int main() {
    _;
    memset(pode, 1, sizeof(pode));
    ll n, k; cin >> n >> k;
    string s; cin >> s;
    string sorig = s;
    forn(i,0,n){
        if(s[i] == 'N') continue;
        if(s[i] == 'A') continue;
        if(s[i] == 'C') continue;
        if(s[i] == '?') continue;
        s[i] = 'X';
    }

    vector<vector<tripla>> reach(n+1);

    reach[0].push_back(tripla(0,0,0));
    
    forn(i,0,n){
        forn(j,0, sz(reach[i])){
            auto [a,b,c,idx, ch] = reach[i][j];
            if(c > k) continue;
            ll l = n-i;
            if((l*(l-1)*(l-2))/6 + a*(l*(l-1))/2 + b*l + c < k) continue;

            if(s[i] == 'N' || s[i]  == '?'){
                if(pode[a+1][b][c]){
                    pode[a+1][b][c] = 0;
                    reach[i+1].push_back({a+1,b,c,j,'N'});
                }
            }
            if(s[i] == 'A' || s[i]  == '?'){
                if(pode[a][b+a][c]){
                    pode[a][b+a][c] = 0;
                    reach[i+1].push_back({a,b+a,c,j,'A'});
                }
            }
            if(s[i] == 'C' || s[i]  == '?'){
                if(pode[a][b][c+b]){
                    pode[a][b][c+b] = 0;
                    reach[i+1].push_back({a,b,c+b,j,'C'});
                }
            }
            if(s[i] == 'X' || s[i]  == '?'){
                if(pode[a][b][c]){
                    pode[a][b][c] = 0;
                    reach[i+1].push_back({a,b,c,j,'X'});
                }
            }
        }
        for(auto [a,b,c,idx, ch] : reach[i+1]) pode[a][b][c] = 1;
    }
    
    tripla tri(-1,-1,-1);
    
    string r(n, '#');

    forn(i,0,sz(reach[n])){
        auto [a,b,c,idx, ch] = reach[n][i];
        if(c == k){
            tri = reach[n][i];
            break;
        }
    }

    if(tri.a == -1){
        cout << -1 << ln;
        return 0;
    }

    for(ll i = n; i > 0; i--){
        r[i-1] = tri.ch;
        auto& aux = reach[i-1];
        tri = aux[tri.idx];
    }

    forn(i,0,n) if(sorig[i] != '?') r[i] = sorig[i];
    cout << r << ln;
    return 0;
}
