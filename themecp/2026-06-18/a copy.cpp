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

#define debug(u) trace(cout << __LINE__ << ": " #u " = " << u << ln)
#define debugv(v) trace(cout << #v ": "; for (auto xx : v) cout << xx << " "; cout << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;

void solve(){
    ll n; cin >> n;
    ll orign = n;
    vll resp;
    while(n>1){
        debug(n);
        vll divs;
        for(ll d = 1; d*d <= n; d++){
            if(n%d != 0) continue;
            divs.push_back(d);
            if(d*d != n) divs.push_back(n/d);
        }
        sort(divs.rbegin(), divs.rend());
        ll d = divs[1];
        resp.push_back(d);
        ll k = n/d;
        ll pot = 1;
        k--;
        n -= d;
        debug(pot);
        debug(k);
        debug(n);
        while(k > 0){
            while(2*pot < k && (k%(2*pot)) == 0) pot *= 2;
            if(pot == k) break;
            resp.push_back(pot*d);
            n -= pot*d;
            k -= pot;
            debug(pot);
            debug(k);
            debug(n);
        }
        trace(cout<<"--------------\n\n";);
    }
    cout << sz(resp)+1 << ln;
    ll acc = 0;
    n = orign;
    forn(i,0,sz(resp)){
        cout << n - acc << " ";
        acc += resp[i];
    }
    cout << 1 << ln;
}

int main() {
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}
