<h1>1 : Truth about the prefix sum</h1>
-> if the array contains all the negative or positive elements then the prefix sum always decrease or increase <br>
-> But if the array contains positive and negative both elements then the prefix sum of array may increase or decrease but not 
  monotonic

<h1> To count the number of the subarrays for the range  : </h1>
 ->  [l , r]  is (r - l + 1)   where l is the fixed starting point <br>
 ->  [l , r]   i belongs to [l , r]    where is the fixed points for every subarray then ( i - l + 1 )*( r - i + 1);
 
## 📌 Subarray Properties

### 🔍 Function Behavior

| Function | Behavior as the Subarray Grows |
|----------|--------------------------------|
| Bitwise AND (`&`) | Non-increasing (decreases or remains constant) |
| Bitwise OR (`\|`) | Non-decreasing (increases or remains constant) |
| Minimum (`min`) | Non-increasing (decreases or remains constant) |
| Maximum (`max`) | Non-decreasing (increases or remains constant) |

### ⚡ Range Query Optimization

- **Sparse Table**: Efficiently compute range minimum, maximum, bitwise AND, and bitwise OR queries on a static array.
- **Time Complexity**: `O(1)` per query after `O(n log n)` preprocessing.

### 🧠 Recommended Practice

- [4114. Count Consistent Subarrays II (Hard)](https://leetcode.com/problems/count-consistent-subarrays-ii/description/)

## 🧠 Special Kind of Monotonic Stack — Transitive Function Dependency

### 💡 Core Idea

When processing subarrays, if the property/function we are calculating has a **transitive relationship**, we may be able to maintain a stack by removing previous elements that become redundant or dominated by the current element.

The stack is maintained based on a condition involving:

- The previous element represented by the stack top.
- The current element.
- A transitive function/property applied to both.

### ⚙️ General Implementation Pattern

```cpp
stack<int> st;

for(int i = 0; i < n; ++i) {
    while(!st.empty() && transitiveFunction(nums[st.top()], nums[i]) cond) {
        st.pop();
    }

    st.push(i);
}
```

### 🔑 Key Learning

- The stack stores indices instead of values, allowing access to the original array elements.
- The current element can eliminate previous stack elements when they satisfy a particular dominance/removal condition.
- The removal condition depends on the nature of the function and the required relationship (`==`, `>`, `<`, `>=`, `<=`, etc.).
- Transitivity helps establish relationships between elements without needing to compare every pair individually.
- This technique can be useful for reducing repeated subarray calculations and maintaining relevant candidates efficiently.

> **Important:** Transitivity alone does not guarantee that popping an element is safe. The removal condition must preserve the information required by the problem. Always prove why a popped element can no longer contribute to the answer or be a necessary candidate.

### 🎯 When to Think About This Technique

Whenever a subarray problem involves a function whose relationship is transitive, consider whether previously stored elements can be removed based on their relationship with the current element, enabling a monotonic-stack solution instead of repeatedly processing the same elements.

