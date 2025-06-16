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

set<ll> badprimes = {1,7,11,13,17,19};

ll solve(v64 v, bool tem14){
    ll n = v.size();
	if(n == 0) return 0;
    ll best_resp = 0;
    do {
        ll curr = 0;
        forn(i,0,n-1){
            curr += gcd(v[i], v[i+1]); 
        }

        if(v[0] % 2 == 0 && tem14) curr += 2;
		else if(tem14) curr += 1;

        best_resp = max(best_resp, curr);
    } while (std::next_permutation(v.begin(), v.end()));
    return best_resp;
}

int main(){
    _;
    ll n; cin >> n;
    v64 freq(21,0);
	v64 valid;

	ll bad = 0;
    
	bool quatro = false;
	bool tem14 = false;
	
	ll algo = 0;

	forn(i,0,n){
        ll aux; cin >> aux;
        freq[aux]++;
    }

	if(freq[14] > 0 && freq[7] == 0){
		freq[2] += freq[14];
		algo += (14-2)*(freq[14]-1);
		freq[14] = 0;
	}

    forn(i,0,21){
        if(freq[i] == 0) continue;
		if(badprimes.count(i)){
            bad++;
            continue;
        }
        
		if(i == 4 || i == 8 || i == 16){
            quatro = true;
            continue;
        }

        if(i == 14){
			tem14 = true;
			continue;
		}
        valid.push_back(i);
    }

    if(quatro) valid.push_back(4);

    sort(valid.begin(), valid.end()); 

	algo += solve(valid, tem14);

	if((freq[16] || freq[8]) && freq[4])  algo += 4;
	if((freq[16] && freq[8]))  algo += 8;
    
    if(freq[14] && freq[7]) {
		algo += 7-1; // 7 ai fazer mdc=1 e agora vai fazer mdc=7
		valid.push_back(14);
	}

    algo += bad;

    if(valid.empty()) algo--; 
	
    forn(i,1,21){
        if(freq[i] == 0) continue;
        algo += i*(freq[i]-1);
    } 
 
    cout << algo << ln;
    return 0;
}