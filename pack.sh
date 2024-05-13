rm -rf ./package/
mkdir ./package
mkdir ./package/testdata
cp prob.md ./package/prob.md
cp ./tests/*.in ./package/testdata/
cp ./tests/*.out ./package/testdata/
g++ ./packdata.cpp -o packdata.exe
./packdata.exe 2.5 524288 0 10 15 20 15 20 20

rm -f ./package.tar.gz
tar zcvf package.tar.gz package
