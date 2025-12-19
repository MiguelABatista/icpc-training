#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64; 
typedef vector<ll> v64;

#define forn(i, s, e) for(ll i = (s); i < (e); i++)
#define sz(x) ((ll) x.size())
#define ln "\n"

#ifdef DEBUG
    #define trace(x) x
    #define _ (void)0
#else
    #define trace(x) (void)0
    #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
#endif

#define debugv(v) trace({cout << #v": "; for (auto x : v) cout<< x << " "; cout << ln;})
#define debug(x) trace(cout << __LINE__ << ": " #x " = " << x << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;

map<char, ll> mp = {{'I',1}, {'V', 5}, {'X', 10}, {'?',0 }};

void solve(){
    ll n, q; cin >> n >> q;
    string s; cin >> s;
    ll base_emp = 0;
    ll base_sum = 0;

    ll size = 0;
    ll ini = 'V';

    map<string, v64> blocks;

    forn(i,0,n-1){
        base_sum += mp[s[i]];
        if(s[i] == 'I' && (s[i+1] == 'V' || s[i+1] == 'X')){
            base_sum -= 2;
        }
        if(s[i] == '?'){
            base_emp++;
            size++;
            if(s[i+1] != '?'){
                string aux;
                aux.push_back(ini);
                aux.push_back(s[i+1] == 'I' ? 'I' : 'V');
                blocks[aux].push_back(size);
            }
        }else{
            ini = s[i];
            if(ini == 'X') ini = 'V';
            size = 0;
        }
    }

    base_sum += mp[s[n-1]];
    if(s[n-1] == '?'){
        base_emp++;
        size++;
        string aux;
        aux.push_back(ini);
        aux.push_back('I');
        blocks[aux].push_back(size);
    }

    ll natI = 0;
    ll natV = 0;
    ll natB = 0;
    ll paresbons = 0;
    natI = sz(blocks["IV"])+sz(blocks["VV"]);
    natV = sz(blocks["IV"])+sz(blocks["II"]);

    for(ll v: blocks["IV"]) if(v == 1){
        natI--;
        natV--;
        natB++;
    }

    for(ll v: blocks["IV"]) paresbons += (v-2)/2;
    for(ll v: blocks["II"]) paresbons += (v-1)/2;
    for(ll v: blocks["VV"]) paresbons += (v-1)/2;
    for(ll v: blocks["VI"]) paresbons += (v)/2;

    debug(base_emp);
    debug(base_sum);
    debug(natB);
    debug(natI);
    debug(natV);
    while(q--){
        ll c,b,a;
        cin >> c >> b >> a;
        ll emp = base_emp;
        ll curr_sum;
        
        if(a >= emp){
            a = emp;
            b = 0;
            c = 0;
        }
        emp -= a;
        
        
        if(b >= emp){
            b = emp;
            c = 0;
        }
        emp -= b;
        
        c = emp;
        curr_sum = a + 5*b + 10*c;
        b += c;

        curr_sum -= 2*min(natI, a);
        a -= min(natI, a);

        curr_sum -= 2*min(natV, b);
        b -= min(natV, b);

        ll pares = min(min(a,b), paresbons);
        curr_sum -= 2*pares;
        a -= pares;
        b -= pares;

        curr_sum -= 2*min(a+b, natB);
        cout << base_sum + curr_sum << ln;
    }
}

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}