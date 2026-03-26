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

mt19937_64 rng((ll) chrono::steady_clock::now().time_since_epoch().count());

ll uniform(ll l, ll r){
    uniform_int_distribution<ll> uid(l, r);
    return uid(rng);
}

int main() {
    _;
    ll tam = 20;
    ll alph = 4;
    ll oddsI = 4;
    ll n = 10;

    string s(tam, ' ');

    forn(i,0,tam) s[i] = 'a' + uniform(0,alph-1);
    cout << s << ln;
    cout <<  n << ln;
    forn(i,0,n){
        if(uniform(1,oddsI) == 1) cout << "I" << ln;
        else cout << "L " << uniform(1,tam) << ln; 
    }
    return 0;
}
