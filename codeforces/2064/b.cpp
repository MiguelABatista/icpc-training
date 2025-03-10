#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64; 
typedef vector<ll> v64;

#define forn(i, s, e) for(ll i = (s); i < (e); i++)
#define ln "\n"

#if defined(DEBUG) || defined(debug)
    #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
    #define debug(x) cout << __LINE__ << ": " << #x << " = " << x << ln
#else
    #define _ (void)0
    #define debug(x) (void)0
#endif

const ll INF = 0x3f3f3f3f3f3f3f3fll;

void solve(){
    ll n;
    cin >> n;
    
    v64 vec(n);
    map<ll, ll> freq;
    
    forn(i,0,n){
        cin >> vec[i];
        freq[vec[i]] += 1;
    }

    if(n == 1){
        cout << 1 << ' ' << 1 << ln;
        return;
    }

    v64 aux(n, 0);

    forn(i,0,n){
        if(freq[vec[i]] > 1) aux[i] = 1;
        //cout << aux[i] << ' ';
    }
    //cout << ln;
    ll max_size = 0;
    ll max_p1 = 0, max_p2 = 0;
    ll p1 = 0, p2 = 0;
    ll size = 0;
    while(p1 < n && p2 < n){
        if(aux[p2] == 0){
            p2++;
            size++;
            continue;
        }
        
        if(size == max_size){
            if(p2-p1 > max_p2 - max_p1){
                max_size = size;
                max_p1 = p1;
                max_p2 = p2;
            }
        }
        if(size > max_size){
            max_size = size;
            max_p1 = p1;
            max_p2 = p2;
        }
        size = 0;
        while(p2 < n && aux[p2] == 1){
            p2++;
        }
        p1 = p2;
        
    }

    if(size == max_size){
        if(p2-p1 > max_p2 - max_p1){
            max_size = size;
            max_p1 = p1;
            max_p2 = p2;
        }
    }
    if(size > max_size){
        max_size = size;
        max_p1 = p1;
        max_p2 = p2;
    }
    
    max_p1++;
    
    if(max_size == 0){
        cout << 0 << ln;
        return;
    }
    else{
        cout << max_p1 << ' ' << max_p2 << ln;
    }
}

int main(){
    _;
    ll t; cin >> t;
    while(t--){
        solve();
    }
    return 0;
}