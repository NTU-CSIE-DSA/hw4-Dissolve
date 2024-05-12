#include <iostream>
#include <vector>
typedef long long ll;
#define maxn (int)3e5+10
using namespace std;

ll s[maxn], b[maxn];
vector <vector<int>> v;
int getV(int x){
    for (int i=0;;++i){
        for (auto &t:v[i]) if (t == x) return i;
    }
}
int main(){
    int n, q;

    cin >> n >> q;
    for (int i=1;i<=n;++i) {cin >> s[i]; v.push_back(vector<int>(1, i));}
    while (q--){
        char op;

        cin >> op;
        if (op == '1'){
            int x, y;

            cin >> x >> y;
            x = getV(x); y = getV(y);
            if (x == y) continue;

            for (auto &t:v[y]) v[x].push_back(t);
            v.erase(v.begin()+y);
        }
        else if (op == '2'){
            int p, x;

            cin >> p >> x;
            int i = getV(p);
            for (auto &t:v[i]) s[t] += x;
        }
        else if (op == '3'){
            int p;

            cin >> p;
            int i = getV(p);
            for (auto &t:v[i]) b[t] += s[t];
        }
        else{
            int p; ll c;

            cin >> p >> c;
            s[p] = c;
            int i = getV(p);
            for (int j=0;j<v[i].size();++j) if (v[i][j] == p){
                v[i].erase(v[i].begin()+j);
                break;
            }
            v.push_back(vector<int>(1, p));
        }
    }
    for (int i=1;i<=n;++i) cout << b[i] << " \n"[i==n];
}