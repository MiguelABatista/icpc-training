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

int main() {
    _; ll n; cin >> n;
    n--;
    vll div;
    ll d = 1;
    while(d*d <= n){
        if(n%d == 0){
            div.push_back(d);
            if(d*d < n) div.push_back(n/d);
        }
        d++;
    }

    sort(div.begin(), div.end());

    for(auto x : div) cout << x << " ";
    cout << ln;
     
    return 0;
}
