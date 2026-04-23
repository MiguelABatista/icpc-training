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
    ll n; cin >> n;
    vll vec(n);
    forn(i,0,n) cin >> vec[i];
    vec.push_back(0);
    n++;
    sort(vec.begin(), vec.end());

    ll lb = 0;
    ll up = INF;
    
    forn(i,0,n-1){
        lb = max(lb, vec[i+1]-vec[i]);
        if(i+2<n) up = min(up, vec[i+2]-vec[i]);
    }
    if(up <= lb){
        cout << 0 << ln;
    }else{
        cout << lb << ln;
    }
    return 0;
}
