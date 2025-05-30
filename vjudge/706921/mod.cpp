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
const ll MOD = 1'000'000'000+7;

struct pt { // ponto
	ll x, y;
	pt(ll x_ = 0, ll y_ = 0) : x(x_), y(y_) {}
	bool operator < (const pt p) const {
		if (x != p.x) return x < p.x;
		return y < p.y;
	}
	bool operator == (const pt p) const {
		return x == p.x and y == p.y;
	}
	pt operator + (const pt p) const { return pt(x+p.x, y+p.y); }
	pt operator - (const pt p) const { return pt(x-p.x, y-p.y); }
	pt operator * (const ll c) const { return pt(x*c, y*c); }
	ll operator * (const pt p) const { return x*(ll)p.x + y*(ll)p.y; }
	ll operator ^ (const pt p) const { return x*(ll)p.y - y*(ll)p.x; }
	friend istream& operator >> (istream& in, pt& p) {
		return in >> p.x >> p.y;
	}
};

struct llm {
    ll val;

    llm(ll v = 0) : val((v % MOD + MOD) % MOD) {}

    bool operator==(const llm& p) const { return val == p.val; }

    llm operator+(const llm& p) const {
        ll aux = val + p.val;
        return (aux < MOD) ? llm(aux) : llm(aux - MOD);
    }

    llm operator-(const llm& p) const {
        ll aux = val - p.val;
        return (aux >= 0) ? llm(aux) : llm(aux + MOD);
    }

    llm operator*(const llm& p) const {
        return llm(val * p.val % MOD);
    }

    friend istream& operator>>(istream& in, llm& p) {
        ll x;
        in >> x;
        p = llm(x);
        return in;
    }

    friend ostream& operator<<(ostream& out, const llm& p) {
        return out << p.val;
    }
};

int main(){
    _;

}