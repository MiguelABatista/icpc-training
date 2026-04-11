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

inline ll tri(ll n){
    return (n*(n+1))/2;
}
int main() {
    _;
    ll n = 1'000'001;
    
    v64 vec(n+1, INF);
    vec[0] = 0;

    forn(i,0,n){
        if(n%10'000 == 0) cout << n << ln;
        forn(j,0,n){
            if(i + tri(j) > n) break;
            vec[i+tri(j)] = min(vec[i+tri(j)], vec[i]+1);
        }
    }

    ll b = 0;
    forn(i,0,n+1){
        b = max(b, vec[i]);
    }
    cout << b << ln;
    return 0;
}
