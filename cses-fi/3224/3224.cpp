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
#define debugp(v) trace(cout << #v ": "; for (auto xx : v) cout << xx.first << ":" << xx.second << " "; cout << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;

int main() {
    _;
    ll n, k; cin >> n >> k;
    v64 vec(n);
    forn(i,0,n) cin >> vec[i];

    set<p64> s;
    map<ll, ll> freq;
    forn(i,0,k){
        ll f = freq[vec[i]];
        if(f > 0) s.erase({f,-vec[i]});
        s.insert({f+1, -vec[i]});
        freq[vec[i]]++;
    }
    debugv(vec);
    cout << -prev(s.end())->second << " ";
    // cout << -prev(s.end())->second << ln;
    forn(i,k,n){
        debugp(s);
        debugp(freq);
        ll f = freq[vec[i-k]];
        s.erase({f,-vec[i-k]});
        s.insert({f-1, -vec[i-k]});
        freq[vec[i-k]]--;

        f = freq[vec[i]];
        if(f > 0) s.erase({f,-vec[i]});
        s.insert({f+1, -vec[i]});
        freq[vec[i]]++;

        cout << -prev(s.end())->second << " \n"[i==n-1];
        // cout << -prev(s.end())->second << ln;
    }
    return 0;
}

