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
const ll MAXN = 1005;
const ll MAXM = 15;

vector<bitset<MAXN>> mask;

template<ll n> struct prob{
    bitset<n> s;

    void add(ll i){
        while(s.test(i)){
            assert(i >= 0);
            // if(i < 0){
            //     cout << "hahahaha" << ln;
            //     return;
            // }
            s.reset(i);
            i--;
        }
        s.set(i);
    }

    void sub(ll i){
        while(!s.test(i)){
            // debug(i);
            assert(i >= 0);
            // if(i < 0){
            //     cout << "hahahaha" << ln;
            //     return;
            // }
            s.set(i);
            i--;
        }
        s.reset(i);
    }

    prob& operator +=(const prob& a){
        forn(i, 0, MAXN){
            if(a.s.test(i)) add(i);
        }
        return *this;
    }

    prob& operator -=(const prob& a){
        // debug("tucunare");
        forn(i, 0, MAXN){
            if(a.s.test(i)) sub(i);
        }
        return *this;
    }

    bool operator < (const prob p) const {
        ll i = 0;
        while(s.test(i) == p.s.test(i)){
            if(i == n-1) return false;
            i++;
        }

        return (!s.test(i)) && (p.s.test(i));
    }

    bool operator == (const prob p) const {
        return s == p.s;
    }
};

//calcula a probabilidade(tamanho) no conjunto (uniao dos conjuntos em not_in)inter universo
prob<MAXN> inc_exc(bitset<MAXM> not_in, bitset<MAXN> universo){
    prob<MAXN> p;

    if(not_in.none()){
        return p;
    }

    forn(i, 0, MAXM){
        if(not_in.test(i)){
            debug(not_in.to_string());
            debug(mask[i].to_string());
            debug(universo.to_string());          
            not_in.reset(i);
            
            bitset<MAXN> aux = mask[i]|universo;
            p.add(aux.count()+1); 
            prob p_tirar = inc_exc(not_in, universo|mask[i]);
            prob p_resto = inc_exc(not_in, universo);

            // debug(p.s.to_string());
            // debug(p_tirar.s.to_string());
            p-=p_tirar;
            p+=p_resto;

            return p;
        }
    }

    return p;
}

int main(){
    _; ll n, m; cin >> n >> m;
    mask.resize(m, 0);
    vector<bitset<MAXM>> not_in(n);

    forn(i, 0, m){
        ll a; cin >> a;
        forn(j, 0, a){
            ll b; cin >> b; b--;
            mask[i].set(b);
        }

        forn(j, 0, n){
            if(mask[i].test(j)) continue;
            not_in[j].set(i);
        }
    }

    vector<pair<prob<MAXN>, ll>> p(n);
    bitset<MAXN> universo;

    forn(i, 0, n){
        debug(i);
        debug(p[i].first.s.to_string());
        p[i].first = inc_exc(not_in[i], universo);
        // debug(not_in[i]);

        p[i].second = -(i+1);
    }

    sort(p.rbegin(), p.rend());
 
    forn(i, 0, n){
        cout << -p[i].second << " ";
    }
    cout << ln;

    return 0;
}