#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64;
typedef vector<ll> v64;

#define forn(i, s, e) for (ll i = (s); i < (e); i++)
#define ln "\n"

#if defined(DEBUG)
    #define _ (void) 0
    #define debug(x) cout << __LINE__ << ": " << #x << " = " << x << ln
#else
    #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
    #define debug(x) (void)0
#endif

const ll INF = 0x3f3f3f3f3f3f3f3fll;

void solve() {
    ll n, f; cin >> n >> f;
    vector<p64> pep(n);
    vector<p64> by_r(n);
    ll ans = 0;
    forn(i, 0, n) cin >> pep[i].first >> pep[i].second, ans += pep[i].second - pep[i].first;
    map<p64, ll> mp;
    forn(i, 0, n) mp[pep[i]] = i; 
    forn(i, 0, n) by_r[i].first = pep[i].second, by_r[i].second = i;
    sort(pep.begin(), pep.end());
    sort(by_r.rbegin(), by_r.rend());
    set<p64> open;

    v64 perm;
    set<ll> used;

    ll mx = -1, mxi = -1;
    ll i = 0;
    while (pep[i].first <= f && i < n) {
        if (pep[i].second > mx) {
            mx = pep[i].second;
            mxi = i;
        }
        i++;
    }

    if (mx > f) {
        perm.push_back(mp[pep[mxi]]);
        used.insert(mp[pep[mxi]]);
    }

    mx = max(f, mx);

    for(; i < n; i++) {
        if (pep[i].first > mx) {
            ans += pep[i].first - mx;
        }
        if (pep[i].second > mx) {
            mx = pep[i].second;
            mxi = i;
            perm.push_back(mp[pep[i]]);
            used.insert(mp[pep[i]]);
        }
    }

    forn(j, 0, n) {
        if (!used.count(by_r[j].second)) perm.push_back(by_r[j].second);
    }

    cout << ans << ln;
    forn(j, 0, n) cout << perm[j] + 1 << " \n"[j==n-1];
}

int main() {
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}