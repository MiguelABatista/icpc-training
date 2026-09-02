#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<ll,ll> pll;
typedef vector<ll> vll;

#define forn(i,s,e) for(ll i=s;i<e;i++)
#define sz(u) ((ll) u.size())
#define ln "\n"

#ifdef DEBUG
#define trace(u) u
#define _
#else
#define trace(u)
#define _ ios::sync_with_stdio(0); cin.tie(0)
#endif

#define debug(u) trace(cout << #u " = " << u << ln);
#define debugv(v) trace(cout << #v ": "; for(auto xx : v) cout << xx << " "; cout << ln)
#define debugm(v) trace(cout << #v ": "; for(auto xx : v) cout << xx.first << ":" << xx.second << " "; cout << ln;)

const ld pi = 2*acos(0.0);
const ld eps = 1e-16;

void ler(ld& zz){
    string s; cin >> s;
    ll n = sz(s);

    string s1 = s.substr(0,n-3);
    string s2 = s.substr(n-2,2);
    ll x = stoi(s1);
    ll y = stoi(s2);
    zz = ld(x) + ld(y)/100;
}

void lerll(ll& zz){
    string s; cin >> s;
    ll n = sz(s);

    string s1 = s.substr(0,n-3);
    string s2 = s.substr(n-2,2);
    ll x = stoi(s1);
    ll y = stoi(s2);
    zz = x*100 + y;
}

ll cmp(ld x, ld y = 0, ld tol = eps){
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}

ld angle(ld x, ld y){
    ld ang = atan2(y,x);
    if(cmp(ang,0) < 0) ang += 2*pi;
    return ang;
}

bool comp(ld x, ld y){
    return (cmp(x,y) < 0);
}

struct ang{
    ld a;
    ang(ld a_) : a(a_) {};

    bool operator < (const ang a_) const{
        return (cmp(a,a_.a) < 0);
    }
};

int main(){
    _;
    ll n;
    ld h;  
    cin >> n;
    ler(h);

    vector<tuple<ld, ld, ld>> vec(n);
    forn(i,0,n){
        ld a, b, c;
        ler(a);
        ler(b);
        ler(c);
        vec[i] = {c,a,b};
    }
    
    ld cx, cy;
    ler(cx); ler(cy);
    sort(vec.rbegin(), vec.rend());

    set<ang> s;

    auto pega = [&](ld t){
        auto it = s.lower_bound(ang(t));

        if(it == s.begin()) return ang(-1);
        return *prev(it);
    };

    forn(i,0,n){
        auto [hh, x, y] = vec[i];
        x -= cx;
        y -= cy;
        ld angulo = angle(x,y);
        
        ang a = pega(angulo+pi);
        ang b = pega(a.a + pi);

        if(cmp(b.a, pi + angulo) > 0){
            cout << fixed << setprecision(15) << max(h - hh, ld(0)) << ln;
            return 0;
        }

        s.insert(angulo);
        s.insert(angulo+2*pi);
        s.insert(angulo+4*pi);   
    }

    cout << -1 << ln;
}

 