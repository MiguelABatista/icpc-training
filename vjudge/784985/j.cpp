// Perfomance geral (seguro p/ CP)
//  #pragma GCC optimize("O3,unroll-loops,fast-math")

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
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
#define debug(xx) trace(cout << __LINE__ << ": " #xx " = " << xx << ln)

const ld DINF = 1e9;
const ll MAXIT = 100;
const ld eps = 1e-12;

v64 a,b;
ll n, p, q; 

int cmp(double x, double y = 0, double tol = eps) {
	return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}

ld melhor(p64 p1, p64 p2, ld x){
    return cmp((1-p1.first*x)*p2.second, (1-p2.first*x)*p1.second) <= 0;
}

p64 f(ld x){
    p64 best = {0,1};
    forn(i, 0, n){
        if(melhor({a[i],b[i]}, best, x)){
            best = {a[i], b[i]};
        }
    }

    return best;
}

int main(){
    _;
    cin >> n >> p >> q;
    a.resize(n);
    b.resize(n);

    ll maxa = 0;

    forn(i,0,n) {
        cin >> a[i];
        cin >> b[i];

        maxa = max(maxa, a[i]);
    }

    ld l = 0, r = 1;

    forn(i, 0, MAXIT){
        ld m1 = (2*l + r)/3, m2 = (l + 2*r)/3;
        p64 p1 = f(m1);
        p64 p2 = f(m2);

        ld num1 = (1-p1.first*m1)*p + p1.second*m1*q;
        ld num2 = (1-p2.first*m2)*p + p2.second*m2*q;

        if(cmp(num1*p2.second, num2*p1.second) <= 0) l = m1;
        else r = m2;        
    }

    ld x = (l+r)/2;
    p64 best = f(x);
    ld ans = ((1-best.first*x)*p + q*x*best.second)/best.second; 
    ld teorical_ans;
    cout << fixed << setprecision(15) << ans << ln;

    cin >> teorical_ans;
    if(abs(ans - teorical_ans) < 0.000001){
        cout << 1 << ln;
    }else{ 
        cout << 0 << ln;
    }
    debug(ans);
    trace(
        cout << fixed << setprecision(15) << ans << ln;
        cout << fixed << setprecision(15) << teorical_ans << ln;
        cout << fixed << setprecision(15) << abs(ans - teorical_ans) << ln;
    );
    return 0;
}