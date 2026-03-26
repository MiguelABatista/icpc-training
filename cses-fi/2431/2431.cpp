#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64;
typedef vector<ll> v64;

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

ll solve(ll k){
    ll tam = 1;
    ll pot = 1;
    
    ll curr_sum = 0;
    ll next_sum = 9;

    // 1*9 + 2*(99-9) + 3*(999-99)
    
    while (next_sum <= k){
        // cout << curr_sum << ln;
        curr_sum = next_sum;
        pot *= 10;
        tam++;
        next_sum = curr_sum + tam*9*pot;
    } ;

    ll delta = k - curr_sum;
    
    if(delta == 0){
        return 9;
    }
    
    delta--;

    ll m = delta/tam;
    ll d = delta%tam;
    
    ll n = pot + m;

    forn(i,0,tam-1 - d) n /= 10;
    return (n%10);
}

// 123456789 1011 1213 1415 16
// 123456789 0123 4567 8901 23

void test(){
    ll lim = 1000;
    string s;
    forn(i,1,lim+1) s += to_string(i);
    ll k = sz(s);
    string s2;
    forn(i,1,k+1){
        ll x = solve(i);
        // cout << x << ln;
        s2.push_back(char(x+'0'));
    }
    cout << s << ln << ln;
    cout << s2 << ln;
    if(s == s2) cout << "OK" << ln;
    else cout << "F" << ln;
}

int main() {
    _;
    ll q; cin >> q;
    while(q--){
        ll k;
        cin >> k;
        cout << solve(k) << ln;
    }
    return 0;
}
