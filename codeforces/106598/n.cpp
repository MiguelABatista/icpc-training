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
    vll vec(n+2);
    ll best = 0 ;
    ll soma = 0 ;
    forn(i,0,n+2){
        cin >> vec[i];
        best = max(best, vec[i]);
        soma += vec[i];
    }
    ll s = best;
    ll m = soma - n*s;
    vll resp;
    bool skips = true;
    bool skipm = true;

    forn(i,0,n+2){
        if(skips && vec[i] == s) {
            skips = false;
            continue;
        }
        if(skipm && vec[i] == m){
            skipm = false;
            continue;
        }
        resp.push_back(s-vec[i]);
    }
    sort(resp.begin(), resp.end());
    cout << s << " " << m << ln;
    forn(i,0,n) cout << resp[i] << " \n"[i==n-1];
    
    return 0;
}
