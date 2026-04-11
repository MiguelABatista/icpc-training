#include<iostream>
using namespace std;

int main(){

long long n,x; cin >> n >> x;

long long v[n];
for(int i=0; i<n; i++) cin >> v[i];

long long s=0, p=0, count=0;

for(int i=0; i<n; i++){
while(s<x){
s+=v[p]; p++;
}
if(s==x) count++;
s-=v[i];
}
cout << count << endl;
return 0;
}


#include<iostream>
using namespace std;

int main(){

    long long n,x; cin >> n >> x;

    long long v[n];
    
    for(int i=0; i<n; i++) cin >> v[i];

    long long s=0, p=0, count=0;

    for(int i=0; i<n; i++){
        while(s<x){
            s+=v[p]; p++;
        }
        if(s==x) count++;
        s-=v[i];
    }
    cout << count << endl;
    return 0;
}
