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
    ll n, m, k; 
    cin >> n >> m >> k;

    v64 pess(n);
    v64 apar(m);
    forn(i,0,n) cin >> pess[i];
    forn(i,0,m) cin >> apar[i];

    sort(pess.begin(), pess.end());
    sort(apar.begin(), apar.end());

    auto left = apar.begin();
    ll resp = 0;

    forn(i,0,n){
        auto curr_it = lower_bound(left, apar.end(), pess[i]-k);
        if(curr_it == apar.end()) break;
        if(*curr_it <= pess[i]+k){
            resp++;
            left = curr_it;
            left++;
        }
    }
    cout << resp << ln;
    return 0;

}
