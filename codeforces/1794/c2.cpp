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

    forn(i,0,n){
        ll resp = 1;
        frac best = vec[i];
        frac curr = vec[i];
        for(ll j = i-1; j >= 0; j--){
            curr = curr*frac(vec[j], i-j+1);
            if(best < curr || curr == best){
                resp = i-j+1;
                best = curr;
            }
        }
        cout << resp << " ";
    }
    cout << ln;
}

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}