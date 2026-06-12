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

vll aux = {0,1,2,3,4,5,6,7,8,9,22,11};

void solve(){
    ll n; cin >> n;
    ll idx = n%12;
    ll a = aux[idx];
    ll b = n-a;
    if(b < 0){
        cout << -1 << ln;
        return;
    }
    cout << a << " " << b << ln;
    assert(b%12 == 0); 
}

int main() {
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}
