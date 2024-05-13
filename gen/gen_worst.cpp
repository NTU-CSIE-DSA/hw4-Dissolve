#include <bits/stdc++.h>
#include "jngen.h"
using namespace std;
typedef long long ll;

int main(int argc, char *argv[]){
    registerGen(argc, argv);
    int N = atoi(argv[1]), Q = atoi(argv[2]);
    bool pick = atoi(argv[3]);
    bool haveOp[4] = {atoi(argv[4]), atoi(argv[5]), atoi(argv[6]), atoi(argv[7])};

    int mergeCnt = 0;
    vector<set<int>> v[21];
    for (int i=1;i<=N;++i) v[0].push_back({i});
    cout << N << ' ' << Q << '\n';
    for (int i=1;i<=N;++i) cout << rnd.next(1ll, (ll)1e12) << " \n"[i==N];
    while (Q--){
        int op = rnd.next(1, 4);
        while (!haveOp[op-1]) op = rnd.next(1, 4);

        if (op == 1){
            int can1 = -1, can1i, can1j, can2 = -1, can2i, can2j;
            for (int i=0;i<20;++i){
                for (int j=0;j<v[i].size();++j){
                    if (can1 == -1){
                        can1 = *(pick ? prev(v[i][j].end()) : v[i][j].begin());
                        can1i = i;
                        can1j = j;
                    }
                    else{
                        can2 = *(pick ? prev(v[i][j].end()) : v[i][j].begin());
                        can2i = i;
                        can2j = j;
                        break;
                    }
                }
                if (can2 != -1) break;
            }
            if (can2 == -1) can2 = rnd.choice(v[can1i][can1j]);
            else if (can1i != can2i || can1j != can2j){
                set <int> ns;
                for (auto &t:v[can1i][can1j]) v[can2i][can2j].insert(t);
                v[can2i+1].push_back({});
                v[can2i+1].back().swap(v[can2i][can2j]);
                v[can2i].erase(v[can2i].begin() + can2j);
                v[can1i].erase(v[can1i].begin() + can1j);
            }
            cout << "1 " << can1 << ' ' << can2;
        }
        else if (op == 2){
            cout << "2 ";
            for (int i=19;i>=0;--i) if (!v[i].empty()){
                int j = rnd.next(0, (int)v[i].size()-1);

                if (pick) cout << *prev(v[i][j].end()) << ' ' << rnd.next(1, (int)1e6);
                else cout << *v[i][j].begin() << ' ' << rnd.next(1, (int)1e6);
                break;
            }
        }
        else if (op == 3){
            cout << "3 ";
            for (int i=19;i>=0;--i) if (!v[i].empty()){
                int j = rnd.next(0, (int)v[i].size()-1);

                if (pick) cout << *prev(v[i][j].end());
                else cout << *v[i][j].begin();
                break;
            }
        }
        else{
            int p = rnd.next(1, N);
            cout << "4 " << p << ' ' << rnd.next(1ll, (ll)1e12);
            v[0].push_back({p});
        }

        cout << '\n';
    }
}