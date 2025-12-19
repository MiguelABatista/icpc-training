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
const ll MAXA = 1'000'000'001;
const ll LIM = 1'000'000;

#include <bits/extc++.h> 

void solve(){
    ll n; cin >> n;
    v64 vec(n);
    map<ll,ll> freq;
    forn(i,0,n) cin >> vec[i];
    
    set<ll> s;
    forn(i,0,n) s.insert(vec[i]);
    forn(i,0,n) freq[vec[i]]++;

    ll resp = 0;

    auto comp = [&](ll k, ll b){
        auto it1 = freq.find(k/b);
        if(it1 == freq.end()) return 0ll;
        auto it2 = freq.find(k*b);
        if(it2 == freq.end()) return 0ll;
        return (it1->second)*(it2->second);
    };

    for(ll k: s){ 
        debug(k);
        ll v = freq[k];
        resp += (v*(v-1)*(v-2));
        
        if(k >= LIM){
            forn(b,2,1001){
                if(k*b > MAXA) break;
                if(k%b) continue;
                resp += v*comp(k,b);
            }
            continue;
        }
        for(ll d = 1; d*d <= k; d++) if(k%d == 0){
            if(d != 1) resp += v*comp(k,d);
            if(d*d != k){
                resp += v*comp(k,k/d);
            }
        }
        debug(resp);
    }
    

    cout << resp << ln;
    trace(cout << "------------\n\n";);
}

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}