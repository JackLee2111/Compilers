flex ./word.l
yacc -d ./grammar.y
# g++ y.tab.c lex.yy.c -o mc -w
# ./mc ./1.sy
./mc ./test.sy
gcc assemble.s -o assemble
./assemble
