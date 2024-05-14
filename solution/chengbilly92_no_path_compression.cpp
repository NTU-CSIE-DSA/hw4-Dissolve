#include <stdio.h>
#define maxn (int)1e6 + 1
#define maxq (int)2e6

long long b[maxn] = {};
int sz[maxn + maxq] = {}, parent[maxn + maxq] = {}, company_id[maxn] = {};
long long total_reward[maxn + maxq] = {}, reward[maxn + maxq] = {}, total_reward_tag[maxn + maxq] = {} , reward_tag[maxn + maxq] = {};
int s_cnt[maxn + maxq] = {}, s_cnt_tag[maxn + maxq] = {}, s_cnt_add[maxn + maxq] = {}, s_cnt_add_tag[maxn + maxq] = {};
int company_num = 0;

int find_set(int p) {
  int x = company_id[p];
  while(x != parent[x]) {
    x = parent[x];
  }
  return x;
}

void merge(int x, int y) {
  x = find_set(x), y = find_set(y);
  if(x == y) return;
  if(sz[x] < sz[y]) {
    parent[x] = y;
    sz[y] += sz[x];
    total_reward_tag[x] = total_reward[y];
    reward_tag[x] = reward[y];
    s_cnt_tag[x] = s_cnt[y];
  }
  else {
    parent[y] = x;
    sz[x] += sz[y];
    total_reward_tag[y] = total_reward[x];
    reward_tag[y] = reward[x];
    s_cnt_tag[y] = s_cnt[x];
  }
}

long long calculate_salary(int x, int *cnt) {
  if(parent[x] == x) {
    *cnt = s_cnt[x];
    return total_reward[x];
  }
  long long ret = calculate_salary(parent[x], cnt);
  ret += total_reward[x] - total_reward_tag[x] + ((*cnt) - s_cnt_tag[x]) * reward[x] - reward_tag[x] * ((*cnt) - s_cnt_tag[x]);
  *cnt = (*cnt) + s_cnt[x] - s_cnt_tag[x];
  return ret;
}

void create_company(int p, long long salary) {
  int cnt = 0;
  b[p] += calculate_salary(company_id[p], &cnt);
  company_id[p] = company_num;
  parent[company_num] = company_num;
  reward[company_num] = salary;
  sz[company_num] = 1;
  company_num++;
}

int main () {

  int n, q;
  scanf("%d%d", &n, &q);
  for(int i = 0; i < n; i++) {
    b[i] = 0;
    parent[i] = i;
    company_id[i] = i;
    sz[i] = 1;
    scanf("%lld", &reward[i]);
  }
  company_num = n;
  for(int i = 0; i < q; i++) {
    int op;
    scanf("%d", &op);
    if(op == 1) {
      int x, y;
      scanf("%d%d", &x, &y);
      x--; y--;
      merge(x, y);
    }
    else if(op == 2) {
      int p, r;
      scanf("%d%d", &p, &r);
      p--;
      int x = find_set(p);
      reward[x] += r;
    }
    else if(op == 3) {
      int p;
      scanf("%d", &p);
      p--;
      int x = find_set(p);
      s_cnt[x]++;
      total_reward[x] += reward[x];
    }
    else {
      int p;
      long long c;
      scanf("%d%lld", &p, &c);
      p--;
      create_company(p, c);
    }
  }
  for(int i = 0; i < n; i++) {
    int cnt = 0;
    b[i] += calculate_salary(company_id[i], &cnt);
    printf("%lld ", b[i]);
  }
  printf("\n");
  return 0;
}
