#include <bits/stdc++.h>
using namespace std;

typedef int ll;
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

int main(){
    _;
    ll n, m;
    cin >> n >> m;
    
    v64 v(n); 
    map<ll,ll> freq;

    forn(i,0,n){
        cin >> v[i];
        freq[v[i]]++;
    }

    set<ll> to_remove;
    set<ll> valid;

    for(auto& p: freq){
        if(p.first > p.second){
            to_remove.insert(p.first);
        }else{
            valid.insert(p.first);
        }
    }

    for(ll val: to_remove) freq.erase(val);

    map<ll, v64> mp;

    for(ll val: valid){
        mp[val] = v64(n,0);
    }

    forn(i,0,n){
        if(valid.count(v[i])){
            mp[v[i]][i] = 1; 
        }
    }

    for(auto& [k, vec] : mp){
        forn(i,1,n) vec[i] += vec[i-1];
    }

    while(m--){
        ll l, r; cin >> l >> r;
        l--; r--;
        ll cnt = 0;
        for(auto& [k, vec] : mp){
            if(vec[r] - (l == 0 ? 0 : vec[l-1]) == k){
                cnt++;
            }
        }
        cout << cnt << ln;
    }
    return 0;
}