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

#define debugv(v) trace({cout << #v": "; for (auto x : v) cout<< x << " "; cout << ln;})
#define debug(x) trace(cout << __LINE__ << ": " #x " = " << x << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;

// Fracao
//
// Funciona com o Big Int

template<typename T = ll> struct frac {
	T num, den;
	frac(ll num_ = 0,ll den_ = 1) : num(num_), den(den_) {
		assert(den != 0);
		if (den < 0) num *= -1, den *= -1;
		T g = gcd(abs(num), den);
		num /= g, den /= g;
	}

	friend bool operator<(const frac& l, const frac& r) {
		return l.num * r.den < r.num * l.den;
	}
    friend bool operator==(const frac& l, const frac& r) {
		return l.num * r.den == r.num * l.den;
	}
	friend frac operator+(const frac& l, const frac& r) {
		return {l.num*r.den + l.den*r.num, l.den*r.den};
	}
	friend frac operator-(const frac& l, const frac& r) {
		return {l.num*r.den - l.den*r.num, l.den*r.den};
	}
	friend frac operator*(const frac& l, const frac& r) {
		return {l.num*r.num, l.den*r.den};
	}
	friend frac operator/(const frac& l, const frac& r) {
		return {l.num*r.den, l.den*r.num};
	}
	friend ostream& operator<<(ostream& out, frac f) {
		out << f.num << '/' << f.den;
		return out;
	}
};

void solve(){
    ll n; cin >> n;
    v64 vec(n);
    forn(i,0,n) cin >> vec[i];
    vector<pair<frac<ll>, ll>> dp(n);

    dp[0] = {frac(vec[0],1), 1};

    forn(i,1,n){
        if(dp[i-1].first*frac(vec[i],(dp[i-1].second+1)) < frac(vec[i],1)){ // dp[i-1].first < dp[i-1].second+1
            dp[i] = {frac(vec[i], 1), 1}; 
        }else if(dp[i-1].first*frac(vec[i],(dp[i-1].second+1)) == frac(vec[i],1)){ // dp[i-1].first == dp[i-1].second+1
            dp[i] = {frac(vec[i], 1), 1};
        }else{ 
            dp[i] = {dp[i-1].first*frac(vec[i],(dp[i-1].second+1)), dp[i-1].second+1};
            while(dp[i].second > 1){
                if(vec[i-dp[i].second+1] == dp[i].second) dp[i].second--;
                else break;
            }
        }
    }

    forn(i,0,n){
        ll resp = dp[i].second;
        while (i - resp >= 0 && vec[i-resp] == resp+1){
            resp++; 
        }
        cout << resp << " ";
    }

    cout << ln;
    trace(
    forn(i,0,n){
        cout << dp[i].first << " : " << dp[i].second << ln; 
    }
    cout << "----------------\n\n"; 
    );
}

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}