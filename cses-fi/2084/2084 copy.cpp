#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
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
#define debugm(v) trace(cout << #v ": "; for (auto xx : v) cout << xx.first << ":" << xx.second << " "; cout << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;

int main() {
    _;
    ll n, ff; cin >> n >> ff;
    vll s(n+1);
    vll f(n+1);

    forn(i,0,n) cin >> s[i];
    forn(i,0,n) cin >> f[i];

    vector<pll> st;
    st.push_back({0,ff});    
    vll dp(n,INF);


    auto recalc = [&](ll z){
        if(sz(st) < 2) return false;

        auto [t2, f2] = st.back(); st.pop_back();
        auto [t1, f1] = st.back(); st.pop_back();
        if(t1 + f1*z >= t2+f2*z){
            st.push_back({t2,f2});
            return true;
        }else{
            st.push_back({t1,f1});
            st.push_back({t2,f2});
            return false;
        }
    };

    forn(i,0,n){
        debug(i);
        debugm(st);
        while (recalc(s[i]));
        debugm(st);
        auto [t,cf] = st.back();
        
        dp[i] = t+s[i]*cf;

        st.push_back({dp[i], f[i]});
        trace(cout << "---------------\n\n";)
    }
    cout << dp[n-1] << ln;
    debugv(dp);
    return 0;
}
