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
#define debugm(v) trace(cout << #v ": "; for (auto xx : v) cout << xx.first << ":" << xx.second << " "; cout << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;

int main() {
    _;
    ll nm, t; cin >> nm >> t;
    
    ll n = nm/2;
    ll m = nm-n;

    vll vec1(n); 
    forn(i,0,n) cin >> vec1[i];
    vll vec2(m); 
    forn(i,0,m) cin >> vec2[i];

    map<ll,ll> freq1;
    forn(mask,0,(1<<n)){
        ll sum = 0;
        forn(i,0,n){
            if((mask&(1<<i)) == 0) continue;        
            sum += vec1[i];
        }
        freq1[sum]++;
    }

    map<ll,ll> freq2;
    forn(mask,0,(1<<m)){
        ll sum = 0;
        forn(i,0,m){
            if((mask&(1<<i)) == 0) continue;        
            sum += vec2[i];
        }
        freq2[sum]++;
    }

    debugm(freq1);
    debugm(freq2);
    ll resp = 0;
    for(auto [k,v] : freq1){
        ll x = t - k;
        resp += v*freq2[x];
    }

    cout << resp << ln;
    return 0;
}
