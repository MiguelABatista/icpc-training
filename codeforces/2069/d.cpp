#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64; 
typedef vector<ll> v64;

#define forn(i, s, e) for(ll i = (s); i < (e); i++)
#define ln "\n"

#if defined(DEBUG) || defined(debug)
    #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
    #define debug(x) cout << __LINE__ << ": " << #x << " = " << x << ln
#else
    #define _ (void)0
    #define debug(x) (void)0
#endif

const ll INF = 0x3f3f3f3f3f3f3f3fll;
void solve(){
    string s; 
    string alph = "abcdefghijklmnopqrstuvwxyz";
    cin >> s;
    ll n = s.size();

    ll p1 = 0;
    ll p2 = n-1;
    while(p1 <= p2){
        if(s[p1] == s[p2]){
            p1++;
            p2--;
            continue;
        }
        break;
    }

    s = s.substr(p1, p2-p1+1);
    n = s.size();
    
    if(n==0){
        cout << 0 << ln;
        return;
    }
    if(n==2){
        cout << 1 << ln;
        return;
    }
    
    ll metade = n/2;

    map<char, ll> freq;
    
    for(char c: s) freq[c]++;

    map<char,ll> freq_esq;
    map<char,ll> freq_dir;

    forn(i,0,metade) freq_esq[s[i]]++;
    forn(i,metade,n) freq_dir[s[i]]++;

    p1 = metade-1;
    p2 = metade;
    ll resp = INF;
    while(p1 > 0 && p2 < n){
        if(s[p1] != s[p2]) break;
        bool valid = true;
        freq_esq[s[p1]]--;
        freq_dir[s[p2]]--;
        p1--;
        p2++;
        for(auto c : alph){
            if(freq_esq[c] != freq_dir[c]){
                valid = false;
            }
        }
        if(valid){
            resp = min(resp, p1+1);
        }
    }

    if(resp != INF){
        cout << resp << ln;
        return;
    }
    
    freq_dir.clear();
 
    forn(i,metade-1,n){
        freq_dir[s[i]]++;
    }

    forn(i,metade-1,n){
        freq_dir[s[i]]--;
        bool valid = true;

        for(char c: alph){
            ll aux = freq[c] - 2*freq_dir[c];
            debug(aux);
            if(aux < 0 || aux%2 != 0) valid = false;
        }

        if(valid){
            resp = min(resp, i+1);
        }
    }

    reverse(s.begin(), s.end());

    freq_dir.clear();
 
    forn(i,metade-1,n){
        freq_dir[s[i]]++;
    }

    forn(i,metade-1,n){
        freq_dir[s[i]]--;
        bool valid = true;

        for(char c: alph){
            ll aux = freq[c] - 2*freq_dir[c];
            debug(aux);
            if(aux < 0 || aux%2 != 0) valid = false;
        }

        if(valid){
            resp = min(resp, i+1);
        }
    }

    cout << resp << ln;
}


int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}