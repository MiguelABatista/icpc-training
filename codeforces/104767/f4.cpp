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

set<ll> badprimes = {1,7,11,13, 17,19};


void monta_gaba(ll val, v64& out){
    ll key = 0;
    for(ll x: out) key += (1<<x);

    cout << "{ " << key << ", " << val << " },\n";
}


void solve(v64 v, v64 out){
    ll n = v.size();

    ll best_resp = 0;
    
    ll count = 0;

    do {
        if(count % 10000000 == 0){
            cout << count << ln;
        }
        ll curr = 0;
        forn(i,0,n-1){
            curr += gcd(v[i], v[i+1]);
        }
        best_resp = max(best_resp, curr);
        count++;
    } while (std::next_permutation(v.begin(), v.end()));
    
    monta_gaba(best_resp, out);
    return ;
}

int main(){
    ll n = 11;
    v64 tudo = {2,3,4,5,6,7,9,10,12,14,15,18,20};

    solve(tudo, v64());

    forn(i,0,n){
        v64 t = tudo;
        v64 out;
        // remove o t[i] e coloca no vetor o
        out.push_back(t[i]);
        t.erase(t.begin() + i);
        solve(t, out);
    }

    forn(i,0,n){
        forn(j,i+1,n){
            v64 t = tudo;
            v64 out;
            out.push_back(t[i]);
            out.push_back(t[j]);

            t.erase(t.begin() + j); 
            t.erase(t.begin() + i);

            solve(t, out);
        }
    }

    return 0; 
}