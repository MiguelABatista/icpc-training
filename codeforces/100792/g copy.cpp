#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
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

ld dist(pll p, pll q){
    p.first -= q.first;
    p.second -= q.second;
    return max(abs(p.first), abs(p.second)) + (sqrt((ld)2)-1)*min(abs(p.first), abs(p.second));
}

mt19937_64 rng((ll) chrono::steady_clock::now().time_since_epoch().count());

ll uniform(ll l, ll r){
    uniform_int_distribution<ll> uid(l,r);
    return uid(rng);
}


int main() {
    _;
    ll n; cin >> n;
    vector<pll> vec(n);
    forn(i,0,n) cin >> vec[i].first >> vec[i].second;

    ld bd = 0;
    ll x = 0,y = 0;

    forn(yyy,0,200){
        ll curr = uniform(0,n-1);
        ll nxt = 0;
        ll lst = -1;
        
        forn(xxx,0,50){
            forn(i,0,n){
                if(dist(vec[curr], vec[nxt]) < dist(vec[curr],vec[i])){
                    nxt = i;
                }
            }
            if(dist(vec[curr], vec[nxt]) > bd){
                x = curr;
                y = nxt;
            } 
            if(nxt == lst) break;
            lst = curr;
            curr = nxt;
        }
    }

    cout << x+1 << " " << y+1 << ln; 
    return 0;
}
