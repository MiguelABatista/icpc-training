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
#define debugv(v) trace(cout << #v ": "; for (auto xx : v) cout << xx << " "; cout << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;

ll n, k;
string s, sorig, r;

bitset<2405> vis[42][42][405];

bool dfs(ll i, ll a, ll b, ll c) {
    if (c > k) return false;    
    ll l = n - i;
    if ((l*(l-1)*(l-2))/6 + a*(l*(l-1))/2 + b*l + c < k) return false;

    if (i == n) {
        return c == k;
    }

    if (vis[i][a][b][c]) return false;
    vis[i][a][b][c] = 1;

    char orig = s[i];

    if (orig == 'N' || orig == '?') {
        r[i] = 'N';
        if (dfs(i + 1, a + 1, b, c)) return true;
    }
    if (orig == 'A' || orig == '?') {
        r[i] = 'A';
        if (dfs(i + 1, a, b + a, c)) return true;
    }
    if (orig == 'C' || orig == '?') {
        r[i] = 'C';
        if (dfs(i + 1, a, b, c + b)) return true;
    }
    if (orig == 'X' || orig == '?') {
        r[i] = (orig == '?') ? 'X' : orig;
        if (dfs(i + 1, a, b, c)) return true;
    }

    return false;
}

int main() {
    _;
    cin >> n >> k;
    cin >> s;
    sorig = s;
    
    forn(i, 0, n) {
        if (s[i] != 'N' && s[i] != 'A' && s[i] != 'C' && s[i] != '?') {
            s[i] = 'X';
        }
    }

    r = s; // Inicializa a string de resposta com o mesmo tamanho e caracteres base

    if (dfs(0, 0, 0, 0)) {
        forn(i, 0, n) if (sorig[i] != '?') r[i] = sorig[i];
        cout << r << ln;
    } else {
        cout << -1 << ln;
    }

    return 0;
}