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

struct trie {
	vector<v64> to;
	v64 end, pref;
	ll sigma; char norm;

	trie(ll sigma_=26, char norm_='a') : sigma(sigma_), norm(norm_) {
		to = {v64(sigma)};
		end = {0}, pref = {0};
	}

	void insert(string s) {
		ll x = 0;
		for (auto c : s) {
			ll &nxt = to[x][c-norm];
			if (!nxt) {
				nxt = to.size();
				to.push_back(v64(sigma));
				end.push_back(0), pref.push_back(0);
			}
			x = nxt, pref[x]++;
		}
		end[x]++, pref[0]++;
	}

	void erase(string s) {
		ll x = 0;
		for (char c : s) {
			ll &nxt = to[x][c-norm];
			x = nxt, pref[x]--;
			if (!pref[x]) nxt = 0;
		}
		end[x]--, pref[0]--;
	}

	ll find(string s) {
		ll x = 0;
		for (auto c : s) {
			x = to[x][c-norm];
			if (!x) return -1;
		}
		return x;
	}

	ll count_pref(string s) {
		ll id = find(s);
		return id >= 0 ? pref[id] : 0;
	}
};

int main(){
    _;
    return 0;
}