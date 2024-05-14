#include <bits/stdc++.h>
#include "jngen.h"
using namespace std;
typedef long long ll;

int main(int argc, char *argv[]){
  registerGen(argc, argv);
  int N = atoi(argv[1]), Q = atoi(argv[2]);
  bool pick = atoi(argv[3]);
  vector<int> ops;
  for(int i = 1; i <= 4; i++) {
    for(int j = 0; j < atoi(argv[i + 3]); j++) {
      ops.push_back(i);
    }
  }

  cout << N << ' ' << Q << '\n';
  for (int i=1;i<=N;++i) cout << rnd.next(1ll, (ll)1e12) << " \n"[i==N];
  deque<vector<int>> v;
  int index = rnd.next(1, N);
  vector<int> v_index;
  for(int i = 1; i <= N; i++) {
    if(i != index) v.push_back({i});
  }
  v_index.push_back(index);
  while (Q--) {
    int op = rnd.choice(ops);

    if (op == 1) {
      cout << "1 ";
      if(v.size() == 0) {
        int x = rnd.next(1, N);
        int y = rnd.next(1, N);
        while(x == y) y = rnd.next(1, N);
        cout << x << ' ' << y;
      }
      else if(rnd.next(0, 1) || v.size() == 1) {
        int x = rnd.choice(v_index);
        int y = rnd.choice(v[0]);
        for(auto &z: v[0]) {
          v_index.push_back(z);
        }
        v.pop_front();
        cout << x << ' ' << y;
      }
      else {
        int c = rnd.next(1, (int) v.size() - 1);
        int x = rnd.choice(v[0]);
        int y = rnd.choice(v[c]);
        for(auto &z: v[0]) {
          v[c].push_back(z);
        }
        v.pop_front();
        cout << x << ' ' << y;
      }
      if(!v.empty()) {
        int idx = rnd.next(0, (int) v.size() - 1);
        if(idx != 0) v[0].swap(v[idx]);
      }
    }
    else if (op == 2) {
      int seed = rnd.next(0, 2);
      if(seed == 0) {
        cout << "2 " << rnd.choice(v_index) << ' ' << rnd.next(1, (int) 1e6);
      }
      else if(seed == 1) {
        cout << "2 " << index << ' ' << rnd.next(1, (int) 1e6);
      }
      else {
        cout << "2 " << rnd.next(1, N) << ' ' << rnd.next(1, (int) 1e6);
      }
    }
    else if (op == 3) {
      int seed = rnd.next(0, 2);
      if(seed == 0) {
        cout << "3 " << rnd.choice(v_index);
      }
      else if(seed == 1) {
        cout << "3 " << index;
      }
      else {
        cout << "3 " << rnd.next(1, N);
      }
    }
    else {
      int x = rnd.next(1, N);
      while(x == index) {
        x = rnd.next(1, N);
      }
      cout << "4 " << x << ' ' << rnd.next(1LL, (ll)1e12);
    }

    cout << '\n';
  }
}
