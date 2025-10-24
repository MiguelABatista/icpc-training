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

int main(){
    _;
    return 0;
}

bool testa(ll h, v64& vec, ll n){
    ll curr = 0;
    ll idx = 0;
    bool chao = true;
    while(idx < n){
        debug(curr);
        debug(chao);
        debug(idx);
        debug(abs(curr-vec[idx]));
        debug(h);
        if(abs(curr-vec[idx]) <= h){
            curr = vec[idx];
            chao = false;
            idx++;
            continue;
        }
        if(chao){
            debug("false");
            return false;
        }
        curr = 0;
        chao = true;
    }
    return true;  
}