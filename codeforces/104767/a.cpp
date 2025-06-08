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
string s;
ll n;

vector<v64> mat;

ll func(ll l, ll r){
    debug(l);
    debug(r);
    if(mat[l][r] != -1) return mat[l][r];
    
    ll last = l + 1;
    ll aux = 1;
    ll sum = 0;
    bool found = false;
    forn(i, l+1, r){
        if(s[i] == '(') sum++;
        else sum--;
        if(sum == 0){
            aux *= func(last, i);
            last = i + 1;
            found = true;
        }
    }
    if(found) aux++;
    mat[l][r] = aux;
    return aux;
}

// ((())(())) 
// 0123456789

// (()())

int main(){
    _;
    cin >> n;
    cin >> s;
    s.insert(s.begin(), '(');
    s.push_back(')');
    n += 2;
    mat.resize(n, v64(n,-1));
    cout << func(0,n-1)-1 << ln;
    return 0;
} 