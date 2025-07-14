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
const ll MAX_D = 1510;

template<int D> struct gauss_z2 {
	bitset<D> basis[D], keep[D];
	int rk, in, dim;
	vector<int> id;
 
	gauss_z2 () : rk(0), in(-1), id(D, -1) {};

    gauss_z2 (ll dim_) : rk(0), in(-1), id(D, -1) {
        dim = dim_;
    };

    bool try_add(bitset<D> v){
        bitset<D> k;
		for (int i = dim - 1; i >= 0; i--) if (v[i]) {
			if (basis[i][i]) v ^= basis[i], k ^= keep[i];
			else {
				return true;
			}
		}
		return false;
    }
 
	bool add(bitset<D> v) {
		in++;
		bitset<D> k;
		for (int i = dim - 1; i >= 0; i--) if (v[i]) {
			if (basis[i][i]) v ^= basis[i], k ^= keep[i];
			else {
				k[i] = true, id[i] = in, keep[i] = k;
				basis[i] = v, rk++;
				return true;
			}
		}
		return false;
	}
	pair<bool, bitset<D>> coord(bitset<D> v) {
		bitset<D> c;
		for (int i = dim - 1; i >= 0; i--) if (v[i]) {
			if (basis[i][i]) v ^= basis[i], c[i] = true;
			else return {false, bitset<D>()};
		}
		return {true, c};
	}
	pair<bool, vector<int>> recover(bitset<D> v) {
		auto [span, bc] = coord(v);
		if (not span) return {false, {}};
		bitset<D> aux;
		for (int i = dim - 1; i >= 0; i--) if (bc[i]) aux ^= keep[i];
		vector<int> oc;
		for (int i = dim - 1; i >= 0; i--) if (aux[i]) oc.push_back(id[i]);
		return {true, oc};
	}
};

int main(){
    _; ll n, d; cin >> n >> d;

    ll special_ind = -1;

    gauss_z2<MAX_D> space(d+2);
    vector<bitset<MAX_D>> base(n);

    forn(i, 0, n){
        forn(j, 0, d){
            char c; cin >> c;
            if(c == '1') base[i].flip(j);
        }
        base[i].flip(d);
        if(special_ind == -1){
            if(!space.try_add(base[i])){
                special_ind = i;
                base[i].flip(d+1);
            }
        }
        space.add(base[i]);
    }

    if(special_ind == -1){
        cout << "*" << ln;
        return 0;
    }

    bitset<MAX_D> aux;
    aux.flip(d+1);

    auto y = space.recover(aux);
    
    vector<ll> resp(n, 0);

    forn(i, 0, (y.second).size()){
        resp[y.second[i]] = (i%2)+1;
    }

    forn(i, 0, n) cout << resp[i];
    cout << ln;

    return 0;
}