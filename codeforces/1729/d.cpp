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

void solve(){
    ll n; cin >> n;
    vll vec(n);
    forn(i,0,n) cin >> vec[i];
    forn(i,0,n){
        ll y; cin >> y;
        vec[i] = y - vec[i];
    }
    sort(vec.begin(), vec.end());
    ll p1 = 0;
    ll p2 = n-1;
    ll resp = 0;
    while(p1 < p2){
        if(vec[p1] + vec[p2] >= 0){
            p1++;
            p2--;
            resp++;
        }else{
            p1++;
        }   
    }
    cout << resp << ln;
}

int main() {
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}
