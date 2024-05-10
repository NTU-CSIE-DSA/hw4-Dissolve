#include <fstream>
#include <iostream>
#include <vector>
#include <cstdio>
using namespace std;

int main(int argc, char *argv[]){
    if (argc <= 3){
        cerr << "Too few args\n";
        exit(0);
    }
    double tl = atof(argv[1]); int ml = atoi(argv[2]);
    int points[20];
    int testcasecnt = argc - 3;
    for (int i=0;i<testcasecnt;++i) points[i] = atoi(argv[i+3]);

    ifstream mapping;
    mapping.open("./tests/mapping");
    string pst, st, tc;
    mapping >> pst >> tc;
    vector <vector<string>> tcs(1, vector<string>(1, tc));

    while (mapping >> st >> tc){
        if (st == pst) tcs.back().push_back(tc);
        else tcs.push_back(vector<string>(1, tc));
        pst = st;
    }

    ofstream meta;
    meta.open("./package/meta.json");
    meta << "{\n";
    meta << "\t\"name\": \"[HW4.P4] Dissolve of the Short-lived Agency\",\n";
    meta << "\t\"timeLimit\": " << tl << ",\n";
    meta << "\t\"memLimit\": " << ml << ",\n";
    meta << "\t\"testdata\": [\n";
    for (int i=0;i<testcasecnt;++i){
        meta << "\t\t{\n";
        meta << "\t\t\t\"points\": " << points[i] << ",\n";
        meta << "\t\t\t\"tests\": [";
        for (auto &s:tcs[i]){
            meta << '"' << s << "\"";
            if (s != tcs[i].back()) meta << ", ";
        }
        meta << "]\n";
        meta << "\t\t}";
        if (i < testcasecnt-1) meta << ',';
        meta << '\n';
    }
    meta << "\t]\n";

    meta << "}\n";

    return 0;
}