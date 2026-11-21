# Small-to-Large Merging — Distinct Colors in Subtrees

## Problem Statement : Distinct Colors in Subtrees

Given a rooted tree consisting of `N` nodes, where each node has a color `C[i]`, find the number of distinct colors present in the subtree of every node.

The subtree of a node includes the node itself and all its descendants.

### Example

**Input**
```text
5
2 3 2 2 1
1 2
1 3
3 4
3 5
```

**Tree**

```text
        1(2)
       /    \
     2(3)   3(2)
            /  \
          4(2) 5(1)
```

**Output**
```text
3 1 2 1 1
```

| Node | Colors in Subtree | Distinct Colors |
|:---:|:---|:---:|
| 1 | {2, 3, 2, 2, 1} | 3 |
| 2 | {3} | 1 |
| 3 | {2, 2, 1} | 2 |
| 4 | {2} | 1 |
| 5 | {1} | 1 |

---

## Approach : Small-to-Large Merging

Instead of repeatedly traversing every node in a subtree to find its distinct colors, maintain a `set` of colors for every subtree.

During DFS:

1. Insert the current node's color into its set.
2. Recursively process every child.
3. Always merge the smaller set into the larger set.
4. Swap the sets if necessary to ensure that the destination set is larger.
5. The answer for the current node is the size of the resulting set.

### Key Optimization

```cpp
if(subtree_colors[v].size() > subtree_colors[u].size()){
    swap(subtree_colors[u], subtree_colors[v]);
}
```

The `swap()` operation exchanges the internal resources of the two containers rather than moving every element individually.

For `std::set`, swapping compatible containers is constant-time, allowing us to reuse the larger set and merge only the smaller one into it.

---

## Implementation

```cpp
#include <iostream>
#include <vector>
#include <set>

using namespace std;

const int MAXN = 200005;

vector<int> adj[MAXN];
int color[MAXN], ans[MAXN];

set<int> subtree_colors[MAXN];

void dfs(int u, int p) {

    subtree_colors[u].insert(color[u]);

    for(int v : adj[u]) {

        if(v == p) continue;

        dfs(v, u);

        // Ensure the destination set is the larger set
        if(subtree_colors[v].size() > subtree_colors[u].size()) {
            swap(subtree_colors[u], subtree_colors[v]);
        }

        // Merge the smaller set into the larger set
        for(int c : subtree_colors[v]) {
            subtree_colors[u].insert(c);
        }

        subtree_colors[v].clear();
    }

    ans[u] = subtree_colors[u].size();
}
```

---

## Why Small-to-Large Merging Works?

The optimization is based on ensuring that whenever an element is moved from one set into another, it belongs to the smaller set.

After merging, the size of the resulting set is at least twice the size of the smaller set.


Therefore, every time an element is moved, the size of the set containing that element increases by at least a factor of two.

---

## Complexity Analysis — Charging Argument

### Step 1 : Track an Individual Element

Consider any element being moved during the merging process.

Whenever the element belongs to the smaller set, it is moved into the larger set. After the merge, the size of the set containing that element at least doubles.


### Step 2 : Count the Number of Moves

Since the set size can at most reach `N`, an individual element can be moved at most:

O(log N)

times.

There are at most `N` elements initially, so the total number of element insertions caused by merging is:

{O(Nlog N)}

### Step 3 : Account for the Cost of Each Insertion

The underlying data structure is `std::set`, which is implemented as an ordered balanced search tree.

Each insertion costs:


O(log N)


Therefore:

$$
\begin{aligned}
\text{Total Time}
&= O(N\log N) \times O(\log N)\\
&= \boxed{O(N\log^2 N)}
\end{aligned}
$$

### Final Complexity

| Complexity | Value |
|---|---|
| Time | `O(N log² N)` |
| Space | `O(N log N)` upper bound for stored set contents across nodes, before considering cleared sets |

---

## Important STL Observation : `swap()`

Normally, swapping two containers element-by-element would require moving their contents.

However, for standard containers such as `vector`, `map`, and `set`, `std::swap()` generally exchanges the internal ownership/resources of the containers in constant time under compatible allocator conditions.

```cpp
swap(container1, container2);
```

Instead of moving every element, it exchanges the underlying storage or internal structure.

This is why the following operation is efficient:

```cpp
if(a.size() < b.size()){
    swap(a, b);
}
```

After the swap, `a` owns the larger container, so we only insert the elements from the smaller container `b` into `a`.

---

## Complexity Analysis — Charging Argument

To prove **`O(N log² N)`** clearly in an interview, analyze the movement of a single element rather than examining the tree level-by-level.

This technique is called the **Charging Argument** (or Contribution to the Sum). It makes the complexity proof easier by tracking how frequently an individual element can participate in a merge.

---

### Step 1 : Track One Element's Journey

Instead of asking *"How much work happens at node `u`?"*, ask:

**"How many times is a single color `x` copied from one set to another?"**

1. A color initially belongs to a set of size `1`.
2. Because of the condition `if (v.size() > u.size()) swap(u, v)`, an element is moved only when it belongs to the smaller set.
3. When a smaller set merges into a larger set, the resulting set has a size at least twice that of the smaller set.



---

### Step 2 : Count the Moves per Element

Each time an element is moved, the size of the set containing it at least doubles.



Since the set size cannot exceed `N`, an element can be moved at most:


log N


times.

Therefore, every individual element is moved at most:


O(log N)


times throughout the entire execution.

> **Important:** `std::swap` on two `std::set` objects swaps their internal resources in constant time under compatible allocator conditions. Elements of the larger set are not individually moved during the swap.

---

### Step 3 : Multiply by the Insertion Cost

- There are `N` elements in total.
- Each element moves at most `O(log N)` times.

Therefore, the total number of insertions caused by merging is:


O(Nlog N)

Since we are using `std::set`, each insertion costs:

O(log N)


Hence, the total time complexity is:

$$
\begin{aligned}
\text{Total Time}
&= N \times O(log N) \times O(log N)\\
&= \boxed{O(Nlog^2 N)}
\end{aligned}
$$

---

### Summary — Interview Explanation

> Instead of summing the work at every node, I count how many times each element moves. Since we always merge the smaller set into the larger set, every time an element moves, the size of the set containing it at least doubles. Consequently, each of the `N` elements can move at most `O(log N)` times, resulting in `O(N log N)` total insertions. As each insertion into `std::set` costs `O(log N)`, the overall time complexity becomes `O(N log² N)`.


## Tags

`#Trees` `#DFS` `#SmallToLargeMerging` `#SetMerging` `#SubtreeQueries` `#AmortizedAnalysis` `#ChargingArgument` `#ComplexityAnalysis` `#STL` `#Optimization` `#CompetitiveProgramming`
