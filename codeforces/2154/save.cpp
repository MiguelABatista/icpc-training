void factor2(ll n, map<ll,ll>& pc, ll i, v64& b){
    if(n == 0) return;
    if(n == 1) return;
    ll p = lp[n];

    auto it = pc.find(p);
    if(it == pc.end()) pc[p] = b[i]; 
    else pc[p] = min(b[i], it->second); 
    
    while(n%p == 0) n /= p;
    factor(n, pc);
}