clang++ encodeLevels.cpp data/lineList.cpp data/lineListNintendo.cpp data/basemath.cpp data/qrcodegen.cpp -v -o encodeLevels -I./include -lbrotlienc -lbrotlidec
./encodeLevels
rm encodeLevels