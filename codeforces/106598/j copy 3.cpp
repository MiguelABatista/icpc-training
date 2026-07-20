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

    vector<vll> inv(2*k+1);

    forn(i,0,n){
        ll l, r; cin >> l >> r;
        inv[l+r].push_back(r-l);
    }
    
    ll resp = 0;
    forn(i,2,2*k-1){
        ll maxsize = min(i, 2*k-i);

        map<ll, ll> esq;
        map<ll, ll> dir;
        map<ll, ll> cen;
        vll pts;

        for(auto v : inv[i-2]) if(v+2 <= maxsize){
            pts.push_back(v+2);
            esq[v+2] = v;
        }
        for(auto v : inv[i]) if(v < maxsize){
            pts.push_back(v);
            cen[v] = v;
        }
        for(auto v : inv[i+2]) if(v+2 <= maxsize){
            pts.push_back(v+2);
            dir[v+2] = v;
        }

        
        pts.push_back(maxsize);
        sort(pts.begin(),pts.end());
        pts.erase(unique(pts.begin(), pts.end()), pts.end());        
        
        ll currresp = 0;
        ll besq = 0;
        ll bdir = 0;
        ll bcen = 0;

        forn(j,0,sz(pts)){
            besq = max(besq, esq[pts[j]]);
            bdir = max(bdir, dir[pts[j]]);
            debug(j);
            currresp += max(bcen, min(besq, bdir));
            bcen = max(bcen, cen[pts[j]]);
            if(j < sz(pts)-1) currresp += max(bcen, min(besq, bdir))*((pts[j+1] - pts[j]-1)/2);
        }

        resp += currresp;
    }
     
    trace(cout << ln << ln;)
    debug(resp);
    ll num = resp;
    ll dem = (k*(k+1))/2;
    debug(num);
    debug(dem);
    ll d = gcd(num,dem);
    cout << num/d << " " << dem/d << ln;
    return 0;
}