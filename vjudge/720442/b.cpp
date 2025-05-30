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
    ll n; cin >> n;

    vector<pair<ll,ll>> eventos;

    forn(i,0,n){
        ll a, b;
        cin >> a >> b;
        eventos.emplace_back(a,1);
        eventos.emplace_back(b,-1);
    }

    sort(eventos.begin(), eventos.end());

    ll curr = 0;
    ll max_people = 0;
    for(auto p: eventos){
        curr += p.second;
        max_people = max(curr, max_people); 
    }

    cout << max_people << ln;
    return 0;
}