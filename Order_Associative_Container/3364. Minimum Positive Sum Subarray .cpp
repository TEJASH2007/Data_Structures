//  In this Question we can not apply the deque because we wants the minimum 
// Positive sum 
//  So Instead of the asking the minimum value of pre[l-1] ask the 
// biggest value among the smaller values of the pre[r]
// For that we can use the multiset

class Solution {
public:
    int minimumSumSubarray(vector<int>& nums, int l, int r) {
        int ans = INT_MAX;

        multiset<int> st;
        int n = nums.size();

        vector<int> pre(n+1 , 0);
        for(int i = 0; i < n ;++i){
            pre[i+1] += pre[i] + nums[i];
        }

        int left = l - r - 1;
        int right = -1;

        for(int i = l ; i <= n ; ++ i){
            ++right;
            st.insert(pre[right]);
            
            if(left >= 0){
                st.erase(st.find(pre[left]));
            }

            ++left;

            auto it = st.lower_bound(pre[i]);
            if(it != st.begin()){

                --it;
                ans = min(ans , pre[i] - *it );

            }
        }
        if(ans == INT_MAX) return -1;
        return ans;
    }
};
