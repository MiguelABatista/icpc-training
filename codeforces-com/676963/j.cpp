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
    ll p, d; cin >> p >> d;
    v64 freq(p), pile(p);
    
    forn(i,0,p) pile[i] = i;

    forn(xxx,0,d){
        ll val; cin >> val;
        vector<p64> curr;
        forn(i,0,val) curr.push_back({freq[pile[i]], pile[i]});

        sort(curr.begin(), curr.end());

        forn(i,0,val){
            pile[i] = curr[i].second;
            freq[pile[i]]++;
        }
    }

    ll resp = 0;
    forn(i,0,p) resp = max(resp, freq[i]);
    cout << resp << ln;
    return 0;
}
