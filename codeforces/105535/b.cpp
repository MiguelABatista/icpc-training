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

struct node {
    ll id, val;
    node *prev = nullptr, *nxt = nullptr;
};


ll id_counter = 1000000000;

void solve() {
    vector<tuple<ll, ll, ll>> ans;
    ll n, k; cin >> n >> k;
    v64 v(n);
    vector<node *> vnodes(n);
    vector<node*> to_free;
    map<p64, map<ll, node *>> mp;
    forn(i, 0, n) {
        cin >> v[i];
        node *n_node = new node{i, v[i]};
        to_free.push_back(n_node);
        vnodes[i] = n_node;
    }

    forn(i, 0, n-1) {
        mp[{vnodes[i]->val, vnodes[i+1]->val}][vnodes[i]->id] = vnodes[i];
        vnodes[i]->nxt = vnodes[i+1];
        vnodes[i+1]->prev = vnodes[i];
    }
    node * peixe = vnodes[0];

    priority_queue<tuple<ll, ll, ll>> pq;
    for (auto& e : mp) {
        pq.emplace(e.second.size(), -e.first.first, -e.first.second);
    }
    
    forn(i, 0, k) {
        auto curr = pq.top(); pq.pop();
        while ((get<0>(curr) != mp[{-get<1>(curr), -get<2>(curr)}].size() || -get<1>(curr) == -get<2>(curr)) && pq.size()) {
            curr = pq.top(); pq.pop();
        }

        if (!pq.size() && (-get<1>(curr) == -get<2>(curr) || get<0>(curr) != mp[{-get<1>(curr), -get<2>(curr)}].size())) break;

        if (get<0>(curr) <= 1) {
            break;
        }

        ll l = -get<1>(curr);
        ll r = -get<2>(curr);

        ans.emplace_back(l, r, get<0>(curr));

        for (auto [id, nd] : mp[{l, r}]) {
            node *n_node = new node{id_counter++, 256+i}; 
            peixe = n_node;
            to_free.push_back(n_node);

            node *prox = nd->nxt;

            mp[{nd->val, prox->val}].erase(id);
            pq.emplace(mp[{nd->val, prox->val}].size(), -(nd->val), -(prox->val));

            if (nd->prev != nullptr) {
                node *source = nd->prev;

                mp[{source->val, nd->val}].erase(source->id);
                pq.emplace(mp[{source->val, nd->val}].size(), -source->val, -nd->val);

                n_node->prev = source;
                source->nxt = n_node;

                mp[{source->val, n_node->val}][source->id] = source;
                pq.emplace(mp[{source->val, n_node->val}].size(), -source->val, -n_node->val);
            }

            if (prox->nxt != nullptr) {
                node *tink = prox->nxt;

                mp[{prox->val, tink->val}].erase(prox->id);
                pq.emplace(mp[{prox->val, tink->val}].size(), -prox->val, -tink->val);

                n_node->nxt = tink;
                tink->prev = n_node;

                mp[{n_node->val, tink->val}][n_node->id] = n_node;
                pq.emplace(mp[{n_node->val, tink->val}].size(), -n_node->val, -tink->val);   
            }
        }
    }

    cout << ans.size() << ln;
    for (auto [a, b, c] : ans) {
        cout << a << " " << b << " " << c << ln;
    }

    node * nd = peixe;
    while (nd->prev != nullptr) nd = nd->prev;
    cout << nd->val << " "; 
    while (nd->nxt != nullptr) {
        nd = nd->nxt;
        cout << nd->val << " ";
    }
    cout << ln;

    forn(i, 0, to_free.size()) {
      delete (to_free[i]);
    }

}

int main(){
    _;
    ll t; cin >> t;
    while (t--) solve();
    return 0;
}