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
    v64 vec(n);

    vector<v64> ap(n+1);
    set<ll> actives;
    set<ll> ult;

    forn(i,0,n){
        cin >> vec[i];
        ap[vec[i]].push_back(i);
        actives.insert(vec[i]);
    }

    for(ll val : actives){
        ult.insert(*(--ap[val].end()));
    }

    ll count = 0;
    ll curr_end = n-1;

    while(!ult.empty()){
        ll aux = *ult.begin();
     
        for(ll i = curr_end; i >= aux; i--){
            debug(i); 
            //for(ll x : ap[vec[i]])  cout << x << " ";
            //cout << ln;
            
            ap[vec[i]].pop_back();
            if(ap[vec[i]].empty()) actives.erase(vec[i]);
        }

        count++;
        ult.clear();
        for(ll val : actives){
            ult.insert(*(--ap[val].end()));
        }
        curr_end = aux-1;
    }

    cout << count << ln;
}

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}