#include <bits/stdc++.h>
#include "jngen.h"
using namespace std;
typedef long long ll;

int main(int argc, char *argv[]){
    registerGen(argc, argv, 1);
    bool randNQ = atoi(argv[1]);
    int N = atoi(argv[2]), Q = atoi(argv[3]);
    if (randNQ){
        N = rnd.next(N / 2, N);
        Q = rnd.next(Q / 2, Q);
    }
    vector <int> ops = {1, 2, 3, 4};
    if (argv[4] == to_string(atoi(argv[4]))){
        ops.clear();
        for (int i=1;i<=4;++i){
            for (int __=atoi(argv[i+3]);__--;){
                ops.push_back(i);
            }
        }
    }

    cout << N << ' ' << Q << '\n';
    for (int i=1;i<=N;++i){
        cout << rnd.next(1ll, (long long)1e12) << " \n"[i == N];
    }
    for (int i=1;i<=Q;++i){
        int op = rnd.choice(ops);

        cout << op << ' ';
        if (op == 1){
            int x = rnd.next(1, N), y = rnd.next(1, N);
            while (y == x) y = rnd.next(1, N);

            cout << x << ' ' << y;
        }
        else if (op == 2){
            int p = rnd.next(1, N);
            int x = rnd.next(1, 1000000);

            cout << p << ' ' << x;
        }
        else if (op == 3){
            int p = rnd.next(1, N);

            cout << p;
        }
        else if (op == 4){
            int p = rnd.next(1, N);
            ll c = rnd.next(1ll, (ll)1e12);

            cout << p << ' ' << c;
        }
        cout << '\n';
    }
}