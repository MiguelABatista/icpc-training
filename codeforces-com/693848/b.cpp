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
#define debugv(v) trace(cout << #v ": "; for (auto xx : v) cout << setw(2) << xx << " "; cout << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;


int main() {
    _;
    string s, r;
    cin >> s >> r;
    vll freqs(27);
    vll freqr(27);
    for(char c : s) freqs[c-'a']++;
    for(char c : r) freqr[c-'a']++;
        
    ll q; cin >> q;
    while(q--){
        ll t; cin >> t;
        if(t == 1){
            ll k; cin >> k;
            string aux; cin >> aux;
            for(char c : aux) freqs[c-'a'] += k;
        }
        if(t == 2){
            ll k; cin >> k;
            string aux; cin >> aux;
            for(char c : aux) freqr[c-'a'] += k;            
        }
        if(t == 3){
            trace(cout << "freqx: "; forn(i,0,26) cout << ' ' << char('a' + i) << " ";; cout << ln;)
            debugv(freqs);
            debugv(freqr);
            if(freqr == freqs){
                cout << "EMPATE" << ln;
                continue;
            }
            ll szs = 0;
            ll szr = 0;
            forn(i,0,26){
                szs += freqs[i];
                szr += freqr[i];
            }

            forn(i,0,26){
                szs -= freqs[i];
                szr -= freqr[i];
                if(szs == 0 && szr == 0){
                    if(freqs[i] < freqr[i]){
                        cout << "ADA" << ln;
                        break;
                    }
                    else{
                        cout << "PY" << ln;  
                        break;
                    }
                }
                if(szs == 0){
                    cout << "ADA" << ln;
                    break;
                }
                if(szr == 0){
                    cout << "PY" << ln;
                    break;
                }
                if(freqs[i] == freqr[i]) continue;

                if(freqs[i] > freqr[i]){
                    cout << "ADA" << ln;
                    break;
                }
                else{
                    cout << "PY" << ln;  
                    break;
                }
            }
        }
    }
    return 0;
}
