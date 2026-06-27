#include <bits/stdc++.h>
using namespace std;

// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("unrool-loops")

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
const ll MAX = 1'000'000;

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

    // auto menor_rep = [&](string ss){
    //     auto pi = find_pi(ss);
    //     int n = ss.size();
    //     int k = n - pi.back();
    //     if(n%k != 0) return ss;
    //     return ss.substr(0, k);
    // };

    // auto comp1 = menor_rep(s);
    // auto comp2 = menor_rep(t);


    // if(comp1 == comp2){
    //     cout << "=" << "\n";
    //     return 0;
    // }

    forn( i,0, min(MAX, p*sz(s)+q*sz(t))){
        char st = ' ';
        char ts = ' ';

        if(i < sz(s)*p) st = s[i%sz(s)];
        else st = t[(i-(sz(s)*p))%sz(t)];

        if(i < sz(t)*q) ts = t[i%sz(t)];
        else ts = s[(i-(sz(t)*q))%sz(s)];

        if(st < ts){
            cout << "<" << ln;
            return 0;
        }else if(ts < st){
            cout << ">" << ln;
            return 0;
        }
    }    
    cout << "=" << ln;
    return 0;
}