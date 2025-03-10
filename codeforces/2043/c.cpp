#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64; 
typedef vector<ll> v64;

#define forn(i, s, e) for(ll i = (s); i < (e); i++)
#define ln "\n"

#if defined(DEBUG) || defined(debug)
    #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
    #define debug(x) cout << __LINE__ << ": " << #x << " = " << x << ln
#else
    #define _ (void)0
    #define debug(x) (void)0
#endif

const ll INF = 0x3f3f3f3f3f3f3f3fll;

void solve(){
    ll n; cin >> n;
    v64 vec(n);
    set<ll> resp;
    ll esp_idx = 0;
    
    forn(i,0,n){
        cin >> vec[i];
        if(vec[i] != 1 && vec[i] != -1) esp_idx = i;
    } 

    ll max_end = 0;
    ll min_end = 0;
    ll max_ans = 0;
    ll min_ans = 0;

    forn(i,0,esp_idx){
        max_end = max(max_end + vec[i], vec[i]);
        min_end = min(min_end + vec[i], vec[i]);

        max_ans = max(max_ans, max_end);
        min_ans = min(min_ans, min_end);
    }

    debug(min_ans);
    debug(max_ans);
    forn(i,min_ans, max_ans+1) resp.insert(i);

    max_end = 0;
    min_end = 0;
    max_ans = 0;
    min_ans = 0;

    forn(i,esp_idx+1,n){
        max_end = max(max_end + vec[i], vec[i]);
        min_end = min(min_end + vec[i], vec[i]);

        max_ans = max(max_ans, max_end);
        min_ans = min(min_ans, min_end);
    }

    debug(min_ans);
    debug(max_ans);
    forn(i,min_ans, max_ans+1) resp.insert(i);


    v64 esq(n+1,0);
    v64 dir(n,0);

    ll max_esq = 0;
    ll min_esq = 0;
    
    for(ll i = esp_idx-1; i >= 0; i--){
        esq[i] = esq[i+1] + vec[i];
        max_esq = max(max_esq, esq[i]);
        min_esq = min(min_esq, esq[i]);
    }

    ll max_dir = 0;
    ll min_dir = 0;

    forn(i, esp_idx+1, n){
        dir[i] = dir[i-1] + vec[i];
        max_dir = max(max_dir, dir[i]);
        min_dir = min(min_dir, dir[i]);
    }

    ll all_max = max_dir + max_esq;
    ll all_min = min_dir + min_esq;

    debug(all_min);
    debug(all_max);
    debug(vec[esp_idx]);

    forn(i,vec[esp_idx]+all_min, vec[esp_idx]+all_max+1) resp.insert(i);

    
    cout << resp.size() << ln;
    for(ll x: resp){
        cout << x << ' ';
    }
    cout << ln;
}

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();

    return 0;
}