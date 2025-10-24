#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64; 
typedef vector<ll> v64;

#define forn(i, s, e) for(ll i = (s); i < (e); i++)
#define sz(x) ((ll) x.size())
#define ln "\n"

#ifdef DEBUG
    #define trace(x) x
    #define _ (void)0
#else
    #define trace(x) (void)0
    #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
#endif

#define debugv(v) trace({cout << #v": "; for (auto x : v) cout<< x << " "; cout << ln;})
#define debug(x) trace(cout << __LINE__ << ": " #x " = " << x << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;

bool attack(p64 p, p64 q){
    if(p.first == q.first) return true;
    if(p.second == q.second) return true;
    if(p.first + p.second == q.first + q.first) return true;
    if(p.first - p.second == q.first - q.first) return true;
    return false;
}


void solve(){
    ll n; 
    cin >> n;
    vector<p64> queens(n);
    set<ll> d1, d2, v, h;
    forn(i,0,n){
        cin >> queens[i].first >> queens[i].second;
        h.insert(queens[i].first);
        v.insert(queens[i].second);
        d1.insert(queens[i].first+queens[i].second);
        d2.insert(queens[i].first-queens[i].second);
    }
    if(n == 1){
        cout << "YES" << ln;
        cout << queens[0].first << " " << queens[0].second << ln;
        return;
    }else if(n == 2){
        cout << "YES" << ln;
        cout << queens[0].first << " " << queens[1].second << ln;
        return;
    }

    if(h.size() == 1)

}

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}