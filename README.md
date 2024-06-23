# DSA 2024 Homework 4 Programming Problem 4 (Dissolve)

# Tutorial
In this problem, as we are merging companies and we need to know which company each employee belongs to, it is clearly based on Disjoint-Set Union. However, to deal with the salary raise and pay, many lazy tags will be added to the standard DSU.

The tutorial for subtask 1 is neglected since it is too simple. As we expect you should have taken Introduction to Computer Programming (CSIE1210) or simliar-level course before taking this course, you should be able to solve this subtask on your own even before this semester. :)

## The foundations of the DSU
In this problem, we can regard each employee as a node and each company as a component. Thus, while merging two companies, simply find the root of the two *components* and assign the parent of a root as the other root. However, to ensure the time complexity is $O(\log N)$ per merging or querying root, assign the parent of the root of the component with smaller size as the root of the larger component. Note that this is the only optimization you have to do within this problem. The other optimization of path-compression that lowers the complexity to $O(\alpha(N))$ is not necessary. While testing this problem, we found out that the full version of this problem requires too many operations during path-compression such that $O(\alpha(N))$ with a large constant is actually roughly the same as $O(\log N)$ when $N = 10^6$. We can not raise $N$ to a very large number as setting the time limit to more than 10 seconds is not practical. In the end, we decided that allowing solutions without path compression to pass is the better way. This is also a great example that complexity is not everything. The constant in the algorithm matters in real-life scenarios!

## Paying
For both the paying and raising part, the same technique will be utilized (Only record on root and visit ancestry to retrieve data). Though it is much simpler when only considering paying. Below is a brief explanation.

While a company is paying salary, record one payment on the root of the company. Let's denot the recorded payment count for node $i$ as $c_i$. For every employee, to retrieve their data, we can recursively visit their parent until root is reached. The sum of $c_i$ visited is the payment count for that employee. However, when two companies merge, all the employees of the smaller company will now also count the recording on the new root. To counter this, simply deduct the recording of the smaller component's root by the recording of the new root. Denote the root of the smaller component as $s$ and the root of the larger component as $l$. Then, when merging, make 

$$
\begin{cases}
parent_s \gets l \\
c_s \gets c_s - c_l
\end{cases}
$$

## Raising
Raising complicates the problem a lot as each raise results in different balance differnces.

First, not considering companies merging, we can use two additional variables to record a sequence of raising ane paying operations. First one records the raising sum ($r_i$) and the second one records the paying sum ($p_i$). Note that the initial salary can be regarded as a pay raise from $0$ to such salary so $p_i$ can be intialized as the initial salary. Then, for each company with node $i$ as the root and assuming no merging operations, a raise by $s$ operation can be $r_i \gets r_i + s$ and a paying operation can be 

$$
\begin{cases}
c_i \gets c_i + 1 \\
p_i \gets p_i + r_i
\end{cases}
$$

Finally, the employees in this company during this sequence earn $p_i$.

Without merging, the problem is still quite easy and straightforward. We now apply the same technique to only record on root and visit ancestry to retrieve data. In order to do that, we again have to adjust the value in the root of the smaller component. The paying sum can simply be deducted. We can not simply deduct the raising sum though as new payings are still affected these raises. Another issue is that the raising sum of the larger component should not have affected employees in the smaller company. Thus, we introduce two additional variables: $c_i'$ and $r_i'$ which are the parent's value of $c\_{parent}$ and $r\_{parent}$ when node $i$ is merged. Thus, similar to the only paying part, we can adjust the values as 

$$
\begin{cases}
parent_s \gets l \\
p_s \gets p_s - p_l \\
c'_s \gets c_l \\
r'_s \gets r_l
\end{cases}
$$

Then, to retrieve the sum of payment of each employee, traverse through the ancestry until root is reached. During the traversal, other than trivially summing the paying sum, we also have to deduct the additional payment due to raising in the larger component affecting those in the smaller component after merging. Thus, within each parent-child, $c_{parent} - c_{child}'$ and $r_{parent} - r_{child}'$ are the additional payment count and raising sum after being merged into. We have to take this into consideration to correctly calculate the payment sum of each employee. As this part is really complicated, I recommend visiting the code of merging and querying part. Anyway, the payment sum of node $i$ should be 

$$
\sum_{node \in ancestry} \left[p_{node} + \left(\left(c_{parent_{node}} - c_{node}'\right) \times \left(r_i + \sum_{node2 \in [i, node]} r_{parent_{node2}} - r_{node2}'\right)\right)\right]
$$

It is possible to calculate this value in $O(|ancestry|)$.

As you can probably see, it is very complicated to implement path compression. Thus, it is left as an exercise to the reader!

## Quiting
An employee quiting is actually not really related to the other operations. Based on the properties of DSU, we can not efficiently *split* a component. We don't actually split a node away here too. Instead, simply query the balance gained since the beginning or last quit and then create a new node.

