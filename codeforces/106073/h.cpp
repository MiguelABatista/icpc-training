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

// Sum over Subsets DP (SOS DP)
//
// sos_dp_sub: for each mask, computes the sum of f[s] over all
// subsets s of mask (i.e., f'[mask] = sum of f[s] for s in mask).
//
// sos_dp_super: for each mask, computes the sum of f[s] over all
// supersets s of mask (i.e., f'[mask] = sum of f[s] for mask in s).
//
// input size must be a power of two (2^n).
//
// complexity: O(n * 2^n), O(2^n) mem

v64 sos_dp_sub(v64 f) {
    ll n = __builtin_ctzll(sz(f));
    assert((1ll<<n) == sz(f));

    forn(i,0,n) forn(mask, 0, (1<<n))
        if (mask>>i&1) f[mask] += f[mask^(1<<i)];
        // -= for inverse
    return f;
}

v64 invsos_dp_sub(v64 f) {
    ll n = __builtin_ctzll(sz(f));
    assert((1ll<<n) == sz(f));

    forn(i,0,n) forn(mask, 0, (1<<n))
        if (mask>>i&1) f[mask] -= f[mask^(1<<i)];
        // -= for inverse
    return f;
}

int main() {
    _;
    ll n, k; cin >> n >> k;
    ll pot2 = 1ll<<k;
    v64 freq(pot2);

    forn(i,0,n){
        string s;
        cin >> s;
        ll x = std::stoi(s, 0, 2);
        freq[x]++;
    }

    auto f2 = sos_dp_sub(freq);

    forn(i,0,pot2) f2[i] = (f2[i]*(f2[i]-1)*(f2[i]-2))/6;

    auto f3 = invsos_dp_sub(f2);

    ll m; cin >> m;
    while(m--){
        string s;
        cin >> s;
        ll x = std::stoi(s, 0, 2);
        cout << f3[x] << ln;
    }
    return 0;
}
