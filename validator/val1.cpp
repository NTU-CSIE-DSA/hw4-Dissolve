#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;

int main(){
    registerValidation();
    int n = inf.readInt(1, 1000, "n");
    inf.readSpace();
    int q = inf.readInt(1, 2000, "q");
    inf.readEoln();
    for (int i=1;i<=n;++i){
        int ai = inf.readLong(1ll, (long long)1e12, "a" + to_string(i));
        if (i != n) inf.readSpace();
        else inf.readEoln();
    }
    for (int i=1;i<=q;++i){
        int op_i = inf.readInt(1, 4, "op_i");
        inf.readSpace();
        if (op_i == 1){
            inf.readInt(1, n, "union x");
            inf.readSpace();
            inf.readInt(1, n, "union y");
        }
        else if (op_i == 2){
            inf.readInt(1, n, "add salary p");
            inf.readSpace();
            inf.readInt(1, 1e6, "add salary value");
        }
        else if (op_i == 3){
            inf.readInt(1, n, "give salary p");
        }
        else{
            inf.readInt(1, n, "quit p");
            inf.readSpace();
            inf.readLong(1ll, (long long)1e12, "quit init salary");
        }
        inf.readEoln();
    }
    inf.readEof();
}