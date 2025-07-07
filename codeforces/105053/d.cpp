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
const ll LIM = 1'000'010;

int main(){
    _;
    ll n; cin >> n;
    
    if(n == 1){
        cout << "N" << ln;
        return 0;
    }

    map<ll,ll> fatores;
    forn(i,2,LIM){
        while(n%i == 0){
            fatores[i]++;
            n /= i;
        }
    }

    if(n > 1){
        fatores[n]++;
    }
    
    if(fatores.size() >= 3){
        cout << "N" << ln;
        return 0;
    }

    if(fatores.size() == 1){
        ll a = fatores.begin()->second;
        if(a%2 == 0){
            cout << "N" << ln;
        }else{
            cout << "Y" << ln;
        }
        return 0;
    }

    ll a = fatores.begin()->second;
    ll b = fatores.rbegin()->second;

    if(a >= 2 && b >= 2){
        cout << "N" << ln;
        return 0;
    }

    if(a < b) swap(a,b);

    if(a >= 2){
        cout << "N" << ln;
        return 0;
    }

    cout << "Y" << ln;
    return 0;
}