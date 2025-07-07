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

bool testa(ll p1, ll p2, ll g, v64 l, v64 b){
    if(b[p1] + b[p2] == b[g]){
        if(l[p1] == l[p2] && (l[p1] + l[g] == b[g])){
            return true;
        }
    }
    return false;
}
void solve(){
    v64 l(3);
    v64 b(3);
    cin >> l[0] >> b[0] >> l[1] >> b[1] >> l[2] >> b[2];

    if(testa(0,1,2, l, b)){
        cout << "YES" << ln;
        return;
    }

    if(testa(0,2,1, l, b)){
        cout << "YES" << ln;
        return;
    }

    if(testa(1,2,0, l, b)){
        cout << "YES" << ln;
        return;
    }
    

    if(b[1] == b[0] && b[1] == b[2]){
        if(l[1] + l[2] + l[0] == b[1]){
            cout << "YES" << ln;
            return;
        }
    }

    swap(l, b);


    if(testa(0,1,2, l, b)){
        cout << "YES" << ln;
        return;
    }

    if(testa(0,2,1, l, b)){
        cout << "YES" << ln;
        return;
    }

    if(testa(1,2,0, l, b)){
        cout << "YES" << ln;
        return;
    }
    

    if(b[1] == b[0] && b[1] == b[2]){
        if(l[1] + l[2] + l[0] == b[1]){
            cout << "YES" << ln;
            return;
        }
    }

    cout << "NO" << ln;
}

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}