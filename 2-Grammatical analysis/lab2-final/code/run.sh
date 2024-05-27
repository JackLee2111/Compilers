# 此脚本用于词法、语法分析，生成out.txt文件
flex ./morphology.l
yacc -d ./grammar.y
gcc y.tab.c lex.yy.c -o mc -O2 -w
./mc ./test/3.sy > ./test/3-out.txt
