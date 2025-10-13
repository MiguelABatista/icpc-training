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

int solve(ll n, ll w) {
    if(n == 2){
        cout << "1 1" << ln;
        cout << "2 2" << ln;
        return 0;
    }

    ll g = (2*n)/3;
    g += 1;
    vector<p64> vec(n);

    forn(i,0,g){
        vec[i] = {i+1, g-i};
    }

    forn(i,g,n){
        vec[i] = {i,i};
    }


    if(w < 5000){
        forn(i,0,n) vec[i].first += w;
    }else{
        forn(i,0,n) vec[i].first = w - vec[i].first;
    }

    // set<p64> s;
    // forn(i,0,n) s.insert(vec[i]);

    // if(s.size() != n){
    //     cout << n << " " << w << ln;
    //     exit(0);
    // }

    forn(i,0,n){
        cout << vec[i].first << " " << vec[i].second << ln;
    }

    return 0;
}

int main(){
    ll n; ll w;
    cin >> n >> w;
    solve(n,w);
}