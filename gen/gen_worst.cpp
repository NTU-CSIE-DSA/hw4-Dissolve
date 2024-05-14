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
  auto arr = Array::id(N).shuffled();
  for(int i = 1; i <= N; i++) {
    v.push_back({arr[i - 1] + 1});
  }
  while (Q--) {
    int op = rnd.choice(ops);

    if (op == 1) {
      cout << "1 ";
      if(v.size() > 1) {
        int x = rnd.choice(v[0]);
        int y = rnd.choice(v[1]);
        auto tmp = v[0];
        for(auto &z: v[1]) {
          tmp.push_back(z);
        }
        v.push_back(tmp);
        v.pop_front();
        v.pop_front();
        cout << x << ' ' << y;
      }
      else {
        int x = rnd.next(1, N), y = rnd.next(1, N);
        while(x == y) {
          y = rnd.next(1, N);
        }
        cout << x << ' ' << y;
      }
    }
    else if (op == 2) {
      if(rnd.next(0, 1)) {
        if(pick) cout << "2 " << v.back()[v.back().size() - 1] << ' ' << rnd.next(1, (int) 1e6);
        else cout << "2 " << rnd.choice(v.back()) << ' ' << rnd.next(1, (int) 1e6);
      }
      else {
        cout << "2 " << rnd.next(1, N) << ' ' << rnd.next(1, (int) 1e6);
      }
    }
    else if (op == 3) {
      if(rnd.next(0, 1)) {
        if(pick) cout << "3 " << v.back()[v.back().size() - 1];
        else cout << "3 " << rnd.choice(v.back());
      }
      else {
        cout << "3 " << rnd.next(1, N);
      }
    }
    else {
      cout << "4 " << rnd.next(1, N) << ' ' << rnd.next(1LL, (ll)1e12);
    }

    cout << '\n';
  }
}
