void dfs(ll i, vector<v64> &g, v64 &parent, v64 &prof){
    if(i != 0){
        prof[i] = prof[parent[i]] + 1;
    }

    for(auto c: g[i]){
        dfs(c, g, parent, prof);
    }

    return;
}
