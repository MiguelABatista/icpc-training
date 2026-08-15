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
    vll dp(n);
    deque<pll> dq; // {f,c} retas da forma fx+c = y

    auto clean_front = [&](ll z){
        if(sz(dq) < 2) return false;
        auto [f1, c1] = dq.front();
        dq.pop_front();
        auto [f2, c2] = dq.front();
        if(f1*z+c1 >= f2*z + c2) return true;
        dq.push_front({f1,c1});
        return false;
    };

    auto clean_back = [&](){
        if(sz(dq) < 3) return false;
        auto [f1, c1] = dq.back();
        dq.pop_back();
        auto [f2, c2] = dq.back();
        dq.pop_back();
        auto [f3, c3] = dq.back();

        //  -(c1-c3)/(f1-f3) <= -(c2-c3)/(f2 - f3) 
        if ((c1-c3)*(f2-f3) >= (c2-c3)*(f1-f3)){
            dq.push_back({f1,c1});
            return true;
        }
        dq.push_back({f2,c2});
        dq.push_back({f1,c1});
        return false;
    };

    dq.push_back({ff, 0});

    forn(i,0,n){
        while (clean_front(s[i]));
        auto [currf, currc] = dq.front();
        dp[i] = currf*s[i] + currc;
        dq.push_back({f[i], dp[i]});
        while(clean_back());
    }

    cout << dp[n-1] << ln;
    return 0;
}
