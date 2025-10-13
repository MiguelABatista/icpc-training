#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using Tree = vector<vector<int>>;
constexpr ll MOD = 1073741719ll; // random large prime... don't use 1e9+7 because there might be adversarial input
constexpr int MAX_POW2 = 400001;
constexpr int MAX_DIV = 200001;
ll pow2[MAX_POW2];
vector<int> divisors[MAX_DIV]; // except 1 and itself

void init() {
    pow2[0] = 1;
    for (int i = 1; i < MAX_POW2; i++) pow2[i] = (pow2[i-1] << 1ll) % MOD;

    for (int i = 2; i * i < MAX_DIV; i++) {
        divisors[i * i].push_back(i);
        for (int j = i * i + i; j < MAX_DIV; j += i) {
            divisors[j].push_back(i);
            divisors[j].push_back(j / i);
        }
    }
}

array<int, 2> find_centroids(const Tree &tree, int node, const vector<bool> &valid, int N) {
    array<int, 2> ans{-1, -1};
    function<int(int, int)> dfs = [&, N](int node, int parent) -> int {
        int my_sz = 1;
        bool centroid = true;
        for (int c : tree[node]) if (c != parent && valid[c]) {
            const int sz_c = dfs(c, node);
            if (sz_c > N / 2) centroid = false;
            my_sz += sz_c;
        }
        if (N - my_sz > N / 2) centroid = false;
        if (centroid) {
            if (ans[0] == -1) ans[0] = node;
            else ans[1] = node;
        }
        return my_sz;
    };
    dfs(node, -1);
    return ans;
}

ll hashes[MAX_DIV];
int sizes[MAX_DIV];
ll hash_rooted(Tree &tree, int root, const vector<bool> &valid) {
    // write tree as (()((()))) and interpret '(' as 0, and ')' as 1.
    // Sort children by hash.
    //
    // The return is a pair (hash, num_nodes)
    function<void(int, int)> dfs = [&](int node, int parent) {
        for (int c : tree[node]) if (c != parent && valid[c])
            dfs(c, node);
        sort(begin(tree[node]), end(tree[node]), [&valid, parent](int a, int b) {
            bool valid_a = valid[a] && a != parent;
            bool valid_b = valid[b] && b != parent;

            if (!valid_a) return false;
            if (!valid_b) return true;

            return hashes[a] < hashes[b];
        }); // sort by hash
        // build final hash and size
        int sz = 0;
        ll hash = 0;
        for (int c : tree[node]) if (c != parent && valid[c]) {
            hash = (hash + hashes[c] * pow2[2 * sz]) % MOD;
            sz += sizes[c];
        }
        hashes[node] = ((hash << 1) | 1) % MOD;
        sizes[node] = sz + 1;
    };
    dfs(root, -1);
    return hashes[root];
}

ll hash_tree(Tree &tree, int node, const vector<bool> &valid, int N) {
    // The tree we are hashing is a subtree of "tree" containing node, but never passing
    // through an invalid node.
    //
    // This allows us to find the hash of a subtree without having to actually copy it.

    auto centroids = find_centroids(tree, node, valid, N); // there can be one or two
                                                        // The hash of the tree is the smallest of the two
    ll h = LLONG_MAX;
    for (int c : centroids) if (c != -1) h = min(h, hash_rooted(tree, c, valid));
    return h;
}

ll hash_divisors(Tree &tree, const int div, vector<bool> &valid) {
    fill(begin(valid), end(valid), true);

    int h = -1;

    // return size of subtree
    function<int(int, int)> dfs = [&, div](int node, int parent) -> int {
        // in case we need to find a hash of a subtree mark node as invalid
        valid[node] = false;
        int my_sz = 1;

        for (int c : tree[node]) if (c != parent) {
            int sz_c = dfs(c, node);
            if (h == -2) return my_sz; // h == -2 means we've decided its impossible
            my_sz += sz_c;
        }

        valid[node] = true; // valid again, yay

        if (my_sz > div) {
            // we surpassed the divisor, impossible
            h = -2;
            return my_sz;
        }
        if (my_sz == div) {
            // we found a subtree with the correct size, yay!
            ll my_h = hash_tree(tree, node, valid, div);
            if (h != -1 && my_h != h) {
                // different hashes, mark as impossible
                h = -2;
                return my_sz;
            }
            h = my_h;
            valid[node] = false; // below me is a subtree, don't let my parent see me
            my_sz = 0;
        }
        return my_sz;
    };
    dfs(0, -1);
    return h;
}

int main() {
    init();

    int N;
    scanf("%d", &N);
    vector<Tree> trees(N);
    vector<bool> sz_present(200001, false);
    for (int i = 0; i < N; i++) {
        int K;
        scanf("%d", &K);
        trees[i].resize(K);
        sz_present[K] = true;
        while (--K) {
            int a, b;
            scanf("%d %d", &a, &b); a--; b--;
            trees[i][a].push_back(b);
            trees[i][b].push_back(a);
        }
    }

    unordered_map<ll, ll> cnt_hash; // count how many trees have a particular hash.
    for (auto &tree : trees) {
        vector<bool> valid(tree.size(), true);
        cnt_hash[hash_tree(tree, 0, valid, tree.size())]++;
    }

    // now process trees one by one
    for (auto &tree : trees) {
        const int N = tree.size();
        vector<bool> valid(N, true);
        // first for the full tree
        int ans = cnt_hash[hash_tree(tree, 0, valid, N)] - 1; // - 1 because can't count tree itself
        // now for all proper divisors (except for 1, because there are no trees of size 1)
        for (int d : divisors[N]) if (sz_present[d]) {
            ll h = hash_divisors(tree, d, valid); // pass valid as to avoid memory allocations
            auto it = cnt_hash.find(h);
            if (it != cnt_hash.end()) ans += it->second;
        }
        printf("%d ", ans);
    }

    printf("\n");

    return 0;
}
