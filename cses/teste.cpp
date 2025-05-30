#include <bits/stdc++.h>
using namespace std;

int main(void){
    long long n;
    vector<long long> list;

    long long a;
    cin>>n;
    cin>>a;
    list.insert(list.begin(),a);
    cout<<0<<"\n";
    bool correct=0;
    long long store;
    for(long long i = 0; i<n-1;i++){
        cin>>a;
        list.insert(list.begin(),a);
        correct=0;
        for(long long j=1;j<(list.size()); j++){
            if(list[j]<a){
                correct=1;
                store=j;
                break;
            }
        }
        if(correct==0){
            cout << 0 << "\n";
        }
        else{
            cout<<list.size()-store << "\n";
        }
    }
    return 0;
}