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
