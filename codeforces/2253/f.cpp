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

ll func(vll a, vll b, ll n, ll m){
    set<ll> s;
    ll extra = 0;

    auto coloca = [&](vll& v){
        auto it = s.find(v.back());
        if(it == s.end()) s.insert(v.back());
        else extra++;
        v.pop_back();
    };

    forn(i,0,n) if(sz(a) > 0) coloca(a);
    forn(i,0,m) if(sz(b) > 0) coloca(b);

    while ((sz(a) > 0 || sz(b) >> 0) && (extra > 0)){
        extra--;
        if(sz(a) == 0){
            coloca(b);
            continue;
        }  

        if(sz(b) == 0){
            coloca(a);
            continue;
        }            
        if(a.back() > b.back()){
            coloca(a);
        }else{
            coloca(b);
        }
    }

    ll sum = 0;
    for(ll x: s) sum += x;
    return sum;
}



int main() {
    _;

    return 0;
}
