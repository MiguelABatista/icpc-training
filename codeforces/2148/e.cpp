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

void solve(){
    ll n, k; cin >> n >> k;
    v64 vec(n);
    forn(i,0,n){
        cin >> vec[i];
        vec[i]--;
    }
    v64 freq(n);
    v64 target(n);
    forn(i,0,n) freq[vec[i]]++;
    
    forn(i,0,n) if(freq[i] != 0){
        if(freq[i]%k != 0){
            cout << 0 << ln;
            return;
        }
        target[i] = freq[i]/k;
    }

    debug(1);
    v64 freq2(n);
    ll p1 = 0;
    ll p2 = 0;
    freq2[vec[0]]++;
    ll resp = 1;
    while(p1 < n && p2 < n){
        // trace(cout << p1 << " " << p2 << ln;);
        // debugv(freq2);
        if(p2 < n-1 && freq2[vec[p2+1]] + 1 <= target[vec[p2+1]]){
            trace(cout << "EBA: " << p1 << " " << p2+1 << ln;);
            p2++;
            freq2[vec[p2]]++;
            resp += p2-p1+1;
            continue;
        }  
        freq2[vec[p1]]--;
        p1++;
    }
    cout << resp << ln;
    trace(cout << "-------------\n\n");
}

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}