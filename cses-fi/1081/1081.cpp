#include <bits/stdc++.h>
using namespace std;

typedef int ll;
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
const ll MAX = 1'000'005;
const ll MAX2 = 20;

vector<v64> divs;
void prep(){
    forn(i,1,MAX){
        for(ll j = i; j < MAX; j+= i){
            divs[j].push_back(i);
        }
    }
}

int main() {
    _;

    ll n; cin >> n;
    v64 freq(MAX);
    forn(j,0,n){
        ll x; cin >> x;
        for(ll i = 1; i*i <= x; i++){
            if(x%i != 0) continue;
            freq[i]++;
            if(i*i != x) freq[x/i]++;
        }
    }
    for(ll j = MAX-1; j >= 0; j--){
        if(freq[j] >= 2){
            cout << j << ln;
            return 0;
        }
    }
    return 0;
}
