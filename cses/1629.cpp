#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64; 
typedef vector<ll> v64;

#define forn(i, s, e) for(ll i = (s); i < (e); i++)
#define ln "\n"

#if defined(DEBUG) || defined(debug)
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

    vector<pair<ll,ll>> movies(n);

    forn(i,0,n) cin >> movies[i].second >> movies[i].first;

    sort(movies.begin(), movies.end());

    ll curr_end = 0;
    ll total_movies = 0;

    forn(i,0,n){
        if(movies[i].second >= curr_end){
            curr_end = movies[i].first;
            total_movies++;
        }
    }

    cout << total_movies << ln;
    return 0;
}