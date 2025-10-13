    #include <bits/stdc++.h>
    using namespace std;

    typedef long long ll;
    typedef pair<ll, ll> p64;
    typedef vector<ll> v64;

    #define forn(i, s, e) for (ll i = (s); i < (e); i++)
    #define ln "\n"

    #if defined(DEBUG)
        #define _ (void) 0
        #define debug(x) cout << __LINE__ << ": " << #x << " = " << x << ln
        #define debugp(x) cout << __LINE__ << ": " << #x << " = " << x.first << " " << x.second << ln
    #else
        #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
        #define debug(x) (void)0
        #define debugp(x) (void)0
    #endif

    const ll INF = 0x3f3f3f3f3f3f3f3fll;

    void solve(){
        ll n, k; cin >> n >> k;
        ll root;
        v64 parent(n+1, 0);
        v64 heads;
        multiset<p64> s;

        forn(i, 0, k){
            ll a, b; cin >> a >> b;
            forn(j, a+1, b+1) parent[j] = j-1;
            heads.push_back(a);
            s.insert({b-a+1, a});
        }
        
        if(n == 1){
            cout << 0 << ln;
            return;
        }


        p64 menor = *s.begin();
        p64 maior = *prev(s.end());
        root = maior.second;

        if(k == 1){
            for(auto x : heads){
                if(x == root) continue;
                parent[x] = root; 
            }
            forn(i,1,n+1) cout << parent[i] << " ";; cout << ln;
            return;
        }

        if(k == 2){
            if(maior.first == menor.first){
                cout << "IMPOSSIBLE" << ln;
                return;
            }
        }else{
            p64 doismaior = *prev(prev(s.end()));
            if(maior.first == doismaior.first){
                if((menor.first == maior.first) || (menor.first == maior.first -1)){
                    cout << "IMPOSSIBLE" << ln;
                    return;
                }
            }
        }
        
        
        for(auto x : heads){
            if(x == root) continue;
            parent[x] = root; 
        }

        p64 doismaior = *prev(prev(s.end()));
        if(doismaior.first == maior.first) parent[menor.second] = root+1;

        // forn(i,1,n+1) cout << setw(2) <<  i << " ";; cout << ln;
        // forn(i,1,n+1) cout << setw(2) << parent[i] << " ";
        forn(i,1,n+1) cout << parent[i] << " ";
        cout << ln;
    }

    int main() {
        _; ll t; cin >> t;
        while(t--) solve();
        return 0;
    }