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

    ll true_emp = 0;
    
    forn(i,0,n) true_emp += (s[i] == '?');

    while(q--){
        ll emp = true_emp;

        ll a, b, c;
        cin >> c >> b >> a;
        vector<char> aux;
        if(a >= emp){
            a = emp;
            b = 0;
            c = 0;
        }else{
            emp -= a;
        }

        if(b >= emp){
            b = emp;
            c = 0;
        }else{
            emp -= b;
        }
        c = emp;

        forn(i,0,a) aux.push_back('I');
        forn(i,0,b) aux.push_back('V');
        forn(i,0,c) aux.push_back('X');
        
        ll resp = INF;
        function<ll (void)> comp = [&](){
            ll cnt = 0;
            string s2 = s;
            forn(i,0,n) if(s2[i] == '?') s2[i] = aux[cnt++];
            
            ll sum = 0;
            
            forn(i,0,n-1){
                sum += mp[s[i]];                
                if(s[i] == 'I' && (s[i+1] == 'V' || s[i+1] == 'X')) sum -= 2;
            }

            sum += mp[s[n-1]];
            return sum;
        };

        do {
            resp = min(resp, comp());
        }while(next_permutation(aux.begin(), aux.end()));
        cout << resp << ln;
    }
}

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}