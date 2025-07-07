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

vector<vector<vector<v64>>> dp(20, vector<vector<v64>>(10, vector<v64>(2, v64(2, -1))));
// dp[idx][prevdigit][leadingzero][tight] = qtd de solucoes no idx i da esq pra dir
// com último digito != prevdigit e se tem ou nao leadingzero e se eh ou nao tight

ll rec(ll curr, ll prevdig, ll leadingzero, ll tight, string& num){
    if(curr == 0) return 1;

    if(prevdig != -1 && dp[curr][prevdig][leadingzero][tight] != -1) 
        return dp[curr][prevdig][leadingzero][tight];

    ll limit;
    if(tight){
        ll sz = num.size();
        limit = num[sz - curr] - '0';
    }else{ 
        limit = 9;
    }

    ll ans = 0;

    forn(currdig, 0, limit+1){ 
        // se o numero é igual ao anterior continua
        // mas caso seja um leading zero nao tem problema
        if((leadingzero == 0) && (currdig == prevdig)) continue;

        ll newleadingzero = (leadingzero == 1 && currdig == 0) ? 1 : 0;
        ll newtight = (currdig == limit && tight == 1) ? 1 : 0;

        ans += rec(curr - 1, currdig, newleadingzero, newtight, num);
    }

    if(prevdig != -1) dp[curr][prevdig][leadingzero][tight] = ans;
    return ans;
}


int main(){
    _;
    ll a,b; cin >> a >> b;
    ll count1 = 0;

    forn(i,0,20){
        forn(j,0,10){
            forn(b1,0,2){
                forn(b2,0,2){
                    dp[i][j][b1][b2] = -1;
                }
            }
        }
    }

    // Calculate count of valid numbers from [0, a-1]
    string str1 = to_string(a - 1);
    if (a != 0)
        count1 = rec(str1.size(), -1, 1, 1, str1);

    forn(i,0,20){
        forn(j,0,10){
            forn(b1,0,2){
                forn(b2,0,2){
                    dp[i][j][b1][b2] = -1;
                }
            }
        }
    }

    string str2 = to_string(b);
    ll count2 = rec(str2.size(), -1, 1, 1, str2);

    cout << count2 - count1 << ln;
    // cout << count1 << ln;
    // cout << count2 << ln;
    return 0;
}