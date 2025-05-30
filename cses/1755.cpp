#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64; 
typedef vector<ll> v64;

#define forn(i, s, e) for(ll i = (s); i < (e); i++)
#define ln "\n"

#if defined(DEBUG) || defined(debug)
    #define _ (void)0
    #define debug(x) cout << __LINE__ << ": " << #x << " = " << x << ln
#else
    #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
    #define debug(x) (void)0
#endif

const ll INF = 0x3f3f3f3f3f3f3f3fll;

int main(){
    _;
    ll n;
    string s;
    cin >> s;
    n = s.size();

    map<char, ll> freq;

    forn(i,0,n) freq[s[i]]++;
    
    char c = '#';

    for(auto p: freq){
        if(p.second%2 == 1 && c != '#'){
            cout << "NO SOLUTION" << ln;
            return 0;
        }else if(p.second%2 == 1){
            c = p.first;
        }
    }

    string s2;

    for(auto p: freq){
        if(p.first == c) continue; 
        forn(i,0,p.second/2){
            s2.push_back(p.first);
        }
    }

    cout << s2;

    debug(c);
    debug(freq[c]);
    forn(i,0,freq[c]) cout << c;
    
    reverse(s2.begin(), s2.end());
    cout << s2;
    return 0;
}