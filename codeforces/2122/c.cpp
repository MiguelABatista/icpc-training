#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64; 
typedef vector<ll> v64;

#define forn(i, s, e) for(ll i = (s); i < (e); i++)
#define ln "\n"

#if defined(DEBUG)
    #define _ (void)0
    #define debug(x) cout << __LINE__ << ": " << #x << " = " << x << ln
#else
    #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
    #define debug(x) (void)0
#endif

const ll INF = 0x3f3f3f3f3f3f3f3fll;

void solve(){
    ll n; cin >> n;
    vector<pair<p64, ll>> vec(n);
    vector<pair<p64, ll>> vec2(n);
    vector<pair<char, char>> pos(n);

    v64 xs(n), ys(n);

    forn(i,0,n){
        cin >> vec[i].first.first >> vec[i].first.second;
        vec[i].second = i;
        vec2[i].first.second = vec[i].first.first;
        vec2[i].first.first = vec[i].first.second;
        vec2[i].second = i;
    }

    sort(vec.begin(), vec.end());
    forn(i,0,n/2){
        ll idx = vec[i].second;
        pos[idx].first = 'b';
    }
    forn(i,n/2,n){
        ll idx = vec[i].second;
        pos[idx].first = 'c';
    }

    sort(vec2.begin(), vec2.end());
    forn(i,0,n/2){
        ll idx = vec2[i].second;
        pos[idx].second = 'b';
    }
    forn(i,n/2,n){
        ll idx = vec2[i].second;
        pos[idx].second = 'c';
    }

    v64 bb, bc, cb, cc;
    forn(i,0,n){
        auto& p = pos[i];
        if(p.first == 'c'){
            if(p.second == 'c'){
                cc.push_back(i);
            }else{
                cb.push_back(i);
            }
        }else{
            if(p.second == 'c'){
                bc.push_back(i);
            }else{
                bb.push_back(i);
            }            
        }
    }

    forn(i,0,(ll)bb.size()){
        cout << bb[i] + 1 << " " << cc[i] + 1 << ln;
    }
    forn(i,0,(ll)bc.size()){
        cout << bc[i] + 1 << " " << cb[i] + 1 << ln;
    }
} 

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}