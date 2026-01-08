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
const ll MOD = 1'000'000'007;
const ll INV2 = 500'000'004;

ll escolhe2(ll x){ return ((((x)*(x-1))%MOD)*INV2)%MOD;}

int main(){
    _;
    ll n; cin >> n;

    v64 vec(n);
    vector<v64> inv(n+1);
    set<ll> paredes;

    paredes.insert(-1);
    paredes.insert(n);
    
    forn(i,0,n){
        cin >> vec[i];
        inv[vec[i]].push_back(i);
    }

    ll resp = 0;
    v64 rs;
    vector<v64> r_to_idxs(n+1, v64());
    v64 r_to_l(n+1);

    for(ll j = n; j >= 0; j--){
        v64& idxs = inv[j];
        if(idxs.empty()) continue;

        // map<p64, v64> mp;

        for(ll idx: idxs){
            auto it =  paredes.lower_bound(idx);
            ll r = *it;
            it--;
            ll l = *it;
            r_to_idxs[r].push_back(idx);
            r_to_l[r] = l;
            rs.push_back(r);
            // mp[{l,r}].push_back(idx);
        }

        ll soma_altura = 0;
        
        // for(auto& [p, v] : mp){
        //     auto [l, r] = p;
        for(ll r : rs){
            ll l = r_to_l[r];
            v64& v = r_to_idxs[r];
            debugv(v);
            v64 buracos;
            buracos.push_back(v[0]-l-1);
            

            forn(i,1,sz(v)){
                buracos.push_back(v[i]-v[i-1]-1);
            }

            buracos.push_back(r-v.back()-1);

            ll soma_parede = escolhe2(r-l); 

            for(ll b: buracos) soma_parede -= escolhe2(b+1);

            resp = (resp + soma_altura*soma_parede)%MOD; 
            soma_altura += soma_parede;

            v64 up(sz(v)), accup(sz(v)), down(sz(v));

            forn(i,0,sz(v)){
                up[i] = ((v[i]-l)*((i == sz(v)-1 ? r : v[i+1])-v[i]))%MOD;
                accup[i] = (up[i] + (i == 0 ? 0 : accup[i-1]))%MOD;
                down[i] = ((r - v[i])*(v[i] - (i == 0 ? l : v[i-1])))%MOD;
            }
            
            ll longe = 0;
            forn(i,2,sz(v)) longe = (longe + (down[i]*accup[i-2]))%MOD;

            ll perto = 0;

            forn(i,0,sz(v)-1){
                perto = (perto + (((v[i]-l)*(escolhe2(v[i+1]-v[i])+v[i+1]-v[i]))%MOD)*(r-v[i+1]))%MOD;
            }

            resp = (resp+perto+longe)%MOD;
        } 
        
        for(ll idx : idxs) paredes.insert(idx);
        for(ll r: rs) r_to_idxs[r].clear();
        rs.clear();
    }   
    cout << resp << ln;
    return 0;
}