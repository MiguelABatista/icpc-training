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
    ll n, k; cin >> n >> k;
    v64 vec(n+1,0);
    v64 p(k);
    forn(i,0,k){
        cin >> p[i];
    }
    sort(p.begin(), p.end());

    vec[0] = 0;
    forn(i,0,n+1){
        if(vec[i] == 1) continue;
        forn(j,0,k){
            if(i+p[j] > n) continue;
            vec[i+p[j]] = 1;
        }
    }
    
    forn(i,1,n+1) cout << "LW"[vec[i]];
    cout << ln;
    return 0;
}
