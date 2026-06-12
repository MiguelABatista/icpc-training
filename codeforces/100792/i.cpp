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
ll MAX = 3000;
const ll BOUND = 1826;


int main() {
    _;
    ll n; cin >> n;

    vll act(MAX);

    forn(xxxx,0,n){
        ll a, d;
        cin >> a >> d;
        forn(i,a,d+1) act[i] = 1;
    }

    vll acc(MAX);
    forn(i,1,MAX) acc[i] =  act[i] + acc[i-1];

    trace(
        forn(i,0,200){
            cout << i << " " << act[i] << " " << acc[i] << ln;
        }
    )

    ll k = 180;
    
    forn(i,k,MAX){
        ll s = acc[i] - acc[i-k]; 
        if(s > 90){
            debug(i);
            debug(s);
            cout << "No" << ln;
            return 0;
        }
    }

    forn(i,BOUND+1, MAX) if(act[i]){
        cout << "No" << ln;
        return 0;
    } 

    cout << "Yes" << ln;
    return 0;
}
