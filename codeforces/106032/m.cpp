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
#define debugp(v) trace({cout << #v": "; for (auto x : v) cout<< x.first << ":" << x.second << " "; cout << ln;})
#define debug(x) trace(cout << __LINE__ << ": " #x " = " << x << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;

void solve(){
    ll n; cin >> n;
    map<char, ll> mpa;
    map<char, ll> mpb;
    ll tota = 0;
    ll totb = 0;

    forn(i,0,n){
        ll t;
        string s;
        ll k;
        cin >> t >> s >> k;
        if(t == 1){
            for(char c: s){
                mpa[c] += k;
                tota += k;
            }
        }else{
            for(char c: s){
                mpb[c] += k;
                totb += k;
            }
        }
        debugp(mpa);
        debugp(mpb);
        bool found = false;
        ll curra = 0;
        ll currb = 0;
        forn(j,0,26){
            char c = 'a'+j;
            curra += mpa[c];
            currb += mpb[c];


            if(mpa[c] > mpb[c]){
                if(currb == totb){
                    found = true;
                    cout << "Bob" << ln;
                    break;
                }else{
                    cout << "Alice" << ln;
                    found = true;
                    break;
                }
            }

            if(mpa[c] < mpb[c]){
                if(curra == tota){
                    found = true;
                    cout << "Alice" << ln;
                    break;
                }else{
                    cout << "Bob" << ln;
                    found = true;
                    break;
                }
            }
        }
        if(!found) cout << "Tie" << ln;
    }
    
}

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}