#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64;
typedef vector<ll> v64;

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

int main() {
    _;
    string s; cin >> s;
    ll n = sz(s);

    v64 freq(26);
    forn(i,0,n) freq[s[i]-'A']++;

    string resp(n, ' ');

    forn(idx,0,n){
        ll proib = -1;
        
        if(idx > 0) proib = resp[idx-1]-'A'; 
        debug(idx);

        ll lim = INF;
        if((n-idx) % 2 == 1) lim = (n-idx+1)/2;
        
        debug(lim);

        forn(i,0,26){
            if(freq[i] == lim){
                if(proib == i){
                    cout << -1 << ln;
                    return 0;
                }
                resp[idx] = 'A'+i;
                freq[i]--;
            }
        }
        
        if(resp[idx] != ' ') continue;

        debug(proib);
        forn(i,0,26){
            if(proib == i) continue; 
            if(freq[i] == 0) continue; 
            resp[idx] = 'A'+i;
            freq[i]--;
            break;
        }

        if(resp[idx] == ' '){
            cout << -1 << ln;
            return 0;
        }
    }
    cout << resp << ln;
    return 0;
}
