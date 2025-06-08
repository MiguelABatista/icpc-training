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

string s;
ll n, q;

void anda(ll &p, char c){
    while(p < n && s[p] != c) p++;
}

void solve(){
    
    cin >> n >> q;
    cin >> s;

    map<char, set<ll>> cidx;
    map<string, set<ll>> qtime;
    
    forn(i,0,n) cidx[s[i]].insert(i);

    forn(i,0,q){
        char x,y;
        cin >> x >> y;
        if(x == 'a') continue;
        if(x == y) continue;
        string aux(2,'a');
        aux[0] = x;
        aux[1] = y;
        qtime[aux].insert(i);
    }

    forn(i,0,n){
        debug(s);
        if(s[i] == 'a') continue;
        if(s[i] == 'b'){
            // quero b -> a
            if(qtime["ba"].size() > 0){
                s[i] = 'a';
                qtime["ba"].erase(qtime["ba"].begin());
                continue;
            }

            // quero b -> c -> a
            auto it = qtime["bc"].begin();
            if(it == qtime["bc"].end()) continue;

            ll t = *it;
            auto it2 = qtime["ca"].lower_bound(t); 
            
            if(it2 == qtime["ca"].end()) continue;

            s[i] = 'a';
            qtime["bc"].erase(it);
            qtime["ca"].erase(it2);
        }
    
        if(s[i] == 'c'){
            ll t = INF;
            // quero c -> a
            if(qtime["ca"].size() > 0){
                s[i] = 'a';
                qtime["ca"].erase(qtime["ca"].begin());
                continue;
            }
            // quero c -> b
            if(qtime["cb"].size() > 0){
                s[i] = 'b';
                auto it = qtime["cb"].begin();
                t = *it;
                qtime["cb"].erase(qtime["cb"].begin());
            }

            // se c -> b tenta b -> a
            if(s[i] != 'b') continue;
            
            auto it2 = qtime["ba"].lower_bound(t);
            if(it2 == qtime["ba"].end()) continue;

            s[i] = 'a';
            qtime["ba"].erase(it2);
            
        }
    }
    cout << s << ln;
}

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}