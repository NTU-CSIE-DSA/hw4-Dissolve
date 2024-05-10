#include <stdio.h>
#include <stdlib.h>
#define maxn (int)3e6+10
typedef long long ll;

typedef struct dsu_node{
    int id;
    dsu_node *f;
    ll give_salary_cnt, give_salary_sum, add_salary_sum;
    int size;
}dsu_node;
dsu_node* newNode(int id){
    dsu_node* t = malloc(sizeof(dsu_node));
    t->id = id;
    t->f = NULL;
    t->give_salary_cnt = t->give_salary_sum = t->add_salary_sum = 0;
    size = 0;
}

ll s[maxn], b[maxn];
dsu_node* dsu[maxn];

dsu_node* find_rec(dsu_node *x, ll *give_salary_cnt, ll *give_salary_sum, ll *add_salary_sum){
    if (x->f == NULL) return x;
    dsu_node* ret = find_rec(x->f, give_salary_cnt, give_salary_sum, add_salary_sum);
    x->f = ret;
    *give_salary_cnt += x->give_salary_cnt;
    x->give_salary_cnt = *give_salary_cnt;
    *give_salary_sum += x->give_salary_sum;
    x->give_salary_sum = *give_salary_sum;
    *add_salary_sum += x->add_salary_sum;
    x->add_salary_sum = *add_salary_sum;
}
dsu_node* find(dsu_node *x){
    ll give_salary_cnt = 0, give_salary_sum = 0, add_salary_sum = 0;
    return find_rec(x, &give_salary_cnt, &give_salary_sum, &add_salary_sum);
}
void merge(int x, int y){
    dsu_node *a = find(dsu[x]), *b = find(dsu[y]);
    if (a == b) return;
    if (a->size > b->size){
        b->f = a;
        a->size += b->size;
    }
    else{
        a->f = b;
        b->size += a->size;
    }
}

int main(){
    int n, q;
    scanf("%d%d", &n, &q);
    for (int i=1;i<=n;++i){
        scanf("%lld", s+i);
        b[i] = 0;
        dsu[i] = newNode(i);
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
            dsu_node *root = find(dsu[p]);
            root->add_salary_sum += x;
        }
        else if (op == 3){
            int p;

            scanf("%d", &p);
            dsu_node *root = find(dsu[p]);
            ++root->give_salary_cnt;
        }
        else ;
    }
}