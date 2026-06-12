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
const ll MAX = 46;

vll fib(MAX);

bool rec(ll n, ll x, ll y){
    trace(
        cout << n << " " << x << " " << y << ln;
    )
    if(n == 0){
        if(x == 0 && y == 0) return true;
        return false;
    }

    ll f = fib[n];
    if(y >= f) return rec(n-1, y-f, x);
    if(y < fib[n+1] - f) return rec(n-1, y, x);
    return false;
}

void solve(){
    ll n, x, y;
    cin >> n >> x >> y;
    x--, y--;

    vector<string> aux = {"NO", "YES"};
    cout << aux[rec(n,x,y)] << ln;

    trace(cout << "------------------\n\n\n";)
}

int main() {
    _;
    fib[0] = 1;
    fib[1] = 1;
    forn(i,2,MAX) fib[i] = fib[i-1]+fib[i-2];

    ll t; cin >> t;
    while(t--) solve();
    return 0;
}
