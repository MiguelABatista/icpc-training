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

void monta_gaba(v64& v){
    v64 gaba = {1, 11, 13, 17, 19, 7, 14};
    for(ll x: v){
        gaba.push_back(x);
        if(x == 4){
            gaba.push_back(8);
            gaba.push_back(16);
        }
    }
    cout << "{ ";
    forn(i,0,gaba.size()-1) cout << gaba[i] << ", ";
    cout << gaba[gaba.size()-1] << " }, \n";
}

ll solve(v64 v){
    ll n = v.size();
    for(ll x: v){
        cout << x << " ";
    }
    cout << ln;
    debug(v.size());
    ll best_resp = 0;

    do {
        ll curr = 0;
        forn(i,0,n-1){
            curr += gcd(v[i], v[i+1]);
        }
        if(v[0] % 2 == 0 || v[n-1] % 2 == 0) curr += 2;

        if(curr == 55) monta_gaba(v);

        best_resp = max(best_resp, curr);
    } while (std::next_permutation(v.begin(), v.end()));
    return best_resp;
}

int main(){
    _;
    ll n; cin >> n;
    v64 freq(21,0);
    ll bad = 0;
    forn(i,0,n){
        ll aux; cin >> aux;
        freq[aux]++;
    }

    v64 valid;

    bool quatro = false;
    forn(i,0,21){
        if(freq[i] == 0) continue;
        if(badprimes.count(i)){
            bad++;
            continue;
        }
        if(i == 4 || i == 8 || i == 16){
            quatro = true;
            continue;
        };
        if( i == 14) continue;
        valid.push_back(i);
    }

    if(quatro) valid.push_back(4);

    sort(valid.begin(), valid.end());

    ll algo = 0;
    
    
    if(!valid.empty()) algo = solve(valid);
    
    debug(algo);
    
    if((freq[16] || freq[8]) && freq[4])  algo += 4;
    if((freq[16] && freq[8]))  algo += 8;
    
    if(freq[14] && freq[7]) algo += 7;
    else if(freq[14]) bad++;
        
    
    debug(algo);

    algo += bad;
    if(valid.empty()) algo--;

    forn(i,1,21){
        if(freq[i] == 0) continue;
        algo += i*(freq[i]-1);
    }

    cout << algo << ln;
    return 0;
}