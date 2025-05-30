#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64; 
typedef vector<ll> v64;
typedef long double ld;

#define forn(i, s, e) for(ll i = (s); i < (e); i++)
#define ln "\n"

#if defined(DEBUG)
    #define _ (void)0
    #define debug(x) cout << fixed << setprecision(10) << __LINE__ << ": " << #x << " = " << x << ln
#else
    #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
    #define debug(x) (void)0
#endif

const ll INF = 0x3f3f3f3f3f3f3f3fll;
const ld pi = 2*acos((double)0.0);

ld comp(ld n1, ld n2, ld n3, ld f){
    // cout << f << " " << n1 << " " << n2 << " " << n3;
    // debug(abs(f - 1/n1 + 1/n2 - 1/n3));
    return fabs(f - 1/n1 + 1/n2 - 1/n3);
}

int main(){
    _;
    ll r,s, h_dia; cin >> r >> s >> h_dia;
    
    ld circ = 2*pi*r;
    ld h_ano = circ/s;
    ld ano_real = h_ano/h_dia;
  
    ld f = ano_real - floor(ano_real);

    if( f >= 0.5) f = 1 - f;

    ll bn1 = 0;
    ll bn2 = 0;
    ll bn3 = 0;
    ld bscore = 10; 

    forn(n1, 2, 1001){
        forn(n2,2, (1000+n1)/n1){
            forn(n3, 2, (1000+n1*n2)/n1*n2){
                if(n1*n2*n3 > 1000) continue;
                if(comp(n1, n1*n2, n1*n2*n3, f) < bscore){
                    bn1 = n1;
                    bn2 = n1*n2;
                    bn3 = n1*n2*n3;
                    bscore = comp(n1, n1*n2, n1*n2*n3, f);
                    debug(bscore);
                }
            }
        }
    }

    cout << bn1 << " " << bn2 << " " << bn3 << ln;
    return 0;
}