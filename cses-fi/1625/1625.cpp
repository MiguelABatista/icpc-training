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
const ll TAM = 6;
const string passos = "ULDR";

void func(ll& x, ll& y, char c){
    if(c == 'D') {y++; return;}
    if(c == 'U') {y--; return;}
    if(c == 'L') {x--; return;}
    if(c == 'R') {x++; return;}
}

string target;
string curr;
vector<set<char>> vec;

ll resp = 0;
vector<v64> vis(TAM+2, v64(TAM+2,0));
ll x = 1;
ll y = 1;

void dfs(ll step){
    if(step == TAM*TAM-1 && x == 1 && y == TAM){
        resp++;
        forn(i,0,sz(curr)) vec[i].insert(curr[i]);
    }

    if(x == 1 && y == TAM) return;
    
    ll h = vis[x-1][y] + vis[x+1][y];
    ll v = vis[x][y-1] + vis[x][y+1];
    if(h == 0 && v == 2) return;
    if(v == 0 && h == 2) return;


    if((target[step]=='?' || target[step]=='D') && vis[x][y+1]==0){
        y++;			
        vis[x][y]=1;
        curr.push_back('D');		
        dfs(step+1);
        curr.pop_back();		
        vis[x][y]=0;
        y--;
    }
    if((target[step]=='?' || target[step]=='R') && vis[x+1][y]==0){
        x++;			
        vis[x][y]=1;
        curr.push_back('R');	
        dfs(step+1);		
        curr.pop_back();		
        vis[x][y]=0;
        x--;
    }
    if((target[step]=='?' || target[step]=='U') && vis[x][y-1]==0){
        y--;			
        vis[x][y]=1;
        curr.push_back('U');	
        dfs(step+1);		
        curr.pop_back();		
        vis[x][y]=0;
        y++;
    }
    if((target[step]=='?' || target[step]=='L') && vis[x-1][y]==0){
        x--;
        vis[x][y]=1;
        curr.push_back('L');	
        dfs(step+1);		
        curr.pop_back();		
        vis[x][y]=0;
        x++;
    }
};



int main() {
    _;
    cin >> target;
    vec.resize(sz(target));
    forn(i,0,TAM+2){
        vis[i][0] = vis[0][i] = 1;
        vis[i][TAM+1] = vis[TAM+1][i] = 1;
    }
    
    vis[1][1] = 1;
    dfs(0);
    cout << resp << ln;
    forn(i,0,sz(vec)){
        cout << i << ": ";
        debugv(vec[i]);
    }
    return 0;
}
