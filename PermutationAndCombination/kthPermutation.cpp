#include <bits/stdc++.h>
using namespace std;

void findKthPermuatation(vector<int> &arr , int k){
    int deno = 1;
    int n = arr.size();
    int num = 1;

    map<int , int> mp;
    for(auto &x : arr){
        mp[x]++;
    }

    set<int> st(arr.begin() , arr.end());
    vector<int> ans;

    vector<int> fact(11 , 1);
    fact[0] = 1;

    for(int i = 1; i <= 10 ; ++i){
        fact[i] *= fact[i-1]*i;
    }
    
    num = fact[n];

    for(auto &x : st){
        deno *= fact[ mp[x] ];
    }

    int mx = num / deno ;
    if(mx < k) return ;

    for(int i = 0; i < n ; ++i){
        num /= (n-i);
        int completed = 0;

        for(auto &x : st){
            
            int newComplete = ( num ) / ( deno / mp[ x ] )  + completed; 
            if(newComplete >= k){

                ans.push_back(x);
                deno /= mp[x];

                int freq = --mp[x];
                if(freq == 0){

                    st.erase(x);

                }
                k -= completed;
                break;
            }
            completed = newComplete;
        }

    }

    for(auto &x : ans){
        cout<<x<<" ";
    }
}

int main() 
{

    int n , k;
    cin >> n >> k;

    vector<int> arr(n , 0);
    
    for(auto &x : arr) cin>>x;

    sort(arr.begin() , arr.end());

    findKthPermuatation(arr,k);

    return  0;
}
