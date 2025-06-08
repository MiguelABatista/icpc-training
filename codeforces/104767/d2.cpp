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
ll n, q;

string calc_burro(v64& vec, vector<char>& op){
    ll resp = 0;
    ll curr = 0;
    
    curr = vec[0];

    forn(i, 1, n){
        if(op[i-1] == '+'){
            resp+= curr;
            curr = vec[i];
        }
        else{
            curr*= vec[i];
        }
    }
    resp+=curr;
    resp = resp%2;
    return (resp == 0 ? "even" : "odd");
}

int main(){
    _;
    cin >> n >> q;
    v64 vec(n);
    vector<char> op(n-1);

    forn(i,0,n){

        cin >> vec[i];
        vec[i] = vec[i]%2;
        if(i != n-1){
            char c; cin >> c;
            if( c == '-') c = '+';
            op[i] = c;
        }
    }  

    cout << calc_burro(vec, op) << ln;
    
    forn(i,0,q){
        ll idx, val;

        cin >> idx >> val; idx--;
        val = val%2;
        vec[idx] = val;

        cout << calc_burro(vec, op)  << ln;
    }
    
    return 0;
}