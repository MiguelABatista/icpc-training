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
    v64 l(n, -INF);
    forn(i,0,n) cin >> vec[i];

    stack<p64> st;

    forn(i,0,n){
        debug(i);
        while(!st.empty() && st.top().first >= vec[i]){
            debug(st.top().first);
            debug(st.top().second);
            st.pop();
        }
        debug(st.empty());
        if(st.empty()) l[i] = 0;
        else l[i] = st.top().second + 1;
        st.push({vec[i],i});
    }
 
    forn(i,0,n) cout << l[i] << " \n"[i==n-1];
    return 0;
}
