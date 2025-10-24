#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
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

#define debug(x) trace(cout << __LINE__ << ": " #x " = " << x << ln)
#define debugv(v) trace({cout << #v": "; for (auto x : v) cout << x << " ";;cout << ln})

const ll INF = 0x3f3f3f3f3f3f3f3fll;
const ll BOUND = 1'000'000'000;

vector<p64> queen;
ll n;

vector<p64> candidates(p64 p, p64 q){
    vector<p64> cand;

    ll v = p.first;
    ll h = p.second;
    ll d1 = p.first-p.second;
    ll d2 = p.first+p.second;

    cand.push_back({v, q.second});
    cand.push_back({v, v+q.second-q.first});
    cand.push_back({v, -v+q.second+q.first});

    cand.push_back({q.first,h});
    cand.push_back({h+q.first - q.second,h});
    cand.push_back({-h+q.first + q.second,h});

    cand.push_back({q.first, q.first-d1});
    cand.push_back({d1+q.second, q.second});
    if((d1+q.first+q.second)%2==0) cand.push_back({(d1+q.first+q.second)/2, (-d1+q.first+q.second)/2});

    cand.push_back({q.first, -q.first+d2});
    cand.push_back({d2-q.second, q.second});
    if((d2+q.first+q.second)%2==0) cand.push_back({(d2+q.first-q.second)/2, (d2-q.first+q.second)/2});

    return cand;
}

bool inbounds(p64 p){
    if( abs(p.first) > BOUND) return false;
    if( abs(p.second) > BOUND) return false;
    return true;
}

bool attack(p64 p, p64 q){
    if(p.first == q.first) return true;
    if(p.second == q.second) return true;
    if(p.first - p.second == q.first - q.second) return true;
    if(p.first + p.second == q.first + q.second) return true;
    return false;
}

bool test(p64 p){
    bool fail = false;
    if(!inbounds(p)) return false;
    forn(i, 0, n) if(!attack(p, queen[i])) fail = true;
    return !fail;
}

void print(p64 p){
    // cout << "YES\n"; 
    if(!test(p)) assert(false);
    cout << "YES\n" << p.first << " " << p.second << ln; 
}

void solve_v(ll v){
    if(n == 2){
        print(queen[0]);
        return;
    }
    ll found_queen = -1;
    forn(i, 2, n) if(queen[i].first != v) found_queen = i;
    if(found_queen == -1){
        print(queen[0]);
        return;
    }

    p64 q = queen[found_queen];
    vector<p64> cand = candidates(queen[0], queen[1]);

    cand.push_back({v, q.second});
    cand.push_back({v, v+q.second-q.first});
    cand.push_back({v, -v+q.second+q.first});

    bool deu_bom = false;
    for(auto p : cand){
        deu_bom = test(p);
        if(deu_bom){
            print(p);
            return;
        }
    }

    cout << "NO" << ln;
    return;
}

void solve_h(ll h){
    if(n == 2){
        print(queen[0]);
        return;
    }
    ll found_queen = -1;
    forn(i, 2, n) if(queen[i].second != h) found_queen = i;
    if(found_queen == -1){
        print(queen[0]);
        return;
    }

    p64 q = queen[found_queen];
    vector<p64> cand = candidates(queen[0], queen[1]);


    cand.push_back({q.first,h});
    cand.push_back({h+q.first - q.second,h});
    cand.push_back({-h+q.first + q.second,h});

    bool deu_bom = false;
    for(auto p : cand){
        deu_bom = test(p);
        if(deu_bom){
            print(p);
            return;
        }
    }

    cout << "NO" << ln;
    return;
}

void solve_d1(ll d){
    if(n == 2){
        print(queen[0]);
        return;
    }
    ll found_queen = -1;
    forn(i, 2, n) if(queen[i].first - queen[i].second != d) found_queen = i;
    if(found_queen == -1){
        print(queen[0]);
        return;
    }

    p64 q = queen[found_queen];
    vector<p64> cand = candidates(queen[0], queen[1]);


    cand.push_back({q.first, q.first-d});
    cand.push_back({d+q.second, q.second});

    if((d+q.first+q.second)%2==0) cand.push_back({(d+q.first+q.second)/2, (-d+q.first+q.second)/2});

    bool deu_bom = false;
    for(auto p : cand){
        deu_bom = test(p);
        if(deu_bom){
            print(p);
            return;
        }
    }

    cout << "NO" << ln;
    return;
}

void solve_d2(ll d){
    if(n == 2){
        print(queen[0]);
        return;
    }
    ll found_queen = -1;
    forn(i, 2, n) if(queen[i].first + queen[i].second != d) found_queen = i;
    if(found_queen == -1){
        print(queen[0]);
        return;
    }

    p64 q = queen[found_queen];
    vector<p64> cand = candidates(queen[0], queen[1]);


    cand.push_back({q.first, -q.first+d});
    cand.push_back({d-q.second, q.second});

    if((d+q.first+q.second)%2==0) cand.push_back({(d+q.first-q.second)/2, (d-q.first+q.second)/2});

    bool deu_bom = false;
    for(auto p : cand){
        deu_bom = test(p);
        if(deu_bom){
            print(p);
            return;
        }
    }

    cout << "NO" << ln;
    return;
}

void solve_diff(){
    vector<p64> cand = candidates(queen[0], queen[1]);

    // for(auto p : cand) cout << "(" << p.first << ", " << p.second << ")\n";

    bool deu_bom = false;
    for(auto p : cand){
        deu_bom = test(p);
        if(deu_bom){
            print(p);
            return;
        }
    }

    cout << "NO" << ln;
    return;
}

void solve(){
    cin >> n;
    queen.clear();
    queen.resize(n);
    forn(i, 0, n) cin >> queen[i].first >> queen[i].second;

    if(n==1){
        print(queen[0]);
        return;
    }

    if(queen[0].first == queen[1].first){
        solve_v(queen[0].first);
        return;
    }

    if(queen[0].second == queen[1].second){
        solve_h(queen[0].second);
        return;
    }

    if(queen[0].first - queen[0].second == queen[1].first - queen[1].second){
        solve_d1(queen[0].first - queen[0].second);
        return;
    }

    if(queen[0].first + queen[0].second == queen[1].first + queen[1].second){
        solve_d2(queen[0].first + queen[0].second);
        return;
    }

    solve_diff();
}

int main() {
    _; ll t; cin >> t;
    while(t--) solve();
    return 0;
}