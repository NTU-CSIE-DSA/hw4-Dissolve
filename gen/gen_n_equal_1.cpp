#include <bits/stdc++.h>
#include "jngen.h"
using namespace std;
typedef long long ll;

int main(int argc, char *argv[]){
  registerGen(argc, argv);
  int N = 1, Q = atoi(argv[1]);
  vector<int> ops;
  for(int i = 2; i <= 4; i++) {
    for(int j = 0; j < atoi(argv[i]); j++) {
      ops.push_back(i);
    }
  }

  cout << N << ' ' << Q << '\n';
  cout << rnd.next(1LL, (ll) 1e12) << '\n';
  while (Q--) {
    int op = rnd.choice(ops);

    if (op == 1) {
      assert(false);
    }
    else if (op == 2) {
      cout << "2 1 " << rnd.next(1, (int)1e6); 
    }
    else if (op == 3) {
      cout << "3 1";
    }
    else {
      cout << "4 " << 1 << ' ' << rnd.next(1LL, (ll)1e12);
    }

    cout << '\n';
  }
}
