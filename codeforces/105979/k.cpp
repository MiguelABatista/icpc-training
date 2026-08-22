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

    ll n,m;
    cin >> n >> m;

    vll left (n);
    vll right (n);


    forn(i,0,n)
        cin >> right[i];
    forn(i,0,n) 
        cin >> left[i];
    


    sort(left.begin(),left.end());
    sort(right.begin(),right.end());

    reverse(left.begin(),left.end());
    reverse(right.begin(),right.end());

    ll pairs = 0 ;

    while (m >= left[sz(left)-1] + right[sz(left)-1]) {
        m -= (left[sz(left)-1] + right[sz(left)-1]) ; 
        left.pop_back();right.pop_back();
        pairs++;
    }

    cout << pairs << ln;
    return 0;
}
