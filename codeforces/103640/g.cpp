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
    
using Tree = vector<v64>;
const ll INF = 0x3f3f3f3f3f3f3f3fll;
const ll MOD = 1'000'000'007;
const ll MAXN= 200'007;

ll pow2[2*MAXN];
v64 divs[MAXN];

void build(){
    pow2[0] = 1;
    forn(i,0,2*MAXN-1) pow2[i+1] = (pow2[i] + pow2[i])%MOD;
    forn(i,2,MAXN){
        for(ll j = i+i; j < MAXN; j += i){
            divs[j].push_back(i);
        }
    }
}

ll hash_rooted(const Tree &tree, ll root, const vector<bool> &valid) {
    // write tree as (()((()))) and interpret '(' as 0, and ')' as 1.
    // Sort children by hash.
    //
    // The return is a pair (hash, num_nodes)
    function<pair<ll, ll>(ll, ll)> dfs = [&](ll node, ll parent) -> pair<ll, ll> {
        vector<pair<ll, ll>> children;
        for (ll c : tree[node]) if (c != parent && valid[c])
            children.push_back(dfs(c, node));
        sort(begin(children), end(children)); // sort by hash
        // build final hash and size
        ll sz = 0;
        ll hash = 0;
        for (auto [h, s] : children) {
            hash = (hash + h * pow2[2 * sz]) % MOD;
            sz += s;
        }
        return {((hash << 1) | 1) % MOD, sz + 1}; // add node
    };
    return dfs(root, -1).first;
}

p64 find_centroid(const Tree& tree,const ll start, const vector<bool>& valid, ll N){
    ll n = N;

    ll best = n + 1, c1 = -1, c2 = -1;

    function<ll (ll,ll)> dfs = [&](ll u, ll p){
        ll my_sz = 1;
        ll mx = 0;
        for(ll v : tree[u]) if(v != p && valid[v]){
            ll v_sz = dfs(v, u);
            my_sz += v_sz;
            mx = max(mx, v_sz);
        }
        mx = max(mx, n - my_sz);
        if(mx < best){
            best = mx;
            c1 = u; c2 = -1;
        }else if(mx == best){
            if(u != c1) c2 = u;
        }
        return my_sz;
    };

    dfs(start, -1);
    if(c2 != -1 && c2 < c1) swap(c1, c2);
    return {c1, c2};
}

ll hash_unrooted(const Tree& tree,const ll start, const vector<bool>& valid, const ll N){
    p64 p = find_centroid(tree, start, valid, N);
    if(p.second != -1){
        ll aux1 = hash_rooted(tree, p.first, valid);
        ll aux2 = hash_rooted(tree, p.second, valid);
        return min(aux1,aux2);
    }
    return hash_rooted(tree, p.first, valid);
}

ll hash_div(const Tree& tree, const ll div, vector<bool>& valid){
    fill(begin(valid), end(valid), true);

    int h = -1;

    function<int(int, int)> dfs = [&](int v, int p) -> int {
        valid[v] = false;
        int my_sz = 1;

        for(ll u: tree[v]) if(u != p){
            ll sz_v = dfs(u,v);
            if(h == -2) return -1;
            my_sz += sz_v;
        }

        valid[v] = true;

        if(my_sz > div){
            h = -2;
            return my_sz;
        }
        if(my_sz == div){
            ll my_hash = hash_unrooted(tree, v, valid, div);
            if(h != -1 && h != my_hash){
                h = -2;
                return my_sz;
            }
            h = my_hash;
            valid[v] = false;
            my_sz = 0;
        }
        return my_sz;
    };
    dfs(0,-1);
    return h;
}

int main(){
    _;
    build();
    ll n; cin >> n;
    vector<Tree> vec(n);

    forn(i,0,n){
        ll k; cin >> k;
        vec[i].resize(k);
        forn(j,0,k-1){
            ll a, b; cin >> a >> b;
            a--; b--;
            vec[i][a].push_back(b);
            vec[i][b].push_back(a);
        }
    }

    unordered_map<ll, ll> cnt_hash;
    v64 all_tree_hash(n);

    forn(i,0,n){
        auto &tree = vec[i];
        const ll k = tree.size();
        vector<bool> valid(k, true);
        
        ll aux = hash_unrooted(tree, 0, valid, tree.size());
        all_tree_hash[i] = aux;
        cnt_hash[aux]++;
    }        

    vector<bool> possible_sizes(MAXN);
    forn(i,0,n){
        auto &tree = vec[i];
        const ll k = tree.size();
        possible_sizes[k] = true;
        vector<bool> valid(k, true);
        
        ll aux = all_tree_hash[i];

        ll ans = cnt_hash[aux]-1;
    
        for(ll d: divs[k]) if(possible_sizes[d]){
            ll h = hash_div(tree, d, valid);
            auto it = cnt_hash.find(h);
            if(it != cnt_hash.end()) ans += it->second;
        }
        cout << ans << " ";
    }
    cout << ln;
    return 0;
}
