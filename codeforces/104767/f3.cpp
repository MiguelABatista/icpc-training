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

void monta_gaba(v64& v, v64& out, bool quat){
    v64 gaba = {1, 11, 13, 17, 19, 7, 14};
    
    for(ll x: v){
        gaba.push_back(x);
        if(x == 4){
            gaba.push_back(8);
            gaba.push_back(16);
        }
    }
    
    ll key = 0;
    for(ll x: out) key += (1<<x);
    if(quat) key *= -1;

    cout << "{ " << key << ", { ";
    forn(i,0,gaba.size()-1) cout << gaba[i] << ", ";
    cout << gaba[gaba.size()-1] << " }}, \n";
}

void monta_gaba2(ll val, v64& out, bool quat){

    ll key = 1;
    for(ll x: out) key += (1<<x);
    if(quat) key *= -1;

    cout << "{ " << key << ", " << val << " },\n";
}


void solve(v64 v, v64 out){
    ll n = v.size();

    ll best_resp = 0;
    ll best_14 = 0;

    v64 bv;
    v64 b14;

    do {
        ll curr = 0;
        forn(i,0,n-1){
            curr += gcd(v[i], v[i+1]);
        }

        if(curr > best_resp){
            best_resp = curr;
            bv = v;
        }

        if(v[0] % 2 == 0) curr += 2;

        if(curr > best_14){
            best_14 = curr;
            b14 = v;
        }
    } while (std::next_permutation(v.begin(), v.end()));
    
    monta_gaba2(best_resp, out, false);
    monta_gaba2(best_14, out, true);
    return ;
}

int main(){
    ll n = 11;
    v64 tudo = {2,3,4,5,6,9,10,12,15,18,20};

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