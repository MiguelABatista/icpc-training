#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;
typedef vector<ll> vll;

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

map<char,ll> m = {
    {'I', 1},
    {'V', 5},
    {'X', 10},
    {'L', 50},
    {'C', 100},
    {'D', 500},
    {'M', 1000},
};

int main() {
    _;
    ll t; cin >> t;
    while(t--) {
        string s; cin >> s;
        ll best=m[s[sz(s)-1]], resp=m[s[sz(s)-1]];
        for(ll i=sz(s)-2;i>=0;i--){
            if(m[s[i]]<best) resp-=m[s[i]];
            else resp+=m[s[i]];
            best=max(best,m[s[i]]);
        }
        cout << resp << ln;
    }
    return 0;
}
