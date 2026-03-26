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

int main() {
    _;
    ll n; cin >> n;
    ll lb = 0;
    ll up = INF;

    forn(i,0,n){
        ll a, b;
        char c;
        cin >> a >> b >> c;
        if(c == 'E'){ 
            if((a+b)%2 == 0){
                lb = max(lb, (a+b)/2);
                up = min(up, (a+b)/2);
            }else{
                lb = INF;
                up = 0;
            }
        }
        if(c == 'A'){ // 1 2 3 4 5 6
            if((a+b)%2 == 0){
                up = min(up, (a+b)/2 - 1);
            }else{
                up = min(up, (a+b)/2);
            }
        }

        if(c == 'B'){
            if((a+b)%2 == 0){
                lb = max(lb, (a+b)/2 + 1);
            }else{
                lb = max(lb, (a+b)/2 + 1);
            }
        }
    }

    if(lb > up) cout << "*" << ln;
    else cout << lb << " " << up << ln;
    return 0;
}
