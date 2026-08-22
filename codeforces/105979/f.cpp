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
    _;
    ll n ; 
    cin >> n ;

    ll sum1 = 0 ; ll sum2 = 0;
    forn(i,0,n) {
        ll p , s ;
        cin >> p >> s; 
        sum1+=p;
        sum2+=s;
    }
    cout << abs(sum1-sum2) <<ln;


    return 0;
}
