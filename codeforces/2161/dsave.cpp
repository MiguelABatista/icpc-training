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

bool testa(v64& vec,ll n, ll k, set<p64>& ord){
    v64 valid(n,1);
    ll cnt = 0;
    for(auto [key,v] : ord){
        if(cnt == k) break;
        valid[v] = 0;
        cnt++;
    }
    map<ll, ll> tras;
    map<ll, ll> frente;
    forn(i,0,n) if(valid[i]){
        frente[vec[i]]++;
    }
    v64 ruindade(n);

    forn(i,0,n)if(valid[i]){
        ll x = frente[vec[i]+1] + tras[vec[i]-1];
        if(x > 0) return false;
        tras[vec[i]]++;
        frente[vec[i]]--;
    }
    return true;
}

void solve(){
    ll n; cin >> n;
    v64 vec(n);
    forn(i,0,n) cin >> vec[i];
    map<ll, ll> tras;
    map<ll, ll> frente;
    forn(i,0,n) frente[vec[i]]++;

    v64 ruindade(n);
    forn(i,0,n){
        ruindade[i] = frente[vec[i]+1] + tras[vec[i]-1];
        tras[vec[i]]++;
        frente[vec[i]]--;
    }
    debugv(ruindade);
    
    set<p64> ord;
    forn(i,0,n){
        ord.insert({ruindade[i], i});

    }
    
    forn(i,0,n+1){
        if(testa(vec, n, i, ord)){
            cout << i << ln;
            return;
        }
    }
    cout << -1 << ln;
}

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}