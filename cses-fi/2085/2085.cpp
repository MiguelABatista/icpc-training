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

// Convex Hull Trick Dinamico
//
// para double, use INF = 1/.0, div(a, b) = a/b
// update(x) atualiza o ponto de intersecao da reta x
// overlap(x) verifica se a reta x sobrepoe a proxima
// add(a, b) adiciona reta da forma ax + b
// query(x) computa maximo de ax + b para entre as retas
//
// O(log(n)) amortizado por insercao
// O(log(n)) por query

struct Line {
    mutable ll a, b, p;
    bool operator<(const Line& o) const { return a < o.a; }
    bool operator<(ll x) const { return p < x; }
};

struct CHT : multiset<Line, less<>> {
    ll div(ll a, ll b) { 
        return a / b - ((a ^ b) < 0 && a % b);
    }
    
    void update(iterator x) {
        if (next(x) == end()) x->p = INF;
        else if (x->a == next(x)->a) x->p = x->b >= next(x)->b ? INF : -INF;
        else x->p = div(next(x)->b - x->b, x->a - next(x)->a);
    }

    bool overlap(iterator x) {
        update(x);
        if (next(x) == end()) return 0;
        if (x->a == next(x)->a) return x->b >= next(x)->b;
        return x->p >= next(x)->p;
    }
        
    void add(ll a, ll b) {
        auto x = insert({a, b, 0});
        while (overlap(x)) erase(next(x)), update(x);
        if (x != begin() && !overlap(prev(x))) x = prev(x), update(x);
        while (x != begin() && overlap(prev(x))) 
            x = prev(x), erase(next(x)), update(x);
    }
    
    ll query(ll x) {
        assert(!empty());
        auto l = *lower_bound(x);
// #warning cuidado com overflow!
        return l.a * x + l.b;
    }
};

int main() {
    _;
    ll n, ff; cin >> n >> ff;
    vll s(n+1);
    vll f(n+1);

    forn(i,0,n) cin >> s[i];
    forn(i,0,n) cin >> f[i];
    vll dp(n);
    CHT cht;
    cht.add(-ff, 0);
    
    forn(i,0,n){
        dp[i] = -cht.query(s[i]);
        cht.add(-f[i], -dp[i]);
    }

    cout << dp[n-1] << ln;
    return 0;
}
