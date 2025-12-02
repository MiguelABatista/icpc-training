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

map<char, ll> mp = {{'I', 1}, {'V',5}, {'X',10}, {'?',0}};
void solve(){
    ll n, q; cin >> n >> q;
    string s;
    cin >> s;
    map<string, v64> blocks;

    ll basesum = 0;
    ll emp = 0;
    char ini = 'V';
    ll size = 0;

    forn(i,0,n-1){
        basesum += mp[s[i]];
        if(s[i] == 'I' && (s[i+1] == 'V' || s[i+1] == 'X')) basesum -= 2;
        
        if(s[i] == '?'){
            emp++;
            size++;
            if(s[i+1] != '?'){
                string aux(2,'*');
                aux[0] = ini;
                aux[1] = (s[i+1] == 'I' ? 'I' : 'V');
                blocks[aux].push_back(size); 
            }
        }else{
            size = 0;
            ini = s[i];
        }

    }
    if(s[n-1] == '?'){
        emp++;
        size++;
        string aux(2,'*');
        aux[0] = ini;
        aux[1] = 'I';
        blocks[aux].push_back(size); 
    }

    basesum += mp[s[n-1]];

    ll natI = 0;
    ll natV = 0;
    ll natB = 0;

    natI += sz(blocks["IV"]) + sz(blocks["VV"]);
    natV += sz(blocks["IV"]) + sz(blocks["II"]);

    for(ll v: blocks["IV"]) if(v == 1){
        natI--;
        natV--;
        natB++;
    }

    ll paresbons = 0;

    for(ll v: blocks["IV"]) paresbons += (v-2)/2;
    for(ll v: blocks["VV"]) paresbons += (v-1)/2;
    for(ll v: blocks["II"]) paresbons += (v-1)/2;
    for(ll v: blocks["VI"]) paresbons += (v)/2;

    ll true_emp = emp;
    ll true_natB = natB;
    debug(natI);

    debug(basesum);
    while(q--){
        emp = true_emp;
        natB = true_natB;
        ll a, b, c;
        cin >> c >> b >> a;
        ll currsum = 0;

        if(a >= emp){
            a = emp;
            emp = 0;
            currsum += a;
            b = 0;
            c = 0;
        }else {
            emp -= a;
            currsum+= a;
        }

        if(b >= emp){
            b = emp;
            emp = 0;
            currsum += 5*b;
            c = 0;
        }else{
            emp -= b;
            currsum += 5*b;
            currsum += emp*10;
            b += emp;   
        }

        debug(currsum);
        
        if(natI >= a){
            currsum -= 2*a;
            a = 0;
        }else{
            currsum -= 2*natI;
            a -= natI;
        }
        
        debug(currsum);
        debug(natB);
        debug(a);
        if(natB >= a){
            natB -= a;
            currsum -= 2*a;
            a = 0;
        }else{
            currsum -= 2*natB;
            a -= natB;
            natB = 0;
        }

        debug(currsum);
        debug(natB);
        debug(a);
        if(natV >= b){
            currsum -= 2*b;
            b = 0;
        }else{
            currsum -= 2*natV;
            b -= natV;
        }

        if(natB >= b){
            natB -= b;
            currsum -= 2*b;
            b = 0;
        }else{
            currsum -= 2*natB;
            b -= natB;
            natB = 0;
        }
        debug(currsum);

        currsum -= 2*min(min(a,b), paresbons);
        cout << currsum+basesum << ln;
    }
    trace(cout << ln;);
}

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}