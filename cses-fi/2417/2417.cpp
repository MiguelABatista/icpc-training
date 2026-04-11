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
#define debugv(v) trace(cout <<  #v ": "; for (auto xx : v) cout << setw(2) <<  xx << " "; cout << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;
const ll MAX = 1'000'005;

// Flattened Divisor Sieve (CSR format)
// Precomputes all divisors up to n. 
// Faster than vector<v64> for cache reasons 
// Time Complexity: O(n log n) | Space Complexity: O(n log n)

tuple<v64, v64, v64> get_divisor(ll n) {
    v64 head(n);
    v64 tail(n);
    v64 divs(n*(log(n)+1));

    forn(i, 1, n)
        for (ll j = i; j < n; j += i)
            head[j]++;

    ll curr = 0;
    forn(i, 1, n) {
        ll cnt = head[i];
        head[i] = curr;
        tail[i] = curr;
        curr += cnt;
    }

    forn(i, 1, n) 
        for (ll j = i; j < n; j += i) 
            divs[tail[j]++] = i; 
    return {head, tail, divs};   
}

inline ll esc2(ll n){
    return (n*(n-1))/2;
}

pair<v64, v64> sieve(ll n){
    v64 lp(n+1);
    v64 pr;
    forn(i, 2, n+1) {
        if (lp[i] == 0) {
            lp[i] = i;
            pr.push_back(i);
        }
        for (ll j = 0; i * pr[j] <= n; ++j) {
            lp[i * pr[j]] = pr[j];
            if (pr[j] == lp[i]) {
                break;
            }
        }
    }
    return {pr, lp};
}

v64 calc_mu(v64& lp) {
    ll n = sz(lp) - 1;
    v64 ans(n);
    ans[1] = 1;
    forn(i,2,n) {
        ll p = lp[i], x = i/p;
        if (lp[x] == p) ans[i] = 0;
        else ans[i] = -ans[x];
    }
    return ans;
}


int main() {
    _;
    auto [head, tail, divs] = get_divisor(MAX);
    auto [pr, lp] = sieve(MAX);
    v64 mu = calc_mu(lp);
    

    ll n; cin >> n;
    v64 freq1(MAX);
    v64 freq2(MAX);

    forn(i,0,n){
        ll x; cin >> x;
        freq1[x]++;
    }

    forn(i,0,MAX){
        if(freq1[i] == 0) continue;
        
        forn(k,head[i], tail[i]){
            ll d = divs[k];
            freq2[d] += freq1[i];
        }
    }

    ll resp = 0;
    forn(i,0,MAX) freq2[i] = esc2(freq2[i]);
    
    forn(i,1,MAX){
        resp += mu[i]*freq2[i];
    }

    cout << resp << ln;
    return 0;
}
