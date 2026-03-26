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
    ll n, x, k; cin >> n >> x >> k;
    v64 vec(n);
    forn(i,0,n) cin >> vec[i];

    vector<bool> used(n, false);

    set<p64> s;
    ll resp = 0;
    ll p1 = 0;
    ll p2 = 0;

    while(p2 < n){
        while (p1 < n && p1 <= p2 + k){
            s.insert({vec[p1], p1});
            debug(p1);
            p1++;
        }
        if((p2+1)%(x+1) == 0){
            auto it = prev(s.end());
            auto [v, idx] = *it;
            s.erase(it);
            used[idx] = 1;
            debug(p2);
            resp += v/2;
        }else{
            auto it = s.begin();
            auto [v, idx] = *it;
            debug(p2);
            s.erase(it);
            used[idx] = 1;
        }
        p2++;
    }

    cout << resp << ln;
    return 0;
}
