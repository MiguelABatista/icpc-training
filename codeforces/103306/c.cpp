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
    string s; cin >> s;
    ll accum = 0;
    ll min_acc = 0;
    ll best_id = 0;
    forn(i, 0, sz(s)){
        accum += (2*(s[i] == 'B') - 1);
        if(accum < min_acc){
            min_acc = accum;
            best_id = i+1;
        }
    } 

    cout << best_id << ln;

}

int main() {
    _;ll t; cin >> t;
    forn(i, 0, t) solve();
    return 0;
}
