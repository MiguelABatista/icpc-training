ll n, m;
vector<ld> d(MAXN);
vector<p64> ar;
vector<ll> v;

bool bellamn_ford(ll a){
    forn(i, 0, n) d[i] = INF;
    d[a] = 0;

    forn(i, 0, n+1){
        forn(j, 0, m){
            if(d[ar[j].second] > d[ar[j].first] + w[j]){
                if(i == n) return 1;
                d[ar[j].second] = d[ar[j].first] + w[j];
            }
        }
    }

    return 0;
}