#include <bits/stdc++.h>
using namespace std;

typedef int ll;
typedef pair<ll, ll> p64; 
typedef vector<ll> v64;

#define forn(i, s, e) for(ll i = (s); i < (e); i++)
#define ln "\n"

#if defined(DEBUG)
    #define _ (void)0
    #define debug(x) cout << __LINE__ << ": " << #x << " = " << x << ln
    #define debugp(x) cout << __LINE__ << ": " << #x << " = " << x.first << " " << x.second << ln
#else
    #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
    #define debug(x) (void)0
    #define debugp(x) (void)0
#endif

const ll INF = 0x3f3f3f3f;//0x3f3f3f3f3f3f3f3fll;
const ll MAXN = 7'000'000;
pair<ll,ll> saida;

ll c, r, e; 
ll delta;
vector<vector<vector<bool>>> maze;

struct pos{
    ll x1, x2, y1, y2;

    pos(ll x1_, ll x2_, ll y1_, ll y2_) : x1(x1_), x2(x2_), y1(y1_), y2(y2_) {
    };
    
    bool operator<(const pos& o) const {
        return std::tie(x1, y1, x2, y2) < std::tie(o.x1, o.y1, o.x2, o.y2);
    }

    ll idx(){
        ll idx1 = x1 + r*y1;
        if(x1 == -1) idx1 = r*c;
        ll idx2 = x2 + r*y2;
        if(x2 == -1) idx2 = r*c; 
        return idx1 + (r*c+1)*idx2;;
    }
    void print(string s) {cout << s << x1 << " " << y1 << " # " << x2 << " " << y2 << ln;}
};

ll calc_delta(char d1, char d2){
    map<char, ll> mp = {{'N',0 }, {'E',1 }, {'S',2 }, {'W',3}};
    ll idx1 = mp[d1];
    ll idx2 = mp[d2];
    
    return (idx2 - idx1+4)%4;
}

pair<ll, ll> rot(ll dir){
    dir = (dir+4)%4;
    if(dir == 0) return {1,0};
    if(dir == 1) return {0,1};
    if(dir == 2) return {-1,0};
    if(dir == 3) return {0,-1};    
    assert(false);
}

pair<pos, ll> walk_pos(pos curr, ll dir){
    pos resp = curr;
    ll bump = 0;
    
    if(curr.x1 != saida.first || curr.y1 != saida.second){
        if(maze[resp.x1][resp.y1][dir] == true) {
            resp.x1 += rot(dir).first;
            resp.y1 += rot(dir).second;
        }
        else bump++;
    }
    
    if(curr.x2 != saida.first || curr.y2 != saida.second){
        ll new_dir = (dir+delta)%4;
        if(maze[resp.x2][resp.y2][new_dir] == true) {
            resp.x2 += rot(new_dir).first;
            resp.y2 += rot(new_dir).second;
        }
        else bump++;
    }

    return {resp, bump};
}

int main(){
    _; cin >> c >> r >> e;
    e--;
    ll c1, r1, c2, r2;
    char d1, d2;
    cin >> c1 >> r1 >> d1 >> c2 >> r2 >> d2;
    c1--; r1--; c2--; r2--;

    saida = {-1,e};
    pos inicio = pos(r1, r2, c1, c2);

    maze.resize(r, vector<vector<bool>>(c , vector<bool>(4, true)));

    forn(i, 0, r){
        maze[i][0][3] = false;
        maze[i][c-1][1] = false;
    }

    forn(i, 0, c){
        maze[0][i][2] = false;
        maze[r-1][i][0] = false;
    }

    maze[0][e][2] = true;

    delta = calc_delta(d1, d2);

    ll n; cin >> n;
    forn(aa, 0, n){
        ll x, y;
        cin >> y >> x;
        x--;
        y--;
        maze[x][y][0] = false;
        maze[x+1][y][2] = false;
    }

    cin >> n;
    forn(aa, 0, n){
        ll x, y;
        cin >> y >> x;
        x--;
        y--;
        maze[x][y][1] = false;
        maze[x][y+1][3] = false;
    }

    priority_queue<pair<pair<ll,ll>, pos>> pq; // dist bump vertice
    
    vector<bool> visitados(MAXN, false);
    vector<pair<ll,ll>> dist_bump(MAXN, {INF,INF});
    
    pq.push({{0,0}, inicio});
    dist_bump[inicio.idx()] = {0, 0};
    
    while(!pq.empty()){
        auto qualquer = pq.top();
        pq.pop();
        pair<ll,ll> v_db = qualquer.first;
        v_db.first *= -1;
        v_db.second *= -1;
        
        pos v = qualquer.second;
        
        // v.print("Der: ");

        if(visitados[v.idx()] == true || v_db > dist_bump[v.idx()]) continue;
        
        visitados[v.idx()] = true;

        forn(i,0,4){
            pair<pos, ll> walk = walk_pos(v, i);
            if(walk.second == 2) continue;
            auto& [u, b] = walk;

            // u.print("Parar: ");
            
            if(visitados[u.idx()]) continue;
            pair<ll,ll> curr_db = dist_bump[u.idx()];
            pair<ll,ll> new_u_db = {v_db.first+1, v_db.second+b}; 
            
            if(curr_db < new_u_db) continue;

            dist_bump[u.idx()] = new_u_db;
            pq.push({{-new_u_db.first, -new_u_db.second}, u});  
        }
    }

    pair<ll,ll> aux = dist_bump[pos(-1,-1,e,e).idx()];

    cout << aux.first << " " << aux.second << ln;

    return 0;
}