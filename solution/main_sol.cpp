#include <stdio.h>
#include <stdlib.h>
#define maxn (int)3e6+10
#define maxq (int)5e6+10
typedef long long ll;

int dsu[maxn+maxq], size[maxn+maxq], id[maxn];
ll b[maxn];
typedef struct pair{
    ll first;
    int second;
}pair;
pair make_pair(ll a, int b){
    pair p;
    p.first = a;
    p.second = b;
    return p;
}
typedef struct lazyTag{
    ll add_salary_sum, give_salary_sum;
    int give_salary_cnt;
    ll add_salary_sum_when_merge;
    int give_salary_cnt_when_merge;
}lazyTag;
lazyTag lazy[maxn+maxq];

int find(int x){
    x = id[x];
    while (dsu[x] != x) x = dsu[x];
    return x;
}

void merge(int x, int y){
    x = find(x); y = find(y);
    if (x == y) return;

    if (size[x] > size[y]){
        dsu[y] = x;
        size[x] += size[y];
        lazy[y].add_salary_sum_when_merge = lazy[x].add_salary_sum;
        lazy[y].give_salary_cnt_when_merge = lazy[x].give_salary_cnt;
        lazy[y].give_salary_sum -= lazy[x].give_salary_sum;
    }
    else{
        dsu[x] = y;
        size[y] += size[x];
        lazy[x].add_salary_sum_when_merge = lazy[y].add_salary_sum;
        lazy[x].give_salary_cnt_when_merge = lazy[y].give_salary_cnt;
        lazy[x].give_salary_sum -= lazy[y].give_salary_sum;
    }
}
pair get_act_salary(int p){
    if (dsu[p] == p) return make_pair(lazy[p].give_salary_sum, 0);
    pair res = get_act_salary(dsu[p]);
    res.second += lazy[dsu[p]].give_salary_cnt - lazy[p].give_salary_cnt_when_merge;
    return make_pair(res.first
                   + lazy[p].give_salary_sum
                   + res.second * (lazy[p].add_salary_sum - lazy[p].add_salary_sum_when_merge),
                //    - (lazy[dsu[p]].give_salary_cnt - lazy[p].give_salary_cnt_when_merge) * lazy[p].add_salary_sum_when_merge,
                     res.second);
}

int main(){
    int n, q;
    scanf("%d%d", &n, &q);
    int cnt = n;
    for (int i=1;i<=n;++i){
        scanf("%lld", &(lazy[i].add_salary_sum));
        dsu[i] = id[i] = i;
        size[i] = 1;
    }
    while (q--){
        int op;

        scanf("%d", &op);
        if (op == 1){
            int x, y;

            scanf("%d%d", &x, &y);
            merge(x, y);
        }
        else if (op == 2){
            int p, x;

            scanf("%d%d", &p, &x);
            p = find(p);
            lazy[p].add_salary_sum += x;
        }
        else if (op == 3){
            int p;

            scanf("%d", &p);
            p = find(p);
            ++lazy[p].give_salary_cnt;
            lazy[p].give_salary_sum += lazy[p].add_salary_sum;
        }
        else{
            int p; ll c;

            scanf("%d%lld", &p, &c);
            
            b[p] += get_act_salary(id[p]).first;
            id[p] = ++cnt;
            dsu[cnt] = cnt;
            size[cnt] = 1;
            lazy[cnt].add_salary_sum = c;
        }
        // for (int i=1;i<=n;++i){
        //     printf("%lld", b[i] + get_act_salary(id[i]).first);
        //     putchar(" \n"[i==n]);
        // }
    }
    for (int i=1;i<=n;++i){
        printf("%lld", b[i] + get_act_salary(id[i]).first);
        putchar(" \n"[i==n]);
    }
}