#include <bits/stdc++.h>
typedef long long ll;
#define forn(i,s,e) for(ll i = (s); i < (e); i++)
using namespace std;

ll binary_search(vector<ll> &list, ll difference)
{
    ll l = 0; ll r = list.size()-1; ll mid;
    mid = (l+r)/2;
    while(l<=r)
    {
        if (list[mid] == difference) return mid;
        
        else if (difference > list[mid])
        {
            l = mid+1;
            mid = (l+r)/2;
        }
        else if (difference < list[mid])
        {
            r = mid-1;
            mid = (l+r)/2;
        }
    }
    if (list[mid] == difference) return mid;
    else return -1;
}

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    
    ll n; cin >> n;
    ll sum; cin >> sum;

    vector<ll> lista(n); 

    forn(i,0,n) cin >> lista[i];

    forn(i,0,n){
        forn(j,i+1,n){
            if(lista[i]+lista[j] == sum){
                cout << i+1 << " " << j+1 << "\n";
                return 0;
            }
        }
    }

    cout << "IMPOSSIBLE" << "\n";
}