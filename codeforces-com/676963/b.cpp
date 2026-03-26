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

int main() {
    _;
    ll n; cin >> n;
    set<p64> s;
    v64 vec(n);
    forn(i,0,n) cin >> vec[i];

    vector<p64> ops;

    forn(i,0,n) s.insert({vec[i], i});

    while(true){
        auto ita = s.begin();
        auto [a, ida] = *ita;
        auto itb = prev(s.end());
        auto [b, idb] = *itb;
        
        if(a > b){
            swap(a,b);
            swap(ida, idb);
        }

        if(b - a <= 1) break;

        s.erase(ita);
        s.erase(itb);

        s.insert({(a+b)/2, ida});
        s.insert({(a+b+1)/2, idb});
        ops.push_back({ida,idb});
    }

    ll menor = s.begin()->first;
    for(auto [x, idx] : s) vec[idx] = x - menor;
    debugv(vec);
    forn(i,0,n){
        if(vec[i] == 0) continue;
        forn(j,i+1, n){
            if(vec[j] == 1) continue;
            ops.push_back({i,j});
            swap(vec[i], vec[j]);
            break;
        }
    }

    cout << sz(ops) << ln;
    for(auto [a,b] : ops){
        cout << a + 1 << " " << b + 1 << ln;
    }
    return 0;
}

//  1  2  3  4  5
// 14  7 13  8 15  2 5
// 14 11 13  8 11  4 1
// 11 11 13 11 11  1 3
// 12 11 12 11 11  1 2
// 11 12 12 11 11  1 2