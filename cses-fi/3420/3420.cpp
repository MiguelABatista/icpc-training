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
    v64 vec(n);
    forn(i,0,n) cin >> vec[i];

    ll p1 = 0;
    ll p2 = 0;
    ll resp = 0;
    set<ll> s;
    
    while(p1 < n){
        if(p2 == n || s.count(vec[p2])){
            s.erase(vec[p1]);
            resp += p2-p1;
            p1++;
            continue;
        }
        s.insert(vec[p2]);
        p2++;
    }
    
    cout << resp << ln;
    return 0;
}
