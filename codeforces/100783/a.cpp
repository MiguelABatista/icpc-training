#include <bits/stdc++.h>
using namespace std;


typedef int ll;
typedef pair<ll, ll> p64;
typedef vector<ll> v64;

#define forn(i, s, e) for (ll i = (s); i < (e); i++)
#define ln "\n"

#if defined(DEBUG)
    #define _ (void)0
    #define debug(x) cout << __LINE__ << ": "<< #x << " = " << x << ln;
#else
    #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
    #define debug(x) (void)0
#endif

const ll INF = 1;

ll tam = 0;
map<char, ll> mp;
vector<ll> tradutor(27);
vector<string> vec;
vector<ll> perm;

ll convert(ll i){
    ll prod = 1;
    ll ans = 0;
    for(char c: vec[i]){
        ans += prod*perm[tradutor[c-'A']];
        prod *= 10;
    }
    return ans;
}

int main() {
    _;
    ll n; cin >> n;

    vec.resize(n);
    set<char> esq;

    forn(i,0,n){
        cin >> vec[i];
        esq.insert(vec[i][0]);

        for(char c: vec[i]){
            if(mp.find(c) == mp.end()) mp[c] = tam++;
        }
        reverse(vec[i].begin(), vec[i].end());
    }

    perm.resize(10);
    iota(perm.begin(), perm.end(), 0);

    ll cnt = 0;

    vector<ll> esqidx;
    for(char c: esq){
        esqidx.push_back(mp[c]);
    }

    for(auto [k,v] : mp){
        // cout << k << " : " << v << ln;
        tradutor[k-'A'] = v;
    }
    // cout << ln;

    do{ 
        bool found = false;
        for(ll temp: esqidx){
            if(perm[temp] == 0) found = true;  
        } 
        if(found) continue;

        ll sum = 0; 
        forn(i,0,n-1) sum += convert(i);
        if(sum == convert(n-1)){
            // forn(i,0,n) cout << perm[i] << " ";; cout << ln;
            cnt++;
        }
    } while(next_permutation(perm.begin(), perm.end()));
    
    forn(i,1,11-tam) cnt /= i;
    cout << cnt << ln;
    return 0;
}