# Sample code 
Below is a copy of `solution/main_sol.cpp`.
```c
# include <stdio.h>
# include <stdlib.h>
# define maxn (int)1e6+10
# define maxq (int)1e6+10
typedef long long ll;

// The dsu with merge by size.
int dsu[maxn + maxq], size[maxn + maxq];

// Mapping each employee to its dsu node
int id[maxn];

// The balance of each employee
long long b[maxn];

// A simple pair, similar to std::pair in C++
typedef struct pair{
    long long first;
    int second;
} pair;

pair make_pair(long long a, int b) {
    pair p;
    p.first = a;
    p.second = b;
    return p;
}

// The lazy tag structure
// Note that the term 'lazy tag' is used here.
// It is common to describe this kind of method (i.e. store
// the data at somewhere every affected node of the operation
// will access) as lazy tag in the context of algorithms or
// more particularly in the context of competitive programming.
// It is perfectly fine to not understand lazy tag in this problem!
// (I especially avoided the term 'lazy tag' in the tutorial :))
typedef struct lazyTag{
    // This values are the r, p, c, r', c'
    // Visit tutorial in README.md for details
    long long raise_salary_sum, pay_salary_sum;  // r, p
    int pay_salary_cnt;                          // c
    long long raise_salary_sum_when_merge;       // r'
    int pay_salary_cnt_when_merge;               // c'
} lazyTag;

// The lazy tag array of each dsu node
lazyTag lazy[maxn + maxq];

// A typical find function for dsu
int find(int x) {
    x = id[x];
    while (dsu[x] != x) x = dsu[x];
    return x;
}

void merge(int x, int y) {
    x = find(x); y = find(y);
    if (x == y) return;

    // x as the larger component, y as the smaller component
    if (size[x] > size[y]) {
        dsu[y] = x;  // Assigning parent
        size[x] += size[y];
        lazy[y].raise_salary_sum_when_merge = lazy[x].raise_salary_sum;  // r'_s = r_l
        lazy[y].pay_salary_cnt_when_merge = lazy[x].pay_salary_cnt;      // c'_s = c_l
        lazy[y].pay_salary_sum -= lazy[x].pay_salary_sum;                // p_s = p_s - p_l
    }
    // Swap of x, y
    else{
        dsu[x] = y;
        size[y] += size[x];
        lazy[x].raise_salary_sum_when_merge = lazy[y].raise_salary_sum;
        lazy[x].pay_salary_cnt_when_merge = lazy[y].pay_salary_cnt;
        lazy[x].pay_salary_sum -= lazy[y].pay_salary_sum;
    }
}

// Note that this funtion is O(|ancestry|)
// By storing the sum of c through the traversal,
// the complicated summations defined in the tutorial can be calculated and returned as res.first
pair get_act_salary(int p) {
    if (dsu[p] == p) return make_pair(lazy[p].pay_salary_sum, 0);
    pair res = get_act_salary(dsu[p]);
    res.second += lazy[dsu[p]].pay_salary_cnt - lazy[p].pay_salary_cnt_when_merge;
    return make_pair(
      res.first + lazy[p].pay_salary_sum + res.second * 
          (lazy[p].raise_salary_sum - lazy[p].raise_salary_sum_when_merge), 
      res.second
    );
}

int main() {
    int n, q;
    scanf("%d%d", &n, &q);
    int cnt = n;  // This variable is the count of nodes currently as quitting will create new nodes.
    for (int i=1;i<=n;++i) {
        // Note that we can see the initial salary as a raise.
        scanf("%lld", &(lazy[i].raise_salary_sum));
        dsu[i] = id[i] = i;
        size[i] = 1;
    }
    while (q--) {
        int op;
        scanf("%d", &op);

        if (op == 1) {
            int x, y;
            scanf("%d%d", &x, &y);
            merge(x, y);
        }
        else if (op == 2) {
            int p, x;
            scanf("%d%d", &p, &x);
            p = find(p);  // Find the root!
            lazy[p].raise_salary_sum += x;  // r_p = r_p + x
        }
        else if (op == 3) {
            int p;
            scanf("%d", &p);
            p = find(p);
            ++lazy[p].pay_salary_cnt;  // c_p = c_p + 1
            lazy[p].pay_salary_sum += lazy[p].raise_salary_sum;  // p_p = p_p + r_p
        }
        else{
            int p; long long c;

            scanf("%d%lld", &p, &c);
            
            // Since I created maxq additional nodes in the array at the beginning,
            // no actual 'node creation' occurs here and
            // only assigning an unused node to p is necessary.
            b[p] += get_act_salary(id[p]).first;
            id[p] = ++cnt;
            dsu[cnt] = cnt;
            size[cnt] = 1;
            lazy[cnt].raise_salary_sum = c;  // Treat the initial salary as a raise again.
        }

        // A relic of my debug code!
        // Bugs are everywhere and printing out the information of
        // the data structures after each operation often
        // helps a lot!
        //
        // for (int i=1; i <= n; ++i) {
        //     printf("%lld", b[i] + get_act_salary(id[i]).first);
        //     putchar(" \n"[i==n]);
        // }
    }
    for (int i=1; i <= n; ++i) {
        printf("%lld", b[i] + get_act_salary(id[i]).first);
        putchar(" \n"[i==n]);
    }
}
```
