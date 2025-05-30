#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64; 
typedef vector<ll> v64;

#define forn(i, s, e) for(ll i = (s); i < (e); i++)
#define ln "\n"

#if defined(DEBUG)
    #define _ (void)0
    #define debug(x) cout << __LINE__ << ": " << #x << " = " << x << ln
#else
    #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
    #define debug(x) (void)0
#endif

const ll INF = 0x3f3f3f3f3f3f3f3fll;

string binary(ll n){
    string bin;
    while(n>0){
        if(n%2 == 1) bin.push_back('1');
        else bin.push_back('0');
        n = n/2;
    }
    reverse(bin.begin(), bin.end());
    return bin;
}

ll num(string s){
    ll pot = 1, n = 0;
    reverse(s.begin(), s.end());
    for(auto c : s){
        if(c == '1') n+=pot;
        pot *= 2;
    }

    return n;
}

int main(){
    _; ll n; cin >> n;
    string bin = binary(n);
    // cout << bin << ln;

    ll m = bin.size();
    ll metade = m/2;
    if(m%2 == 1) metade++;

    string best_s;
    for(ll i = metade; i>=0; i--){
        // cout << i << ln;
        string s = "", revs = "";
        forn(j, 1, metade+1){
            if(j<i){
                s.push_back(bin[j-1]);
            }
            else if(j==i){
                s.push_back('0');
            }
            else{
                s.push_back('1');
            }
        }
        // cout << "pre palindromizacao: " << s << ln;
        revs = s;
        if(m%2 == 1) revs.pop_back();
        reverse(revs.begin(), revs.end());
        s = s+revs;
        // cout << "pos palindromizacao: " << s << ln;

        if(s <= bin and s >= best_s) best_s = s;
    }

    // cout << best_s << ln;
    cout << num(best_s) << ln;
    return 0;
}