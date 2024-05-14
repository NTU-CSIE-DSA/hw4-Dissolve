#include <stdio.h>
#define maxn (int)1e6 + 1
#define maxq (int)2e6

long long b[maxn] = {};
int sz[maxn + maxq] = {}, parent[maxn + maxq] = {}, company_id[maxn] = {};
long long total_reward[maxn + maxq] = {}, reward[maxn + maxq] = {}, total_reward_tag[maxn + maxq] = {} , reward_tag[maxn + maxq] = {};
int s_cnt[maxn + maxq] = {}, s_cnt_tag[maxn + maxq] = {}, s_cnt_add[maxn + maxq] = {};
int company_num = 0;

int path_compression(int x, long long *total_r, long long *r, int *cnt) {
  if(parent[x] == x) {
    *total_r = total_reward[x];
    *r = reward[x];
    *cnt = s_cnt[x];
    return x;
  }
  else {
    int ret = path_compression(parent[x], total_r, r, cnt);
    *total_r = total_reward[x] + (*total_r) - total_reward_tag[x] + ((*cnt) - s_cnt_tag[x]) * (reward[x] - reward_tag[x]);
    *r = (*r) + reward[x] - reward_tag[x];
    *cnt = (*cnt) - s_cnt_tag[x] + s_cnt[x];
    parent[x] = ret;
    total_reward[x] = *total_r;
    reward[x] = *r;
    s_cnt_add[x] = (*cnt) - s_cnt[x];
    s_cnt[x] = *cnt;
    total_reward_tag[x] = total_reward[ret];
    reward_tag[x] = reward[ret];
    s_cnt_tag[x] = s_cnt[ret];
    return ret;
  }
}

int find_set(int p) {
  int x = company_id[p];
  long long total_r = 0, r = 0;
  int cnt = 0;
  return path_compression(x, &total_r, &r, &cnt);
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

long long calculate_salary(int p) {
  find_set(p);
  int x = company_id[p];
  return total_reward[x];
}

void create_company(int p, long long salary) {
  b[p] += calculate_salary(p);
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
    b[i] += calculate_salary(i);
    printf("%lld ", b[i]);
  }
  printf("\n");
  return 0;
}
