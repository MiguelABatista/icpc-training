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
    ll n, k; cin >> n >> k;
    vector<pll> vec(n);

    forn(i,0,n){
        ll l, r; cin >> l >> r;
        vec[i] = {l,r};
    }
    ll resp = 0;
    forn(l,0,k+1){
        forn(r,l+1,k+1){
            ll esq = 0;
            ll dir = 0;
            ll meio = 0;

            forn(i,0,n){
                if(l > vec[i].first) continue;
                if(r < vec[i].second) continue;
                if(l == vec[i].first && r == vec[i].second) continue;
                // l vec[i].first vec[i].second r
                if(l+r == vec[i].first + vec[i].second) meio = max(meio, vec[i].second-vec[i].first);
                if(l+r+2 == vec[i].first + vec[i].second && r-l >= vec[i].second - vec[i].first +2) esq = max(esq, vec[i].second-vec[i].first);
                if(l+r-2 == vec[i].first + vec[i].second && r-l >= vec[i].second - vec[i].first +2) dir = max(dir, vec[i].second-vec[i].first);
            }
            // if(max(meio, min(esq,dir))) cout << l << " " << r << ln;
            resp += max(meio, min(esq,dir));
        }
    }
    
    debug(resp);
    ll num = resp;
    ll dem = (k*(k+1))/2; 
    debug(num);
    debug(dem);
    ll d = gcd(num,dem);
    cout << num/d << " " << dem/d << ln;
    return 0;
}