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

int main(){
    _;
    ll n, m, c; cin >> n >> m >> c;
    vector<pair<ll,ll>> students (n);
    vector<ll> schools (m,0); 
    ll foption = 0 ;
    ll soption = 0 ;
    forn(i,0,n){
        ll f , s ; 
        cin >> f >> s ; 
        students[i].first = f-1 ; 
        students[i].second = s-1 ; 
    }
    forn(i,0,n){
        if (schools[students[i].first]<c){
            schools[students[i].first]++;
            foption++;
        }
        else if (schools[students[i].second]<c){
            schools[students[i].second]++ ;    
            soption++;  
        }

    }
    cout << foption << " " << soption << ln ; 
    return 0;
}