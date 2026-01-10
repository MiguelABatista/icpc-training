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
const ll MOD = 1e9+7;

template<int p> struct mod_int {
    ll expo(ll b, ll e) {
        ll ret = 1;
        while(e){
            if(e%2) ret = ret * b % p;
            e /= 2, b = b*b % p;
        }
        return ret;
    }
    ll inv(ll b) { return expo(b, p-2);}

    using m = mod_int;
    ll v;
    mod_int() : v(0) {}
    mod_int(ll v_) {
        if(v_ >= p or v_ <= -p) v_ %= p;
        if(v_ < 0) v_ += p;
        v = v_;
    }
    m& operator += (const m& a){
        v += a.v;
        if(v >= p) v -=p;
        return *this;
    }
    m& operator -= (const m& a){
        v -= a.v;
        if(v < 0) v +=p;
        return *this;
    }
    m& operator *= (const m& a){
        v = v * ll(a.v) % p;
        return *this;
    }
    m& operator /= (const m& a){
        v = v * inv(a.v) % p;
        return *this;
    }
    m operator -(){ return m(-v); }
    m& operator ^=(ll e){
        if(e<0){
            v = inv(v);
            e = -e;
        }

        v = expo(v, e);
        return *this;
    }

    friend ostream& operator << (ostream& out, m a){
        return out << a.v;
    }

    friend m operator +(m a, m b){ return a += b; }
    friend m operator -(m a, m b){ return a -= b; }
    friend m operator *(m a, m b){ return a *= b; }
    friend m operator /(m a, m b){ return a /= b; }
    friend m operator ^(m a, ll b){ return a ^= b; }
};
typedef mod_int<MOD> mint;

int main(){
    _; ll n, m, c; cin >> n >> m >> c;
    debug(n);
    debug(c);
    mint color = mint(c)^(n*n);

    debug(color);
    mint resp = 0;
    forn(i, 0, m){
        resp += color^gcd(i, m);
        debug(resp);
    } 
 
    resp /= m;
    cout << resp << ln;
    
    return 0;
}