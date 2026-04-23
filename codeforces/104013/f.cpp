#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pll;
typedef vector<ll> vll;

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
const ld eps = 1e-9;

ll cmp(ld x, ld y = 0, ld tol = eps){
    return(x <= y + tol) ? (x +tol < y) ? -1 : 0 : 1;
}

int main() {
    _; ll n;
    ld p;
    cin >> n >> p;
    vll c(n), diff_sq(n), acc(n);
    forn(i, 0, n) cin >> c[i];

    forn(i, 1, n){
        diff_sq[i] = (c[i] - c[i-1])*(c[i] - c[i-1]);
    }

    acc[0] = 0;
    forn(i, 1, n){
        acc[i] = diff_sq[i]+acc[i-1];
    }

    auto a = [&](ll l, ll r){
        return ((ld)(c[r] - c[l]))/(r-l);
    };

    auto d = [&](ll l, ll r){
        ld av_sq = ((ld)(acc[r] - acc[l]))/(r-l );
        ld av = a(l,r);

        return sqrt(av_sq - av*av);
    };

    ll pos = 0;
    ll neg = 0;
    forn(l, 0, n){

        forn(r, l+2, n){
            ld av = a(l, r);
            ld sd = d(l,r);
            trace(
                cout << setw(2)<< l << " " << r << ln;
                cout << fixed << setprecision(2) << av << " " << sd << " " << av/sd << ln;
            );
            if(av == 0) continue;
            if(sd == 0){
                if(av > 0) pos++;
                if(av < 0) neg++;
                continue;
            }
            
            if(cmp(av, p*sd)>= 0) pos ++;
            if(cmp(av, -p*sd)<= 0) neg ++;
        }
    }
  
    cout << pos << " " << neg << ln;

    return 0;
}
