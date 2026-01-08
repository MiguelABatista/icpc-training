#pragma GCC optimize("Ofast,fast-math,unroll-loops,inline")


#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64; 
typedef vector<ll> v64;

#define forn(i, s, e) for(ll i = (s); i < (e); i++)
#define sz(x) ((ll) x.size())
#define ln "\n"

#ifdef DEBUG
    #define trace(x) x
    #define _ (void)0
#else
    #define trace(x) (void)0
    #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
#endif

#define debugv(v) trace({cout << #v": "; for (auto x : v) cout<< x << " "; cout << ln;})
#define debug(x) trace(cout << __LINE__ << ": " #x " = " << x << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;

bool comp(string a, string b) {
    ll ia = sz(a)-1, ib = sz(b)-1;
    while (ia >= 0 && ib >= 0) {
        if (a[ia] < b[ib]) {
            return true;
        } else if (a[ia] > b[ib]) {
            return false;
        }
        ia--;
        ib--;
    }
    if (ia < 0) return true;
    return false;
}

bool valid(string temp, string b) {
    ll itemp = sz(temp)-1, ib = sz(b)-1;
    if (itemp < ib) return false;
    while (ib >= 0) {
        if (temp[itemp] != b[ib]) return false;
        itemp--;
        ib--;
    }
    return true;
}

void solve() {
    ll n, m; cin >> n >> m;
    string s; cin >> s;
    vector<string> v(m);
    forn(i, 0, m) cin >> v[i];
    sort(v.begin(), v.end(), comp);
    
    string temp = "";
    ll ans = 0;

    auto find = [&]() {
        ll l = 0, r = m-1;
        while (l <= r) {
            ll mid = (l + r) / 2;
            if (valid(temp, v[mid])) return true;

            if (comp(temp, v[mid])) {
                r = mid-1;
            } else {
                l = mid+1;
            }
        }
        return false;
    };

    forn(i, 0, n) {
        temp += s[i];
        if (find()) {
            ans++;
            temp = "";
        }
        debug(temp);
    }
    cout << ans << ln;
}

int main(){
    _;
    ll t; cin >> t;
    while (t--) solve();
    return 0;
}