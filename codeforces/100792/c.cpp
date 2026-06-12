    #include <bits/stdc++.h>
    using namespace std;

    typedef long long ll;
    typedef pair<ll, ll> pll;
    typedef vector<ll> vll;

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
    #define debugv(v) trace(cout << #v ": "; for (auto xx : v) cout << xx << " "; cout << ln)

    const ll INF = 0x3f3f3f3f3f3f3f3fll;
    const ll MAX = 1'000'000'000;
    // const ll MAX = 21;

    bool askx(ll x){  // 1 se o x do ponto é >= x;
        if(x == 0) return true;

        debug(x);

        bool resp = true;
        cout << x-1 << " " << 0 << endl;
        cin >> resp;
        cout << x << " " << 0 << endl;
        cin >> resp;

        return resp; 
    }

    bool asky(ll y){  // 1 se o y do ponto é >= y;
        if(y == 0) return true;

        bool resp = true;
        cout << 0 << " " << y-1 << endl;
        cin >> resp;
        cout << 0 << " " << y << endl;
        cin >> resp;

        return resp;
    }

    int main() {
        ll lx = 0, rx = MAX;
        ll ansx = 0;
        while(lx <= rx){
            ll mx = (lx + rx)/2;
            debug(lx);
            debug(rx);
            debug(mx);

            bool resp = askx(mx);
            if(resp){
                ansx = mx;
                lx = mx + 1;
            }
            else rx = mx-1;
        }

        ll ly = 0, ry = MAX;
        ll ansy = 0;
        while(ly <= ry){
            ll my = (ly + ry)/2;

            bool resp = asky(my);
            if(resp){
                ansy = my;
                ly = my + 1;
            }
            else ry = my-1;
        }

        cout << "A " << ansx << " " << ansy << endl;
        return 0;
    }
