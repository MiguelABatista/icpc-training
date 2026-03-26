#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64;
typedef vector<ll> v64;

#define forn(i, s, e) for (ll i = (s); i < (e); i++)
#define sz(u) ((ll) u.size())
#define ln "\n"

#ifdef DEBUG
#define trace(u) u
#define _
#else
#define trace(u)
#define _ ios::sync_with_stdio(0); cin.tie(0)
#endif

#define debug(u) trace(cout << #u " = " << u << ln)
#define debugv(v) trace(cout << #v ": "; for (auto xx : v) cout << xx << " "; cout << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;

void solve(){
    ll n, a, b;
    cin >> n >> a >> b;
    
    if(a + b > n){
        cout << "NO" << ln;
        return;
    }

    bool to_swap = false;
    if(a > b){
        swap(a,b);
        to_swap = true;
    }

    if(a == 0){
        if(b != 0){
            cout << "NO" << ln;
            return;
        }
        cout << "YES" << ln;
        forn(i,1,n+1) cout << i << " ";; cout << ln;
        forn(i,1,n+1) cout << i << " ";; cout << ln;
        return;
    }
    
    v64 vec(n, -1);
    forn(i,0,n) vec[i] = i;
    ll aux = min(a,b) - 1;

    forn(i,0,aux) swap(vec[2*i], vec[2*i+1]);
    
    a -= aux;
    b -= aux;

    ll start = 2*aux;
    ll end = start+a+b-1;
    ll mem = vec[end];
    for(ll i = end; i > start; i--) vec[i] = vec[i-1];
    vec[start] = mem;

    cout << "YES" << ln;
    if(to_swap){
        forn(i,1,n+1) cout << i << " ";
        cout << ln;
    }
    forn(i,0,n) cout << vec[i]+1 << " ";; cout << ln;

    if(!to_swap){
        forn(i,1,n+1) cout << i << " ";
        cout << ln;
    }
    return;
    ll ta = 0;
    ll tb = 0;

    forn(i,0,n){
        if(vec[i] > i) ta++;
        if(vec[i] < i) tb++;
    }
    if(to_swap){
        cout << tb << " " << ta << ln;
    }else{
        cout << ta << " " << tb << ln;
    }
} 

int main() {
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}
