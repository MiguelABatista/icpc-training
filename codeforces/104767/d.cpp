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

void solve(ll q){
    ll val; cin >> val;
    cout << (val%2 == 0 ? "even" : "odd") << ln;

    forn(i,0,q){
        ll idx;

        cin >> idx >> val; idx--;

        val = val%2;
        
        cout << (val == 0 ? "even" : "odd") << ln;
    }
}

int main(){
    _;
    ll n, q; cin >> n >> q;
    if(n == 1){
        solve(q);
        return 0;
    }
    v64 vec(n);
    vector<char> op(n-1);
    v64 rep(n);
    vector<set<ll>> mset(n, set<ll>{});


    forn(i,0,n){
        rep[i] = i;
        cin >> vec[i];
        vec[i] = vec[i]%2;
        if(i != n-1){
            char c; cin >> c;
            if( c == '-') c = '+';
            op[i] = c;
        }
    }  

    
    forn(i,0,n-1){
        if(op[i] == '*'){
            rep[i+1] = rep[i];
        }
    }
 
    forn(i,0,n){
        if(vec[i] == 0) mset[rep[i]].insert(i);
    }

    ll resp = 0;

    forn(i,0,n){
        if(rep[i] != i) continue;
        resp += (mset[i].size() > 0 ? 0 : 1);
    }
    
    resp = resp%2;

    cout << (resp == 0 ? "even" : "odd") << ln;

    forn(i,0,q){
        ll idx, val;

        cin >> idx >> val; idx--;
        val = val%2;
        
        if(vec[idx] == val){ 
            cout << (resp == 0 ? "even" : "odd") << ln;
            continue;
        }

        vec[idx] = val;
        if(val == 1){
            mset[rep[idx]].erase(idx);
            if(mset[rep[idx]].size() == 0) resp ^= 1;
        }else{
            mset[rep[idx]].insert(idx);
            if(mset[rep[idx]].size() == 1) resp ^= 1;
        }
        cout << (resp == 0 ? "even" : "odd") << ln;
    }

    return 0;
}