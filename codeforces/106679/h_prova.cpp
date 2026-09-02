#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pll;
typedef vector<ll> vll;

#define forn(i,s,e) for(ll i=s; i<e; i++)
#define sz(u) ((ll) u.size())
#define ln "\n"

#ifdef DEBUG
#define trace(u) u
#define _
#else
#define trace(u)
#define _ ios::sync_with_stdio(0); cin.tie(0)
#endif

#define debug(u) trace(cout << #u " = " << u << ln);
#define debugv(v) trace(cout << #v ": " ;for(auto xx : v) cout << xx << " ";cout << ln);
#define debugm(v) trace(cout << #v ": " ;for(auto xx : v) cout << xx.first << ":" << xx.second << " ";cout << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;

const ll MAX = 100'505;

class BIT{
    ll bit[2][MAX+2];
    ll n;
public:
    BIT(ll n2, vll& v) {
        n = n2;
        for(ll i = 1; i <= n; i++){
            // bit[1][min(n+1,i+(i&-i))] += bit[1][i] += v[i-1];
            v[i-1] %= 2;
            bit[1][i] += v[i-1];
            bit[1][i] %= 2;
            bit[1][min(n+1,i+(i&-i))] += bit[1][i];
            bit[1][min(n+1,i+(i&-i))] %= 2;
        }
    }
    ll get(ll x, ll i){
        ll ret = 0;
        for(; i; i -= i&-i){
            ret += bit[x][i];
            ret %= 2;
        }
        return ret;
    }
    void add(ll x, ll i, ll val){
        val %= 2;
        for(; i<= n; i += i&-i){
            bit[x][i] += val;
            bit[x][i] %= 2;
        }
    }
    ll get2(ll p){
        return (get(0,p) * (p%2) + get(1,p))%2;
    }
    ll query(ll l, ll r){
        return ((get2(r+1) - get2(l))%2 + 2)%2;
    }
    void update(ll l, ll r, ll x){
        add(0,l+1, x%2), add(0,r+2,((-x)%2+2)%2);
        add(1,l+1,(-(x*l)%2+2)%2), add(1,r+2, (x*(r+1))%2);
    }
};


int main(){
    _;
    ll n; ll m; 
    cin >> n >> m;
    vll vec(n);
    forn(i,0,n) cin >> vec[i];
    BIT bit(n, vec);

    vector<set<ll>> ltor(n);
    vll idxs(n);
    forn(i,0,n) idxs[i] = i;
    // ltor[idxs[l]];   

    forn(i,0,m){
        ll l, r; cin >> l >> r;
        l--, r--;
        ltor[idxs[l]].insert(r);
    }

    auto merge = [&](ll a, ll b){
        ll idxpai = -1;
        ll idxfilho = -1;

        if(sz(ltor[idxs[a]]) > sz(ltor[idxs[a]])){
            idxpai = idxs[a];
            idxfilho = idxs[b];
        }else{
            idxpai = idxs[b];
            idxfilho = idxs[a];
        }
        
        idxs[a] = idxpai;
        idxs[b] = idxpai;

        for(auto x : ltor[idxfilho]) ltor[idxpai].insert(x);
    };

    forn(i,0,n){
        ll x = bit.query(i,i)%2;
        auto& s = ltor[idxs[i]];
        if(s.empty() && x == 1){
            cout << "NO" << ln;
            return 0;
        }
        if(s.empty() && x == 0){
            continue;
        }

        ll menor_r = *s.begin();

        if(x == 1) bit.update(i,menor_r, 1);
        s.erase(menor_r);
        
        if(menor_r == n-1) continue;
        merge(i, menor_r+1);
    }

    cout << "YES" << ln;
    return 0;
}