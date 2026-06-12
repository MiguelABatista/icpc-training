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
const ll MAX = 7;
#define _
#else
#define trace(u)
const ll MAX = 3005;
#define _ ios::sync_with_stdio(0); cin.tie(0)
#endif

#define debug(u) trace(cout << #u " = " << u << ln)
#define debugv(v) trace(cout << #v ": "; for (auto xx : v) cout << xx << " "; cout << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;

int main() {
    _;
    ll n; cin >> n;
    vector<bitset<MAX>> vec(n);
    // trace( forn(i,0,n) cout << vec[i] << ln;)
    forn(i,0,n){
        string s; cin >> s;
        forn(j,0,n){ 
            vec[i][j] = s[j] == '1';
        }
    }

    // trace( forn(i,0,n) cout << vec[i] << ln;)
    ll resp = 0;
    forn(i,0,n){
        forn(j,i+1,n){
            ll x = (vec[i]&vec[j]).count(); 
            trace(
                cout << i << " " << j << " " << x << ln;
                auto y = vec[i]&vec[j];
                debug(y);
            )
            resp += x*(x-1)/2;     
        }
    }
    cout << resp << ln;
    return 0;
}
