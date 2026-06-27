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

const ll INF = 0x3f3f3f3f3f3f3f3fll;

vector<int> find_pi(string s){
    vector<int> pi(s.size());
    for(int i = 1, j = 0; i < s.size(); i++){
        while (j > 0 && s[i] != s[j]) j = pi[j-1];
        if(s[j] == s[i]) j++;
        pi[i] = j;
    }
    return pi;
}

int main() {

    string s, t; cin >> s >> t;
    int p, q; cin >> p >> q;

    auto menor_rep = [&](string s){
        auto pi = find_pi(s);
        int n = s.size();
        int k = n - pi.back();
        if(n%k != 0) return s;
        return s.substr(0, k);
    };

    auto comp1 = menor_rep(s);
    auto comp2 = menor_rep(t);

    // cout << "debug: " << comp1 << " " << comp2 << "\n";

    if(comp1 == comp2){
        cout << "=" << "\n";
        return 0;
    }

    auto extend = [](string &s, int x){
        string novo;
        for(int i = 0; i < x; i++) novo += s;
        return s;
    };

    if(s.size() > t.size()){
        s = extend(s, min(p, 10));
        int quant = 1;
        string novo = t;
        while(quant < q && novo.size() < s.size()) {novo += t; quant++;}
        t = novo;
    }else if(t.size() > s.size()){
        t = extend(t, min(q, 10));
        int quant = 1;
        string novo = s;
        while(quant < p && novo.size() < t.size()) {novo += s; quant++;}
        s = novo;
    }

    auto porra = s + t;
    t += s;
    s = porra;

    for(int i = 0; i < min(s.size(), t.size()); i++){
        if(s[i] == t[i]) continue;
        if(s[i] < t[i]){
            cout << "<\n";
            return 0;
        }else{
            cout << ">\n";
            return 0;
        }
    }
    
    assert(0);

    return 0;
}