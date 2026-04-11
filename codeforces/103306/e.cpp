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
    string s; cin >> s;
    ll c = 0;
    char cc = s.back();
    s.pop_back();
    debug(s);
    c = stoi(s);
    // if(cc == 'M') c *= 1024;
    if(cc == 'G') c *= 1024;
    if(cc == 'T') c *= 1024*1024;
    debug(c);
    vll vec(n);
    forn(i,0,n) cin >> vec[i];

    ll p1 = 0;
    ll p2 = 0;
    ll sum = 0;

    ll r = INF; 

    while(p1 < n && p2 <= n){
        if(p2 == n){
            r = min(r, p2-p1);
            break;
        }
        if(p2 < n && sum + vec[p2] <= c){
            sum += vec[p2];
            p2++;
            continue;
        }

        trace(
            cout << sum << ln;
            cout << p1 << " " << p2 << ln;
        );
        
        r = min(r, p2-p1);
        sum -= vec[p1];
        p1++;
    }

    ll x = 0;
    ll l = -1;
    debug(r);
    if(r == n){
        cout << r << " " << -1 << ln;
        return 0;
    }

    forn(i,0,r+1) x += vec[i];
    forn(i,r+1, n){
        if(x > c){
            l = i - (r +1);
            break;
        }
        x -= vec[i-(r+1)];
        x += vec[i];
    }
    cout << r << " " << l+1 << ln;
    return 0;
}
