    #include <bits/stdc++.h>
    using namespace std;

    typedef long long ll;
    typedef pair<ll, ll> p64;
    typedef vector<ll> v64;

    #define forn(i, s, e) for (ll i = (s); i < (e); i++)
    #define sz(u) ((ll) u.size())
    #define ln "\n"

    #ifdef DEBUG
    #define trace(u) u
    #define _
    #else
    #define trace(u)
    #define _ ios::sync_with_stdio(0); cin.tie(0)
    #endif

    #define debug(u) trace(cout << #u " = " << u << ln)
    #define debugv(v) trace(cout << #v ": "; for (auto xx : v) cout << setw(3) << xx << " "; cout << ln)
    #define debugp(v) trace(cout << #v ": "; for (auto xx : v) cout << xx.first << "->" << xx.second << " "; cout << ln)
    #define conv(c) ((ll)(c-'a'))
    
    const ll INF = 0x3f3f3f3f3f3f3f3fll;
    const ll MAX = 1000000;
    // const ll MAX = 20;

    // Aho-Corasick Automaton
    //
    // Builds a trie with failure links for multi-pattern matching; insert is O(|s|), build is linear in total length, and queries run in linear time in the text.
    //
    // complexity: varies, O(total patterns length)

    ll to[MAX][26], linkk[MAX], term[MAX], exitt[MAX];
    ll idx = 0;

    struct aho {
        vector<v64> g;
        
        aho(ll n): g(n){ };
        
        void insert(string& s, ll idx_) {
            ll at = 0;
            for (char c : s) {
                // auto it = to[at].find(c);
                // if (it == to[at].end()) at = to[at][c] = ++idx;
                if(to[at][conv(c)] == -1) at = to[at][conv(c)] = ++idx;
                else at = to[at][conv(c)] ;
            }
            term[at] = idx_; 
        }

        void build() {
            queue<ll> q;
            q.push(0);
            linkk[0] = exitt[0] = -1;
            while (q.size()) {
                ll i = q.front(); q.pop();
                // for (auto [c, j] : to[i]) {
                forn(ci,0,26) {
                    ll j = to[i][ci];
                    if(j==-1) continue;
                    // char c = 'a'+ci;
                    ll l = linkk[i];
                    // while (l != -1 and !to[l].count(c)) l = linkk[l];
                    while (l != -1 and to[l][ci] == -1) l = linkk[l];
                    linkk[j] = l == -1 ? 0 : to[l][ci];
                    // exitt[j] = term[linkk[j]] ? linkk[j] : exitt[linkk[j]];
                    exitt[j] = term[linkk[j]] != -1 ? term[linkk[j]] : exitt[linkk[j]];
                    q.push(j);
                }
            }
        }

        void print(){
            forn(i,0,MAX){
                cout << i << ": " << ln;
                debugp(to[i]);
                cout << ln;
            }
        }

        void query(string& s, ll idxs) {
            ll at = 0;
            forn(i,0,sz(s)){
                char c = s[i];
                at = to[at][conv(c)];
                assert(at != -1);
                if(exitt[at] != -1){
                    g[exitt[at]].push_back(idxs);
                }
                if(i < sz(s)-1 && term[at] != -1){
                    g[term[at]].push_back(idxs);
                }
            }
        }
    };

    void solve(ll n){
        vector<string> vec(n);

        forn(i,0,n) cin >> vec[i];

        aho cora(n);
        forn(i,0,n) cora.insert(vec[i], i);

        cora.build();

        // trace(
        //     cora.print();  
            
        //     cout << "testt: ";
        //     forn(i,0,MAX) cout << setw(3) << i << " ";
        //     cout << ln;
        //     debugv(linkk);
        //     cout << " "; debugv(term);
        //     debugv(exitt);
        // ) 

        forn(i,0,n) cora.query(vec[i], i);
        
        auto& g = cora.g;
        
        trace(  
            forn(i,0,n){
                cout << i << " : ";
                for(ll x: g[i]) cout << x << " ";
                cout << ln; 
            }
        )

        v64 dp(n, -1);

        function<void (ll)> dfs = [&](ll u){
            ll resp = 0;

            for(ll v: g[u]){
                if(dp[v] == -1) dfs(v);
                resp = max(resp, dp[v]);
            }

            resp++;
            dp[u] = resp;
        };

        ll resp = 0;
        forn(i,0,n){
            if(dp[i] == -1) dfs(i);
            resp = max(resp, dp[i]);
        }

        cout << resp << ln; 
    }

    int main() {
        _;
        while(true){
            ll n; cin >> n;
            if(n == 0) break;
            idx = 0;

            memset(linkk, 0, sizeof(linkk)); 
            memset(term, -1, sizeof(term));
            memset(exitt, -1, sizeof(exitt));
            forn(i,0,MAX) memset(to[i], -1, sizeof(to[i]));
            solve(n);
        }
        return 0;
    }
