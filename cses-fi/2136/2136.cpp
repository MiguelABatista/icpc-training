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

void solve_burro(ll n, ll k){
    vll vec(n);
    forn(i,0,n){
        string s; cin >> s;
        vec[i] = stoi(s, 0, 2);
    }

    ll resp = INF;
    
    forn(i,0,n){
        forn(j,i+1,n){
            resp = min(resp, (ll)__builtin_popcountll(vec[i]^vec[j]));
        }
    }
    cout << resp << ln;
}

int main() {
    _;
    ll n, k; cin >> n >> k;
    solve_burro(n, k);
    return 0;
    vll vec(n);
    forn(i,0,n){
        string s; cin >> s;
        vec[i] = stoi(s, 0, 2);
    }
    set<ll> s;
    forn(i,0,n){
        s.insert(vec[i]);
    }

    if(sz(s) == n){
        cout << 1 << ln;
        return 0;
    }
    cout << 0 << ln;
    return 0;
}
