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
    ll tot = 0;
    forn(i,0,n){
        cin >> vec[i];
        tot += vec[i];
    }

    sort(vec.begin(), vec.end());

    ll pref = 0;

    // 1 3    6 7 9
    // 2*x - (1 + 3)
    // (6+7+9) - 3*x 
    // (i+1)*x - pref
    // (tot - pref) - (n-(i+1))*x
    // tot - (n-2*(i+1))*x
    
    ll resp = INF;

    // 1 2 2 3 5
    forn(i,0,n){
        pref += vec[i];
        if(n-2*(i+1) >= 0){
            resp = min(resp, tot - 2*pref - (n-2*(i+1))*vec[i+1]);
        }else{
            resp = min(resp, tot - 2*pref - (n-2*(i+1))*vec[i]);  
        }
        debug(resp);
    }

    cout << resp << ln;
    return 0;
}
