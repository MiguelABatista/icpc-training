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


ll ask(ll a, ll b){
    cout << "? " << a << " " << b << endl;
    ll x; cin >> x;
    return x;
}

int main() {

    forn(b,2,26){
        ll x = ask(1,b);
        ll y = ask(b,1);
        if(x == -1){
            cout << "! " << b-1 << endl;
            return 0; 
        }
        if(x != y){
            cout << "! " << x+y << endl;
            return 0;
        }
    }

    return 0;
}
